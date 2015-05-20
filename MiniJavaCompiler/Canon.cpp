#include "Canon.h"


namespace Canon
{
	StmExpList* nopNull = new StmExpList( new EXP( new CONST( 0 ) ), nullptr );

	bool isNop( const IStm* a )
	{
		const EXP* exp = dynamic_cast< const EXP* >( a );
		return exp != 0
			&& dynamic_cast< const CONST* >( exp->GetExp() ) != 0;
	}

	bool commute( const IStm* a, const IExp* b )
	{
		return isNop( a )
			|| dynamic_cast< const NAME* >( b ) != 0
			|| dynamic_cast< const CONST* >( b ) != 0;
	}

	const IStm* seq( const IStm* a, const IStm* b )
	{
		if( isNop( a ) ) {
			return b;
		} else if( isNop( b ) ) {
			return a;
		} else {
			return new SEQ( a, b );
		}
	}

	const IStm* do_stm( const SEQ* s )
	{
		return seq( do_stm( s->GetLeft() ), do_stm( s->GetLeft() ) );
	}

	const IStm* do_stm( const MOVE* s )
	{
		const TEMP* stemp = dynamic_cast< const TEMP* >( s->GetDst() );
		const CALL* scall = dynamic_cast< const CALL* >( s->GetSrc() );

		const ESEQ* seseq = dynamic_cast< const ESEQ* >( s->GetDst() );

		if( stemp != 0 && scall != 0 ) {
			return reorder_stm( new MoveCall( stemp, scall ) );
		} else if( seseq != 0 ) {
			return do_stm( new SEQ( seseq->GetStm(),
				new MOVE( seseq->GetExp(), s->GetSrc() ) ) );
		} else {
			return reorder_stm( s );
		}
	}

	const IStm* do_stm( const EXP* s )
	{
		const CALL* scall = dynamic_cast< const CALL* >( s->GetExp() );
		if( scall != 0 ) {
			return reorder_stm( new ExpCall( scall ) );
		} else {
			return reorder_stm( s );
		}
	}

	const ESEQ* do_exp( const ESEQ* e )
	{
		const IStm* stms = do_stm( e->GetStm() );
		const ESEQ* b = do_exp( e->GetExp() );
		return new ESEQ( seq( stms, b->GetStm() ), b->GetExp() );
	}

	const IStm* do_stm( const IStm* s )
	{
		const SEQ* sseq = dynamic_cast< const SEQ* >( s );
		const MOVE* smove = dynamic_cast< const MOVE* >( s );
		const EXP* sexp = dynamic_cast< const EXP* >( s );

		if( sseq != 0 ) {
			return do_stm( sseq );
		} else if( smove != 0 ) {
			return do_stm( smove );
		} else if( sexp != 0 ) {
			return do_stm( sexp );
		} else {
			return reorder_stm( s );
		}
	}

	const ESEQ* do_exp( const IExp* e )
	{
		const ESEQ* eeseq = dynamic_cast< const ESEQ* >( e );
		if( eeseq ) {
			return do_exp( eeseq );
		} else {
			return reorder_exp( e );
		}
	}

	const StmExpList* reorder( const CExpList* exps )
	{
		if( exps == nullptr )
			return nopNull;
		else {
			const IExp* a = exps->GetHead();
			if( dynamic_cast< const CALL* >( a ) != 0 ) {
				Temp::CTemp* t = new Temp::CTemp();
				IExp* e = new ESEQ( new MOVE( new TEMP( t ), a ), new TEMP( t ) );
				return reorder( new CExpList( e, exps->GetTail() ) );
			} else {
				const ESEQ* aa = do_exp( a );
				const StmExpList* bb = reorder( exps->GetTail() );
				if( commute( bb->GetStm(), aa->GetExp() ) )
					return new StmExpList( seq( aa->GetStm(), bb->GetStm() ),
					new CExpList( aa->GetExp(), bb->GetExps() ) );
				else {
					Temp::CTemp* t = new Temp::CTemp();
					return new StmExpList(
						seq( aa->GetStm(), seq( new MOVE( new TEMP( t ), aa->GetExp() ), bb->GetStm() ) ),
						new CExpList( new TEMP( t ), bb->GetExps() ) );
				}
			}
		}
	}

	const IStm* reorder_stm( const IStm* s )
	{
		const StmExpList* x = reorder( s->kids() );
		return seq( x->GetStm(), s->build( x->GetExps() ) );
	}

	const ESEQ* reorder_exp( const IExp* e )
	{
		const StmExpList* x = reorder( e->kids() );
		return new ESEQ( x->GetStm(), e->build( x->GetExps() ) );
	}

	const CStmList* linear( const SEQ* s, const CStmList* l )
	{
		return linear( s->GetLeft(), linear( s->GetRight(), l ) );
	}

	const CStmList* linear( const IStm* s, const CStmList* l )
	{
		const SEQ* sseq = dynamic_cast< const SEQ* >( s );
		if( sseq != 0 ) {
			return linear( sseq, l );
		} else {
			return new CStmList( s, l );
		}
	}

	const CStmList* linearize( const IStm* s )
	{
		return linear( do_stm( s ), nullptr );
	}

	// === CCanon ===
	CCanon::CCanon( const IStm* statement, const Frame::CFrame* frame ):
		_statement(statement), _methodFrame(frame) {
	}

	void CCanon::Canonize() {
		this->linearizeStatetment();
		this->split();
		this->connect();
		this->generateTraces();
		this->optimizeCJUMPBlocks();
		this->translateToStatements();
	}

	void CCanon::linearizeStatetment() {
		_linearizedStatements = linearize( _statement );
	}

	void CCanon::split() {
		_basicBlocks.clear();

		// ������� ����
		CBasicBlock currentBasicBlock;
		currentBasicBlock.Clear();

		// �������� ������� ���������
		const IStm* currentExp = _linearizedStatements->GetHead();
		while ( currentExp ) {

			// ��������� ���
			if ( isLABEL( currentExp ) ) {
				// ���� ��������� �����, �� ��� ��������� �� ������ ������ �����

				// ��������� ���������� ����
				_basicBlocks.push_back( currentBasicBlock );
				currentBasicBlock.Clear();
				currentBasicBlock.Label = dynamic_cast<const IRTree::LABEL*>( currentExp );

			}
			else if ( isCJUMP( currentExp ) || isJUMP( currentExp ) ) {
				// ���� ��������� ������, �� �� ��������� ����
				currentBasicBlock.Jump = currentExp;
				_basicBlocks.push_back( currentBasicBlock );
				currentBasicBlock.Clear();
			}
			else {
				// ����� ������ ��������� ���������� � ����
				currentBasicBlock.AddStatement( currentExp );
			}

			// ��������� � ������ ���������
			const CStmList* tail = _linearizedStatements->GetTail();
			if ( tail ) {
				currentExp = tail->GetHead();
			}
		}
	}

	void CCanon::connect() {
		const IStm* labelOfCurrentBlock = nullptr;
		const IStm* jumpOfCurrentBlock = nullptr;

		// ����� ��������� �� ����� ������, ������ �����
		auto& previousBlock = _basicBlocks.begin();
		auto& nextBlock = ( _basicBlocks.begin() )++;

		// ���� � ������� ����� ����������� �����
		if ( !previousBlock->Label ) {
			// �� ���� � �� ������
			previousBlock->Label = new LABEL( _methodFrame->GetStartLabel() );
		}

		// ���� �� ������� � �����
		while ( nextBlock != _basicBlocks.end() ) {

			// ����� ���� ��� ������

			// ���� ���������� ���� �� ����� ��������, �� ���� ����� � ������ ����������
			if ( !previousBlock->Jump && nextBlock->Label ) {
				// �� ��������� �������
				previousBlock->Jump = new JUMP( nextBlock->Label->GetLabel() );
			}
			// ���� ����������� ����� ��� ��������, �� ��� ������ � ���������� ������
			else if ( previousBlock->Jump && !nextBlock->Label ) {
				throw( "Error by connecting basic blocks" );
			}
			// ������ ������, ����� ���� � �����, � ������� ��� �� ����������, ��������� ��� �� � �������.
			// ������, ����� ��� �� �����, �� �������� �� ����� ���� ������� (�� ��������� �� ����� ������ �� ������ � ���������)

			// ��������� � ����� ����
			previousBlock++;
			nextBlock++;
		}

		// ���� � ���������� ����� ����������� �������, �� �� ������ ������ ����� ������� �� ������ ������� (����������� �����)
		if ( !nextBlock->Jump ) {
			nextBlock->Jump = new JUMP( _methodFrame->GetEpilogueLabel() );
		}
	}

	void CCanon::generateTraces() {
		// ���� ����� ������� ����������������� �����
		std::vector<CBasicBlock> reorderedBlocks;

		// ������ ����� ��������� ������
		std::map<const Temp::CLabel*, bool> isBlockVisited;
		for ( auto& basicBlock : _basicBlocks ) {
			isBlockVisited[ basicBlock.Label->GetLabel() ] = false;
		}

		// ������� ��� �����
		for ( auto& basicBlock : _basicBlocks ) {
			// ������ ����� "����" (trace)
			std::vector<CBasicBlock*> currentTrace;

			// ����� ���������� �����
			CBasicBlock* currentBlock = &basicBlock;
			const Temp::CLabel* labelOfCurrentBlock = basicBlock.Label->GetLabel();

			// ���� �������� ������������ �����
			while ( !isBlockVisited[ labelOfCurrentBlock ] ) {
				// �������� ���� ���������� � ��������� ��� � ����� �����
				isBlockVisited[ labelOfCurrentBlock ] = true;
				currentTrace.push_back( currentBlock );

				// ��������� �����, ���� ����� ������� � ��������
				if ( currentBlock->GetJUMP() ) {
					const Temp::CLabel* jumpLabel = currentBlock->GetJUMP()->GetTargets()->GetHead();
				}
				else if ( currentBlock->GetCJUMP() ) {
					const Temp::CLabel* ifTrueLabel = currentBlock->GetCJUMP()->GetIfTrue();
					const Temp::CLabel* ifTrueLabel = currentBlock->GetCJUMP()->GetIfFalse();
				}

			}

			// ��������� ����, �������� ��� �������� � �������� ������
			reorderedBlocks.insert( reorderedBlocks.end(), currentTrace.begin(), currentTrace.end() );
			currentTrace.clear();
		}

		// ��������� �����
		_basicBlocks.clear();
		_basicBlocks = std::vector<CBasicBlock>( reorderedBlocks );
	}

	void CCanon::optimizeCJUMPBlocks() {
		// ���������� ��� ����� 
		for ( std::vector<CBasicBlock>::iterator basicBlock = _basicBlocks.begin(), nextBasicBlock = _basicBlocks.begin() + 1;
			nextBasicBlock != _basicBlocks.end();
			basicBlock++, nextBasicBlock++
			) {
			// ���� ���� ������������� CJUMP'��
			const IRTree::CJUMP* jumpStatement = ( *basicBlock )->GetCJUMP();
			if ( jumpStatement != nullptr ) {
				// �������� true � false �����
				const Temp::CLabel* falseLabel = jumpStatement->GetIfFalse();
				const Temp::CLabel* trueLabel = jumpStatement->GetIfFalse();

				// ��������� ����� ���������� �����
				const Temp::CLabel* nextBlockLabel = ( *nextBasicBlock )->Label->GetLabel();

				// ���� fals�-���� ��� ��� �� CJUMP-�� - ������ ���������� ����
				if ( nextBlockLabel == falseLabel ) {
					continue;
				}
				// ���� ��� true-����� - �� ������ ������� ����� true � false � ������ ��������� �������
				else if ( nextBlockLabel == trueLabel ) {
					const IRTree::IExp *leftExpression = jumpStatement->GetLeft();
					const IRTree::IExp *rightExpression = jumpStatement->GetRight();
					IRTree::TCJump operation;
					switch ( jumpStatement->GetRelop() ) {
					case CJ_EQ:
						operation = CJ_NE;
						break;
					case CJ_NE:
						operation = CJ_EQ;
						break;
					case CJ_GE:
						operation = CJ_LT;
						break;
					case CJ_LT:
						operation = CJ_GE;
						break;
					case CJ_LE:
						operation = CJ_GT;
						break;
					case CJ_GT:
						operation = CJ_LE;
						break;
					default:
						break;
					}
					( *basicBlock )->Jump = new CJUMP( operation, leftExpression, rightExpression, falseLabel, trueLabel );
				}
				else {
					// � ��������� ������ �� CJUMP ��� ���-�� ������ ������ - ��� ����� ��
					// ������ ��������������� ���� � ������ �����
					CBasicBlock* newBlock = new CBasicBlock();
					// ������ ����� �����
					const Temp::CLabel* newLabel = new Temp::CLabel();
					newBlock->Label = new IRTree::LABEL( newLabel );
					newBlock->Jump = new JUMP( jumpStatement->GetIfFalse() );

					// ������������ false-�����
					( *basicBlock )->Jump = new CJUMP(
						jumpStatement->GetRelop(),
						jumpStatement->GetLeft(),
						jumpStatement->GetRight(),
						jumpStatement->GetIfTrue(),
						newLabel
						);

					// ��������� ����� ���� � ������������������
					auto insertedBlockIterator = _basicBlocks.insert( nextBasicBlock, newBlock );
					// �������������� ��������
					basicBlock = insertedBlockIterator;
					nextBasicBlock = insertedBlockIterator + 1;
				}
			}
		}
	}

	void CCanon::translateToStatements() {
		// ������ ��������
		std::list<const IRTree::IStm*> statements;
		
		// ���������� ���� ������
		auto basicBlock = _basicBlocks.begin();
		auto nextBasicBlock = basicBlock + 1;

		
		// ����� ��������� � ������ ����� ������� ����� � ��� ����������

		while ( nextBasicBlock != _basicBlocks.end() ) {
			// ��������� ���������� ������� �����
			for ( auto block : basicBlock->FlowStatements ) {
				statements.push_back( block );
			}

			// �������, ��� ��������� �� ����� ������. ���� ������ ���� ����������� JUMP'�� �� �����,
			// ������� ��� �� ��������� ���� - ������� ������� ��� ��������
			const IRTree::JUMP* jumpStatement = basicBlock->GetJUMP();
			const IRTree::LABEL* nextBlockLabel = nextBasicBlock->Label;
			bool isOmmited = false;

			if ( jumpStatement != nullptr ) {
				if ( jumpStatement->GetTargets()->GetHead() == nextBlockLabel->GetLabel() ) {
					isOmmited = true;
				}
			}

			if ( !isOmmited ) {
				statements.push_back( jumpStatement );
				statements.push_back( nextBlockLabel );
			}

			// ���������, ��� 
			basicBlock++;
			nextBasicBlock++;
		}
		// ��������� � ����� ���������� � ������� ���������� �����
		for ( auto block : basicBlock->FlowStatements ) {
			statements.push_back( block );
		}
		statements.push_back( basicBlock->Jump );

		// ������ ������ �� IStm ��������� � CStmList
		// ������ � �����
		const CStmList* list = nullptr;
		for ( auto statement = statements.rbegin(); statement != statements.rend(); statement++ ) {
			list = new CStmList( *statement, list );
		}
		_canonizedStatementsList = list;
	}
}

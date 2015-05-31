#include "Canon.h"
#include "IRTreePrinter.h"


namespace Canon
{
	StmExpList* nopNull = new StmExpList( new EXP( new CONST( 0 ) ), nullptr );

	bool isNop( const IStm* a )
	{
		const EXP* exp = dynamic_cast< const EXP* >( a );
		return exp != nullptr
			&& dynamic_cast< const CONST* >( exp->GetExp() ) != nullptr;
	}

	bool commute( const IStm* a, const IExp* b )
	{
		return isNop( a )
			|| dynamic_cast< const NAME* >( b ) != nullptr
			|| dynamic_cast< const CONST* >( b ) != nullptr;
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
		return seq( do_stm( s->GetLeft() ), do_stm( s->GetRight() ) );
	}

	const IStm* do_stm( const MOVE* s )
	{
		const TEMP* stemp = dynamic_cast< const TEMP* >( s->GetDst() );
		const CALL* scall = dynamic_cast< const CALL* >( s->GetSrc() );

		const ESEQ* seseq = dynamic_cast< const ESEQ* >( s->GetDst() );

		if( stemp != nullptr && scall != nullptr ) {
			return reorder_stm( new MoveCall( stemp, scall ) );
		} else if( seseq != nullptr ) {
			return do_stm( new SEQ( seseq->GetStm(),
				new MOVE( seseq->GetExp(), s->GetSrc() ) ) );
		} else {
			return reorder_stm( s );
		}
	}

	const IStm* do_stm( const EXP* s )
	{
		const CALL* scall = dynamic_cast< const CALL* >( s->GetExp() );
		if( scall != nullptr ) {
			return reorder_stm( new ExpCall( scall ) );
		} else {
			return reorder_stm( s );
		}
	}

	const IStm* do_stm( const IStm* s )
	{
		const SEQ* sseq = dynamic_cast< const SEQ* >( s );
		const MOVE* smove = dynamic_cast< const MOVE* >( s );
		const EXP* sexp = dynamic_cast< const EXP* >( s );

		if( sseq != nullptr ) {
			return do_stm( sseq );
		} else if( smove != nullptr ) {
			return do_stm( smove );
		} else if( sexp != nullptr ) {
			if( isNop( s ) ) {
				return nullptr;
			} else {
				return do_stm( sexp );
			}
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
		if( s == nullptr ) {
			return nullptr;
		}
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
		if( sseq != nullptr ) {
			return linear( sseq, l );
		} else {
			if( s != nullptr ) {
				return new CStmList( s, l );
			} else {
				return l;
			}
		}
	}

	const CStmList* linearize( const IStm* s )
	{
		if( s != nullptr ) {
			return linear( do_stm( s ), nullptr );
		} else {
			return nullptr;
		}
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

		const CStmList* list = _linearizedStatements;

		CIRTreePrinter *irTreePrinter = new CIRTreePrinter( "test.txt" );
		irTreePrinter->OpenFile();

		size_t methodsCounter = 1;
		while( list ) {
			irTreePrinter->ResetPrinter( "fragment" + std::to_string( methodsCounter ) + "_", "fragment" + std::to_string( methodsCounter ) );
			list->GetHead()->Accept( irTreePrinter );
			methodsCounter += 1;
			irTreePrinter->WriteGraphStructureToTheFile();

			// ��������� � ������ ���������
			list = list->GetTail();
		}
		irTreePrinter->CloseFile();
	}

	void CCanon::split() {
		_basicBlocks.clear();

		// ������� ����
		CBasicBlock currentBasicBlock;
		currentBasicBlock.Clear();
		bool isCleared = true; // ����, ��������������, ��� ������ �� �������� ����� ����������

		// �������� ������� ���������
		const CStmList* list = _linearizedStatements;
		while ( list ) {

			const IStm* currentExp = list->GetHead();

			// ��������� ���
			if ( isLABEL( currentExp ) ) {
				// ���� ��������� �����, �� ��� ��������� �� ������ ������ �����

				// ��������� ���������� ����
				_basicBlocks.push_back( currentBasicBlock );
				currentBasicBlock.Clear();
				currentBasicBlock.Label = dynamic_cast<const IRTree::LABEL*>( currentExp );
				isCleared = false;

			}
			else if ( isCJUMP( currentExp ) || isJUMP( currentExp ) ) {
				// ���� ��������� ������, �� �� ��������� ����
				currentBasicBlock.Jump = currentExp;
				_basicBlocks.push_back( currentBasicBlock );
				currentBasicBlock.Clear();
				isCleared = true;
			}
			else {
				// ����� ������ ��������� ���������� � ����
				currentBasicBlock.AddStatement( currentExp );
				isCleared = false;
			}

			// ��������� � ������ ���������
			list = list->GetTail();
		}
		// ���������� ����� ����� ��������
		if ( !isCleared ) {
			_basicBlocks.push_back( currentBasicBlock );
		}
	}

	void CCanon::connect() {
		// ������ ��� - �������
		if ( _basicBlocks.empty() ) {
			return;
		}

		const IStm* labelOfCurrentBlock = nullptr;
		const IStm* jumpOfCurrentBlock = nullptr;

		// ����� ��������� �� ����� ������, ������ �����
		auto& previousBlock = _basicBlocks.begin();
		auto& nextBlock = previousBlock + 1;

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
		if ( !previousBlock->Jump ) {
			previousBlock->Jump = new JUMP( _methodFrame->GetEpilogueLabel() );
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
			std::vector<CBasicBlock> currentTrace;

			// ����� ���������� �����
			CBasicBlock currentBlock = basicBlock;
			const Temp::CLabel* labelOfCurrentBlock = basicBlock.Label->GetLabel();

			// ���� �������� ������������ �����
			while ( !isBlockVisited[ labelOfCurrentBlock ] ) {
				// �������� ���� ���������� � ��������� ��� � ����� �����
				isBlockVisited[ labelOfCurrentBlock ] = true;
				currentTrace.push_back( currentBlock );

				// ��������� �����, ���� ����� ������� � ��������
				if ( currentBlock.GetJUMP() ) {
					const Temp::CLabel* jumpLabel = currentBlock.GetJUMP()->GetTargets()->GetHead();
				}
				else if ( currentBlock.GetCJUMP() ) {
					const Temp::CLabel* ifTrueLabel = currentBlock.GetCJUMP()->GetIfTrue();
					const Temp::CLabel* ifFalseLabel = currentBlock.GetCJUMP()->GetIfFalse();
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
			const IRTree::CJUMP* jumpStatement = basicBlock->GetCJUMP();
			if ( jumpStatement != nullptr ) {
				// �������� true � false �����
				const Temp::CLabel* falseLabel = jumpStatement->GetIfFalse();
				const Temp::CLabel* trueLabel = jumpStatement->GetIfFalse();

				// ��������� ����� ���������� �����
				const Temp::CLabel* nextBlockLabel = nextBasicBlock->Label->GetLabel();

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
					basicBlock->Jump = new CJUMP( operation, leftExpression, rightExpression, falseLabel, trueLabel );
				}
				else {
					// � ��������� ������ �� CJUMP ��� ���-�� ������ ������ - ��� ����� ��
					// ������ ��������������� ���� � ������ �����
					CBasicBlock newBlock;
					// ������ ����� �����
					const Temp::CLabel* newLabel = new Temp::CLabel();
					newBlock.Label = new IRTree::LABEL( newLabel );
					newBlock.Jump = new JUMP( jumpStatement->GetIfFalse() );

					// ������������ false-�����
					basicBlock->Jump = new CJUMP(
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

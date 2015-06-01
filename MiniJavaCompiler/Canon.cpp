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

			// Переходим к новому выражению
			list = list->GetTail();
		}
		irTreePrinter->CloseFile();
	}

	void CCanon::split() {
		_basicBlocks.clear();

		// Базовый блок
		CBasicBlock currentBasicBlock;
		currentBasicBlock.Clear();
		bool isCleared = true; // флаг, сбрасывающийся, как только мы добавили новую инструкцию

		// Начинаем перебор выражений
		const CStmList* list = _linearizedStatements;
		while ( list ) {

			const IStm* currentExp = list->GetHead();

			// Проверяем тип
			if ( isLABEL( currentExp ) ) {
				// Если встретили метку, то она указывает на начало нового блока

				// Завершаем предыдущий блок
				if( isCleared == false ) {
					_basicBlocks.push_back( currentBasicBlock );
					currentBasicBlock.Clear();
				}
				currentBasicBlock.Label = dynamic_cast<const IRTree::LABEL*>( currentExp );
				isCleared = false;

			} else if ( isCJUMP( currentExp ) || isJUMP( currentExp ) ) {
				// Если встретили прыжок, то он завершает блок
				currentBasicBlock.Jump = currentExp;
				_basicBlocks.push_back( currentBasicBlock );
				currentBasicBlock.Clear();
				isCleared = true;
			} else {
				// Иначе просто переносим инструкцию в блок
				currentBasicBlock.AddStatement( currentExp );
				isCleared = false;
			}

			// Переходим к новому выражению
			list = list->GetTail();
		}
		// Оставшийся хвост нужно добавить
		if ( !isCleared ) {
			_basicBlocks.push_back( currentBasicBlock );
		}
	}

	void CCanon::connect() {
		// Блоков нет - выходим
		if ( _basicBlocks.empty() ) {
			return;
		}

		const IStm* labelOfCurrentBlock = nullptr;
		const IStm* jumpOfCurrentBlock = nullptr;

		// Будем двигаться по парам блоков, изучая стыки
		auto& previousBlock = _basicBlocks.begin();
		auto& nextBlock = previousBlock + 1;

		// Если у первого блока отсутствует метка
		if ( !previousBlock->Label ) {
			// То берём её от фрейма
			previousBlock->Label = new LABEL( _methodFrame->GetStartLabel() );
		}

		// Пока не упёрлись в конец
		while ( nextBlock != _basicBlocks.end() ) {

			// Может быть три случая

			// Если предыдущий блок не имеет перехода, но есть метка в начале следующего
			if ( !previousBlock->Jump && nextBlock->Label ) {
				// То добавляем переход
				previousBlock->Jump = new JUMP( nextBlock->Label->GetLabel() );
			}
			// Если отсутствуем метка без перехода, то это ошибка в построении дерева
			else if ( previousBlock->Jump && !nextBlock->Label ) {
				throw( "Error by connecting basic blocks" );
			}
			// Третий случай, когда есть и метка, и переход нас не интересует, поскольку там всё в порядке.
			// Случай, когда нет ни метки, ни перехода не может быть априори (мы разбиваем на блоки именно по меткам и переходам)

			// Переходим к новой паре
			previousBlock++;
			nextBlock++;
		}

		// Если у последнего блока отсутствует переход, то мы должны создаём новый переход на эпилог функции (специальная метка)
		if ( !previousBlock->Jump ) {
			previousBlock->Jump = new JUMP( _methodFrame->GetEpilogueLabel() );
		}
	}

	void CCanon::generateTraces() {
		// Сюда будем хранить переупорядоченные блоки
		std::vector<CBasicBlock> reorderedBlocks;

		// Хранит флаги посещения блоков
		std::map<const Temp::CLabel*, bool> isBlockVisited;
		for ( auto& basicBlock : _basicBlocks ) {
			isBlockVisited[ basicBlock.Label->GetLabel() ] = false;
		}

		// Обходим все блоки
		for ( auto& basicBlock : _basicBlocks ) {
			// Создаём новый "след" (trace)
			std::vector<CBasicBlock> currentTrace;

			// Метка обходимого блока
			CBasicBlock currentBlock = basicBlock;
			const Temp::CLabel* labelOfCurrentBlock = basicBlock.Label->GetLabel();

			// Пока остались непосещённые блоки
			while ( !isBlockVisited[ labelOfCurrentBlock ] ) {
				// Помечает блок посещённым и добавляет его в конец следа
				isBlockVisited[ labelOfCurrentBlock ] = true;
				currentTrace.push_back( currentBlock );

				// Проверяем блоки, куда можно перейти с текущего
				if ( currentBlock.GetJUMP() ) {
					const Temp::CLabel* jumpLabel = currentBlock.GetJUMP()->GetTargets()->GetHead();
				}
				else if ( currentBlock.GetCJUMP() ) {
					const Temp::CLabel* ifTrueLabel = currentBlock.GetCJUMP()->GetIfTrue();
					const Temp::CLabel* ifFalseLabel = currentBlock.GetCJUMP()->GetIfFalse();
				}

			}

			// Закрывает след, перенеся все элементы в конечный список
			reorderedBlocks.insert( reorderedBlocks.end(), currentTrace.begin(), currentTrace.end() );
			currentTrace.clear();
		}

		// Переносим блоки
		_basicBlocks.clear();
		_basicBlocks = std::vector<CBasicBlock>( reorderedBlocks );
	}

	void CCanon::optimizeCJUMPBlocks() {
		// Перебираем все блоки 
		for ( std::vector<CBasicBlock>::iterator basicBlock = _basicBlocks.begin(), nextBasicBlock = _basicBlocks.begin() + 1;
			nextBasicBlock != _basicBlocks.end();
			basicBlock++, nextBasicBlock++
			) {
			// Если блок заканчивается CJUMP'ом
			const IRTree::CJUMP* jumpStatement = basicBlock->GetCJUMP();
			if ( jumpStatement != nullptr ) {
				// Получаем true и false метки
				const Temp::CLabel* falseLabel = jumpStatement->GetIfFalse();
				const Temp::CLabel* trueLabel = jumpStatement->GetIfFalse();

				// Проверяем метку следующего блока
				const Temp::CLabel* nextBlockLabel = nextBasicBlock->Label->GetLabel();

				// Если falsе-блок уже идёт за CJUMP-ом - просто продолжаем цикл
				if ( nextBlockLabel == falseLabel ) {
					continue;
				}
				// Если идёт true-метка - мы меняем местами метки true и false и делаем отрицание условия
				else if ( nextBlockLabel == trueLabel ) {
					const IRTree::IExp *leftExpression = jumpStatement->GetLeft();
					const IRTree::IExp *rightExpression = jumpStatement->GetRight();
					IRTree::TCJump operation;
					basicBlock->Jump = new CJUMP( jumpStatement->GetNegRelop(), leftExpression, rightExpression, falseLabel, trueLabel );
				}
				else {
					// В противном случае за CJUMP идёт что-то вообще другое - для этого мы
					// создаём вспомогательный блок с пустым телом
					CBasicBlock newBlock;
					// Создаём новую метку
					const Temp::CLabel* newLabel = new Temp::CLabel();
					newBlock.Label = new IRTree::LABEL( newLabel );
					newBlock.Jump = new JUMP( jumpStatement->GetIfFalse() );

					// Перевешиваем false-метку
					basicBlock->Jump = new CJUMP(
						jumpStatement->GetRelop(),
						jumpStatement->GetLeft(),
						jumpStatement->GetRight(),
						jumpStatement->GetIfTrue(),
						newLabel
						);

					// Вставляем новый блок в последовательность
					auto insertedBlockIterator = _basicBlocks.insert( nextBasicBlock, newBlock );
					// Переопределяем счётчики
					basicBlock = insertedBlockIterator;
					nextBasicBlock = insertedBlockIterator + 1;
				}
			}
		}
	}

	void CCanon::translateToStatements() {
		// Список операций
		std::list<const IRTree::IStm*> statements;
		
		// Перебираем пары блоков
		auto basicBlock = _basicBlocks.begin();
		auto nextBasicBlock = basicBlock + 1;

		
		// Сразу добавляем в начало метку первого блока и его инструкции

		while ( nextBasicBlock != _basicBlocks.end() ) {
			// Добавляем инструкции первого блока
			for ( auto block : basicBlock->FlowStatements ) {
				statements.push_back( block );
			}

			// Смотрим, что находится на стыке блоков. Если первый блок завершается JUMP'ом на метку,
			// которая идёт на следующий блок - удаляем таковые как ненужные
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

			// Проверяем, что 
			basicBlock++;
			nextBasicBlock++;
		}
		// Добавляем в конец инструкции и переход последнего блока
		for ( auto block : basicBlock->FlowStatements ) {
			statements.push_back( block );
		}
		statements.push_back( basicBlock->Jump );

		// Теперь список из IStm переводим в CStmList
		// Строим с конца
		const CStmList* list = nullptr;
		for ( auto statement = statements.rbegin(); statement != statements.rend(); statement++ ) {
			list = new CStmList( *statement, list );
		}
		_canonizedStatementsList = list;
	}
}

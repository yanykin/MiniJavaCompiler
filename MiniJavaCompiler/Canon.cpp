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
		// что есть дети Stm?? уже в дереве или где?
		//StmExpList x = reorder( s.kids() );
		//return seq( x.stm, s.build( x.exps ) );
		return nullptr;
	}

	const ESEQ* reorder_exp( const IExp* e )
	{
		// что есть дети Exp?? уже в дереве или где?
		//StmExpList x = reorder( e.kids() );
		//return new Tree.ESEQ( x.stm, e.build( x.exps ) );
		return nullptr;
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
	const CStmList* CCanon::Linearize( const IStm* statement ) {
		return linearize( statement );
	}

	// === CBasicBlocks ===
	CBasicBlocks::CBasicBlocks( const CStmList* blocks ) {

	}

	void CBasicBlocks::split( const CStmList* statements ) {
		// Сбрасываем буфер
		buffer.Clear();

		// Начинаем перебор выражений
		const IStm* currentExp = statements->GetHead();
		while ( currentExp ) {

			// Проверяем тип
			if ( isLABEL( currentExp ) ) {
				// Если встретили метку, то она указывает на начало нового блока

				// Завершаем предыдущий блок
				foundBlocks.push_back( buffer );
				buffer.Clear();
				buffer.Label = dynamic_cast<const IRTree::LABEL*>( currentExp );

			} else if ( isCJUMP( currentExp ) || isJUMP( currentExp ) ) {
				// Если встретили прыжок, то он завершает блок
				buffer.Jump = currentExp;
				foundBlocks.push_back( buffer );
				buffer.Clear();
			}
			else {
				// Иначе просто переносим инструкцию в блок
				buffer.AddStatement( currentExp );
			}

			// Переходим к новому выражению
			const CStmList* tail = statements->GetTail();
			if ( tail ) {
				currentExp = tail->GetHead();
			}
		}
		
	}

	void CBasicBlocks::connectBlocks( const Frame::CFrame* methodFrame ) {
		const IStm* labelOfCurrentBlock = nullptr;
		const IStm* jumpOfCurrentBlock = nullptr;

		// Будем двигаться по парам блоков, изучая стыки
		auto& previousBlock = foundBlocks.begin();
		auto& nextBlock = (foundBlocks.begin())++;

		// Если у первого блока отсутствует метка
		if ( !previousBlock->Label ) {
			// То берём её от фрейма
			previousBlock->Label = new LABEL( methodFrame->GetStartLabel() );
		}

		// Пока не упёрлись в конец
		while ( nextBlock != foundBlocks.end() ) {

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
		if ( !nextBlock->Jump ) {
			nextBlock->Jump = new JUMP( methodFrame->GetEpilogueLabel() );
		}
	}

	// === CTraceSchedule ===
	CTraceSchedule::CTraceSchedule( std::vector<CBasicBlock>& basicBlocks ) {
		for ( auto& basicBlock : basicBlocks ) {
			labelToBlock[ basicBlock.Label ] = &basicBlock;
		}
	}

	void CTraceSchedule::generateTraces( std::vector<CBasicBlock>& basicBlocks ) {
		// Хранит флаги посещения блоков
		std::map<const Temp::CLabel*, bool> isBlockVisited;
		for ( auto& basicBlock : basicBlocks ) {
			isBlockVisited[ basicBlock.Label ] = false;
		}

		// Обходим все блоки
		for ( auto& basicBlock : basicBlocks ) {
			// Создаём новый "след" (trace)
			std::vector<CBasicBlock*> currentTrace;

			// Метка обходимого блока
			CBasicBlock* currentBlock = &basicBlock;
			const Temp::CLabel* labelOfCurrentBlock = basicBlock.Label->GetLabel();

			// Пока остались непосещённые блоки
			while ( !isBlockVisited[ labelOfCurrentBlock ] ) {
				// Помечает блок посещённым и добавляет его в конец следа
				isBlockVisited[ labelOfCurrentBlock ] = true;
				currentTrace.push_back( currentBlock );

				// Проверяем блоки, куда можно перейти с текущего
				if ( currentBlock->GetJUMP() ) {
					const Temp::CLabel* jumpLabel = currentBlock->GetJUMP()->GetTargets()->GetHead();
				}
				else if ( currentBlock->GetCJUMP() ) {
					const Temp::CLabel* ifTrueLabel = currentBlock->GetCJUMP()->GetIfTrue();
					const Temp::CLabel* ifTrueLabel = currentBlock->GetCJUMP()->GetIfFalse();
				}
					
			}


			// Закрывает след, перенеся все элементы в конечный список
			reorderedBlocks.insert( reorderedBlocks.end(), currentTrace.begin(), currentTrace.end() );
			currentTrace.clear();
		}
	}
}

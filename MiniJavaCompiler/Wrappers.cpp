#include "Wrappers.h"
#include "Temp.h"

using namespace Translate;

// return CONST(0) or CONST(1) 
const IRTree::IExp* CConditionalWrapper::ToExp() const
{
	Temp::CTemp* temp = new Temp::CTemp();
	IRTree::TEMP* retValue = new IRTree::TEMP( temp );

	IRTree::MOVE* moveTrue = new IRTree::MOVE( retValue, new IRTree::CONST( 1 ) );
	IRTree::MOVE* moveFalse = new IRTree::MOVE( retValue, new IRTree::CONST( 0 ) );

	Temp::CLabel* trueLabel = new Temp::CLabel();
	Temp::CLabel* falseLabel = new Temp::CLabel();
	Temp::CLabel* endLabel = new Temp::CLabel();

	return new IRTree::ESEQ( new IRTree::SEQ
		( new IRTree::SEQ
			( new IRTree::SEQ
				( new IRTree::SEQ
					// условие
					( ToConditional( trueLabel, falseLabel ),
					// блок true
					new IRTree::SEQ( new IRTree::LABEL( trueLabel ), moveTrue ) ),
					new IRTree::JUMP( endLabel ) ),
					// блок false
					new IRTree::SEQ( new IRTree::LABEL( falseLabel ), moveFalse ) ),
					new IRTree::LABEL( endLabel ) ),
					// возвращаем значение
					retValue );
}

// return Stm
const IRTree::IStm* CConditionalWrapper::ToStm() const
{
	Temp::CLabel* tempLabel = new Temp::CLabel();
	const IRTree::IStm* cond = ToConditional( tempLabel, tempLabel );
	return new IRTree::SEQ( cond, new IRTree::LABEL( tempLabel ) );
}

// умный "И", если первый IExp == false сразу выходим
const IRTree::IStm* CFromAndConverter::ToConditional( const Temp::CLabel* ifTrue, const Temp::CLabel* ifFalse ) const
{
	Temp::CLabel* firstTrueLabel = new Temp::CLabel();
	IRTree::CJUMP* firstTrueJump = new IRTree::CJUMP( IRTree::CJ_NE, _leftArg, new IRTree::CONST( 0 ), firstTrueLabel, ifFalse );
	IRTree::CJUMP* secondTrueJump = new IRTree::CJUMP( IRTree::CJ_NE, _rightArg, new IRTree::CONST( 0 ), ifTrue, ifFalse );
	return new IRTree::SEQ( firstTrueJump, new IRTree::SEQ( new IRTree::LABEL( firstTrueLabel ), secondTrueJump ) );
}


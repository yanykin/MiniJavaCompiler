#include "Wrappers.h"
#include "Temp.h"

using namespace Translate;
/*
const IRTree::IStm* CExpConverter::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const
{
	пример:
	if ( a < b && c < d ) {
		// true block
	} else {
		// false block
	}


	приблизительный код:
	IRTree::IExp *first, *second, *nextExp;
	IRTree::TCJump op;
	CExpConverter* next = new CExpConverter( nextExp );
	Temp::CLabel* z = new Temp::CLabel();
	return new IRTree::SEQ( new IRTree::CJUMP( op, first, second, z, f ), new IRTree::SEQ( new IRTree::LABEL( z ), next->ToConditional( t, f ) ) );
}
*/
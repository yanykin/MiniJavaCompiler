#include "Translate.h"
#include "Temp.h"

using namespace Translate;

const IRTree::IStm* CExpConverter::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const
{
	/*пример для выражения:

	if ( a < b && c < d ) {
		// true block
	} else {
		// false block
	}
	
	*/
	// TODO: получить соотственно все Exp и знаки
	Temp::CLabel* z = new Temp::CLabel();
	IRTree::IExp *a, *b, *c, *d;
	return new IRTree::SEQ( new IRTree::CJUMP( IRTree::CJ_LT, a, b, z, f ), new IRTree::SEQ( new IRTree::LABEL( z ), new IRTree::CJUMP( IRTree::CJ_LT, c, d, t, f ) ) );
}
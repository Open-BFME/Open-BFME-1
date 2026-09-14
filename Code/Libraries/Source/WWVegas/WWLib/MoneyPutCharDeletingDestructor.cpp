// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: money_put<char, ostreambuf_iterator<char> > scalar-deleting
// destructor at retail 0x00832330 (30 bytes).  Vtable 0x0112E96C has the
// matched long-double do_put body at 0x00836050 in MoneyPutCharLongDouble.cpp;
// its slot zero is this destructor and slot one is the matched string overload.

#include "stlport_prefix.h"
#include <stl/_monetary.h>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<char, char_traits<char> > BfmeMoneyPutCharIterator;
typedef money_put<char, BfmeMoneyPutCharIterator> BfmeMoneyPutChar;

template class money_put<char, BfmeMoneyPutCharIterator>;

_STLP_END_NAMESPACE

void Force_BfmeMoneyPutChar_Deleting_Destructor()
{
}

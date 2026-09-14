// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: money_put<unsigned short, ostreambuf_iterator<unsigned short> >
// scalar-deleting destructor at retail 0x008323F0 (30 bytes). Retail RTTI
// identifies vtable 0x0112E9E8 as this exact specialization; slot zero is
// this wrapper and the adjacent complete destructor is at 0x00832410.

#include "stlport_prefix.h"
#include <stl/_monetary.h>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > BfmeMoneyPutWideIterator;

template class money_put<wchar_t, BfmeMoneyPutWideIterator>;

_STLP_END_NAMESPACE

void Force_BfmeMoneyPutWide_Deleting_Destructor()
{
}

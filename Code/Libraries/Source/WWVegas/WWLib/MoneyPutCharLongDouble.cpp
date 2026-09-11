// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 money_put<char, ostreambuf_iterator<char> >::do_put(long
// double), retail 0x00836050.  The canonical inline body lives in
// stl/_monetary.h.  This is a STLport-library instantiation, so the vendor
// prefix exposes the allocator implementation that retail inlined.
//
// BFME's locale release is also inline at the end of this body.  STLport's
// public header deliberately leaves _Locale_impl opaque, so complete its
// three-slot ABI here before asking VC7.1 to instantiate the facet method.

#include "stlport_prefix.h"
#include <stl/_monetary.h>

_STLP_BEGIN_NAMESPACE

class _Locale_impl
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_increment(void) = 0;
	virtual void _bfme_decrement(void) = 0;
};

inline locale::~locale()
{
	_M_impl->_bfme_decrement();
}

typedef ostreambuf_iterator<char, char_traits<char> > BfmeMoneyPutCharIterator;

template BfmeMoneyPutCharIterator
money_put<char, BfmeMoneyPutCharIterator>::do_put(
	BfmeMoneyPutCharIterator, bool, ios_base &, char, long double) const;

_STLP_END_NAMESPACE

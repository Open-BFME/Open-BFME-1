// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GO@Z
// partial score=0.99 date=2026-09-16
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 money_put<wchar_t, ostreambuf_iterator<wchar_t> >::do_put(long
// double), retail 0x00836140.  The canonical inline body lives in
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

// Retail reaches the node allocator through a call here rather than inlining
// it the way the narrow twin at 0x00836050 does.  Keeping deallocate out of
// line is also what lets VC7.1 inline the wide string destructor into this
// body, which is the shape retail shows.
// ?deallocate@?$__node_alloc@$00$0A@@_STL@@SAXPAXI@Z
template <>
__declspec(noinline)
void __node_alloc<true, 0>::deallocate(void *p, size_t n) throw()
{
	if (n > (size_t)_MAX_BYTES)
		__stl_delete(p);
	else
		_M_deallocate(p, n);
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > BfmeMoneyPutWideIterator;

template BfmeMoneyPutWideIterator
money_put<wchar_t, BfmeMoneyPutWideIterator>::do_put(
	BfmeMoneyPutWideIterator, bool, ios_base &, wchar_t, long double) const;

_STLP_END_NAMESPACE

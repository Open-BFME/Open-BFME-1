// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GO@Z
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

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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

// Retail's FuncInfo at VA 0x01243F20 has three cleanup states: locale,
// allocator temporary, and wide string. An empty in-class allocator destructor
// loses its EH state in VC7.1. The instruction-free barrier retains that
// lifetime without introducing a normal-path destructor call.
template <>
allocator<wchar_t>::~allocator() _STLP_NOTHROW
{
	_ReadWriteBarrier();
}

inline locale::~locale()
{
	_M_impl->_bfme_decrement();
}

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

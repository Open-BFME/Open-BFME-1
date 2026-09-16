// ?do_put@?$money_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@_NAAVios_base@2@DABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@@Z
// partial score=0.21 date=2026-09-16
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// STLport 4.5.3 money_put<char, ostreambuf_iterator<char> >::do_put(digits).
// The retail body is slot 1 of the vtable at VA 0x0112E96C, whose RTTI complete
// object locator names the narrow money_put.  MSVC writes an overload set into
// a vtable backwards, so slot 1 holds the second do_put that
// vendor/stlport/stl/_monetary.h declares and that overload writes a string.

#include "stlport_prefix.h"

#include <stl/_monetary.h>

_STLP_BEGIN_NAMESPACE

// Retail inlines the locale destructor here, so its body has to be visible.
// It matches the landed 0x00832170 body, which drops the impl reference
// through vtable slot 2.
class _Locale_impl
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_incr(void) = 0;
	virtual void _bfme_decr(void) = 0;
};

__forceinline locale::~locale() _STLP_NOTHROW
{
	_M_impl->_bfme_decr();
}

typedef ostreambuf_iterator<char, char_traits<char> > BfmeNarrowPutIterator;

template BfmeNarrowPutIterator
money_put<char, BfmeNarrowPutIterator>::do_put(BfmeNarrowPutIterator,
					       bool,
					       ios_base &,
					       char,
					       const string &) const;

_STLP_END_NAMESPACE

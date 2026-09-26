// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// STLport 4.5.3 num_get<wchar_t, istreambuf_iterator<wchar_t> >::do_get(bool&).
// The retail body is slot 11 of the vtable at VA 0x0112E9F8, whose RTTI
// complete object locator names the wide num_get.  MSVC writes an overload set
// into the vtable backwards, so slot 11 holds the first do_get declared in
// inputs/vendor/stlport/stl/_num_get.h and that one reads a bool.  The narrow twin
// sits in stlport_num_get_bool.cpp, which cannot host this one because retail
// inlines the node allocator there and calls it here.
//
// The body itself is the vendored template in inputs/vendor/stlport/stl/_num_get.c.
// Retail calls equal, _M_getc and sbumpc out of line, so the vendored
// istreambuf_iterator is replaced with a model that declares those three and
// leaves them to the link.

// Retail calls sbumpc out of line.  The narrow basic_streambuf is a full
// class specialization, so the only way to keep its inline members out of this
// body is to read the header with automatic inlining switched off.
#define __BUILDING_STLPORT 1
#define _STLP_REAL_LOCALE_IMPLEMENTED
#include <stl/_config.h>
#include <stl/_ios_base.h>
#include <stl/_stdio_file.h>
#pragma auto_inline(off)
#include <stl/_streambuf.h>
_STLP_BEGIN_NAMESPACE
// The wide streambuf comes from the primary template, which the pragma above
// does not reach, so its sbumpc is specialized here and left to the link.
template <>
__declspec(noinline) char_traits<wchar_t>::int_type
basic_streambuf<wchar_t, char_traits<wchar_t> >::sbumpc();
_STLP_END_NAMESPACE
#pragma auto_inline(on)

#include "stlport_prefix.h"

#include <stl/_string.h>
#include <stl/_ios_base.h>
#include <stl/_numpunct.h>

#define _STLP_INTERNAL_ISTREAMBUF_ITERATOR_H

_STLP_BEGIN_NAMESPACE

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	typedef CharT char_type;
	typedef Traits traits_type;
	typedef basic_streambuf<CharT, Traits> streambuf_type;

	__declspec(noinline) bool equal(const istreambuf_iterator &__i) const
	{
		if (this->_M_buf)
			this->_M_getc();
		if (__i._M_buf)
			__i._M_getc();
		return this->_M_eof == __i._M_eof;
	}

	CharT operator*() const { this->_M_getc(); return _M_c; }
	istreambuf_iterator &operator++()
	{
		_M_buf->sbumpc();
		_M_have_c = false;
		return *this;
	}

public:
	__declspec(noinline) void _M_getc() const
	{
		if (_M_have_c)
			return;
		typename Traits::int_type __c = _M_buf->sgetc();
		_M_c = Traits::to_char_type(__c);
		_M_eof = Traits::eq_int_type(__c, Traits::eof());
		_M_have_c = true;
	}

	streambuf_type *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
inline bool operator==(const istreambuf_iterator<CharT, Traits> &x,
		       const istreambuf_iterator<CharT, Traits> &y)
{
	return x.equal(y);
}

template <class CharT, class Traits>
inline bool operator!=(const istreambuf_iterator<CharT, Traits> &x,
		       const istreambuf_iterator<CharT, Traits> &y)
{
	return !x.equal(y);
}

_STLP_END_NAMESPACE

#include <stl/_num_get.h>

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

// Retail reaches the node allocator through a call in the wide string
// destructor here, while the narrow twin inlines it.  Keeping deallocate out
// of line is what reproduces that call.
template <>
__declspec(noinline)
void __node_alloc<true, 0>::deallocate(void *p, size_t n) throw()
{
	if (n > (size_t)_MAX_BYTES)
		__stl_delete(p);
	else
		_M_deallocate(p, n);
}

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > BfmeWideGetIterator;

template BfmeWideGetIterator
num_get<wchar_t, BfmeWideGetIterator>::do_get(BfmeWideGetIterator,
					      BfmeWideGetIterator,
					      ios_base &,
					      ios_base::iostate &,
					      bool &) const;

_STLP_END_NAMESPACE

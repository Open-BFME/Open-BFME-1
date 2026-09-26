// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// STLport 4.5.3 money_get<char, istreambuf_iterator<char> >::do_get(long
// double&).  The retail body is slot 2 of the vtable at VA 0x0112E95C, whose
// RTTI complete object locator names the narrow money_get.  MSVC writes an
// overload set into a vtable backwards, so slot 2 holds the first do_get that
// inputs/vendor/stlport/stl/_monetary.h declares and that overload reads a long
// double.  It reads the digits through the sibling slot and then converts.
// Retail inlines equal here and calls _M_getc, which is the opposite of what
// the num_get bool readers show, so only _M_getc carries the noinline mark.

#define __BUILDING_STLPORT 1
#define _STLP_REAL_LOCALE_IMPLEMENTED
#include <stl/_config.h>
#include <stl/_ios_base.h>
#include <stl/_stdio_file.h>
#pragma auto_inline(off)
#include <stl/_streambuf.h>
#pragma auto_inline(on)

#include "stlport_prefix.h"

#include <stl/_string.h>
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

	istreambuf_iterator(streambuf_type * = 0);

	bool equal(const istreambuf_iterator &__i) const
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

#include <stl/_monetary.h>

_STLP_BEGIN_NAMESPACE

typedef istreambuf_iterator<char, char_traits<char> > BfmeNarrowGetIterator;

template BfmeNarrowGetIterator
money_get<char, BfmeNarrowGetIterator>::do_get(BfmeNarrowGetIterator,
					       BfmeNarrowGetIterator,
					       bool,
					       ios_base &,
					       ios_base::iostate &,
					       long double &) const;

_STLP_END_NAMESPACE

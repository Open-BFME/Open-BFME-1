// cl: /Od /Oi /Ob2 /DNDEBUG /MD /EHsc-

/*
 * Copyright (c) 1997-1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

// Open-BFME: STLport basic_string<char>::copy, retail 0x0082C490, 152 bytes.
// The retail body is the STLport member in vendor/stlport/stl/_string.h: it
// checks the position against size(), takes min(count, size() - position),
// copies the selected range with char_traits::copy, and returns its length.
// Its twelve-byte _String_base layout is established by the neighbouring
// STLport string constructors and reserve/append reconstructions.
//
// STLport's traits copy returns the destination pointer.  With the vendor
// conditional written below, the retail /Od body spills that discarded result
// to its second compiler temporary after the intrinsic copy.

extern "C" void *__cdecl memcpy(void *dest, const void *source,
	unsigned int count);
#pragma intrinsic(memcpy)

namespace _STL
{

template <class T>
class allocator
{
};

template <class T>
class char_traits
{
};

template <>
class char_traits<char>
{
public:
	static char *copy(char *dest, const char *source,
		unsigned int count)
	{
		return count == 0 ? dest : (char *)::memcpy(dest, source, count);
	}
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const Alloc &, Pointer data) : _M_data(data) {}

	Pointer _M_data;
};

template <class T, class Alloc>
class _String_base
{
public:
	typedef allocator<T> allocator_type;

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;

	void _M_throw_out_of_range(void) const;
};

template <class CharT, class Traits, class Alloc>
class basic_string : protected _String_base<CharT, Alloc>
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;

	size_type copy(CharT *dest, size_type count, size_type position) const;

	__forceinline size_type size(void) const
	{
		return (size_type)(this->_M_finish - this->_M_start);
	}

};

template <class T>
__forceinline const T &min(const T &left, const T &right)
{
	return right < left ? right : left;
}

template <class CharT, class Traits, class Alloc>
typename basic_string<CharT, Traits, Alloc>::size_type
basic_string<CharT, Traits, Alloc>::copy(CharT *dest, size_type count,
	size_type position) const
{
	if (position > size())
		this->_M_throw_out_of_range();

	const size_type __len = (min)(count, size() - position);
	Traits::copy(dest, this->_M_start + position, __len);
	return __len;
}

}

template unsigned _STL::basic_string<char, _STL::char_traits<char>,
	_STL::allocator<char> >::copy(char *, unsigned, unsigned) const;

typedef char RetailNarrowStringSize[(sizeof(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >) == 12) ? 1 : -1];

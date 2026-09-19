// ??0Rva00776240Vector54@@QAE@ABU0@@Z
// partial score=0.88 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport vector copy constructor at retail 0x0076CF20.

#include <new>
#include "../../../../../reference/shims/stringinline/StringInline.h"

struct Open2Elem7716A0
{
	int m_word00;
	int m_word04;
	int m_word08;
	AsciiString m_room0C;
	int m_word10;

	~Open2Elem7716A0();
};

namespace _STL
{
template <typename T> class allocator
{
	int value;
};

template <typename T, typename Alloc> struct _Vector_base
{
	_Vector_base(unsigned count, const Alloc &alloc);
	~_Vector_base();
	T *m_start;
	T *m_finish;
	T *m_storage;
};

}

struct Rva00776240Vector54
	: public _STL::_Vector_base<
		Open2Elem7716A0,
		_STL::allocator<Open2Elem7716A0> >
{
	typedef Open2Elem7716A0 T;
	typedef _STL::_Vector_base<
		Open2Elem7716A0,
		_STL::allocator<Open2Elem7716A0> > Base;
	typedef _STL::allocator<Open2Elem7716A0> allocator_type;

	allocator_type get_allocator() const;
	Rva00776240Vector54(const Rva00776240Vector54 &other);
};

Rva00776240Vector54::Rva00776240Vector54(
	const Rva00776240Vector54 &other)
	: Base(
		(unsigned int)(other.m_finish - other.m_start),
		other.get_allocator())
{
	T *end = other.m_finish;
	T *source = other.m_start;
	T *destination = m_start;
	while (source != end)
	{
		new (destination) T(*source);
		source++;
		destination++;
	}
	m_finish = destination;
}

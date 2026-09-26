// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport vector copy constructor at retail 0x0076D020.

#include <new>

struct Rva00776240Vector60Element
{
	int value[5];
	Rva00776240Vector60Element(const Rva00776240Vector60Element &);
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

void __cdecl BfmeElementConstruct(
	Rva00776240Vector60Element *destination,
	const Rva00776240Vector60Element &value);
}

struct Rva00776240Vector60
	: public _STL::_Vector_base<
		Rva00776240Vector60Element,
		_STL::allocator<Rva00776240Vector60Element> >
{
	typedef Rva00776240Vector60Element T;
	typedef _STL::_Vector_base<
		Rva00776240Vector60Element,
		_STL::allocator<Rva00776240Vector60Element> > Base;
	typedef _STL::allocator<Rva00776240Vector60Element> allocator_type;

	allocator_type get_allocator() const;
	Rva00776240Vector60(const Rva00776240Vector60 &other);
};

Rva00776240Vector60::Rva00776240Vector60(
	const Rva00776240Vector60 &other)
	: Base(
		(unsigned int)(other.m_finish - other.m_start),
		other.get_allocator())
{
	T *end = other.m_finish;
	T *source = other.m_start;
	T *destination = m_start;
	while (source != end)
	{
		_STL::BfmeElementConstruct(destination, *source);
		source++;
		destination++;
	}
	m_finish = destination;
}

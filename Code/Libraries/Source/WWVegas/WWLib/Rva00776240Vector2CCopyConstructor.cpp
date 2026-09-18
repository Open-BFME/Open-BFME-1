// The ILT at 0x0003EDFB names this body as the Rva00776240Vector2C copy
// constructor.  Gen_t_00776240_p128pod copies the member, and the 0x38-byte
// Rva00762170 element copy constructor supplies the loop's element ABI.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB

#include <new>

class Rva00762170
{
public:
	Rva00762170(const Rva00762170 &other);
	char m_body[0x38];
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

#pragma comment(linker, "/alternatename:??0?$_Vector_base@VRva00762170@@V?$allocator@VRva00762170@@@_STL@@@_STL@@QAE@IABV?$allocator@VRva00762170@@@1@@Z=?j_00018845@@YAXXZ")
#pragma comment(linker, "/alternatename:?get_allocator@Rva00776240Vector2C@@QBE?AV?$allocator@VRva00762170@@@_STL@@XZ=?j_00022255@@YAXXZ")

struct Rva00776240Vector2C
	: public _STL::_Vector_base<
		Rva00762170, _STL::allocator<Rva00762170> >
{
	typedef Rva00762170 T;
	typedef _STL::_Vector_base<
		Rva00762170, _STL::allocator<Rva00762170> > Base;
	typedef _STL::allocator<Rva00762170> allocator_type;

	allocator_type get_allocator() const;
	Rva00776240Vector2C(const Rva00776240Vector2C &other);
};

Rva00776240Vector2C::Rva00776240Vector2C(
	const Rva00776240Vector2C &other)
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

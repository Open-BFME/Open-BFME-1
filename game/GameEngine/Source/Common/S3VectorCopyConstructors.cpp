// stlport
#include <vector>

struct Gen_t_000bb4e0_p4cd { int a[1]; Gen_t_000bb4e0_p4cd(); Gen_t_000bb4e0_p4cd(const Gen_t_000bb4e0_p4cd&); ~Gen_t_000bb4e0_p4cd(); Gen_t_000bb4e0_p4cd& operator=(const Gen_t_000bb4e0_p4cd&); };
class Gen_000b9800 { public: int m(int); };
struct Gen_t_000cc740_p4cd { int a[1]; Gen_t_000cc740_p4cd(); Gen_t_000cc740_p4cd(const Gen_t_000cc740_p4cd&); ~Gen_t_000cc740_p4cd(); Gen_t_000cc740_p4cd& operator=(const Gen_t_000cc740_p4cd&); };
class Gen_000cc700 { public: int m(int); };
struct Gen_t_0036d7d0_p4cd { int a[1]; Gen_t_0036d7d0_p4cd(); Gen_t_0036d7d0_p4cd(const Gen_t_0036d7d0_p4cd&); ~Gen_t_0036d7d0_p4cd(); Gen_t_0036d7d0_p4cd& operator=(const Gen_t_0036d7d0_p4cd&); };
class Gen_0036c930 { public: int m(int); };
struct Gen_t_00585a70_p4cd { int a[1]; Gen_t_00585a70_p4cd(); Gen_t_00585a70_p4cd(const Gen_t_00585a70_p4cd&); ~Gen_t_00585a70_p4cd(); Gen_t_00585a70_p4cd& operator=(const Gen_t_00585a70_p4cd&); };
class Gen_005852f0 { public: int m(int); };
namespace _STL
{
template <> _Vector_base<Gen_t_000bb4e0_p4cd, allocator<Gen_t_000bb4e0_p4cd> >::_Vector_base(unsigned int, const allocator<Gen_t_000bb4e0_p4cd> &);
template <> _Vector_base<Gen_t_000cc740_p4cd, allocator<Gen_t_000cc740_p4cd> >::_Vector_base(unsigned int, const allocator<Gen_t_000cc740_p4cd> &);
template <> _Vector_base<Gen_t_0036d7d0_p4cd, allocator<Gen_t_0036d7d0_p4cd> >::_Vector_base(unsigned int, const allocator<Gen_t_0036d7d0_p4cd> &);
template <> _Vector_base<Gen_t_00585a70_p4cd, allocator<Gen_t_00585a70_p4cd> >::_Vector_base(unsigned int, const allocator<Gen_t_00585a70_p4cd> &);
}

// Four 76-byte vector copy constructors. Each asks the source for its
// allocator, hands the element count and that allocator to an allocate-and-copy
// member, and then copies the elements itself before writing the finish
// pointer.
//
// Three things are worth recording.
//
// The allocator comes back by value through a hidden return pointer, and the
// slot MSVC picks for it is the incoming argument's own stack slot -- the
// parameter is still live but its VALUE is already in a register, so the slot
// is free. That falls out on its own; nothing in the source asks for it.
//
// The allocate-and-copy result is never read. The loop reads this->start back
// out of the object instead, which is what says that member writes into this
// rather than returning the block.
//
// The copy loop DOES have a null test in front of it, so unlike the assignment
// loops at 0x000B0290 this one really is placement new -- the elements do not
// exist yet.
//
// Both the source's finish pointer and its start have to be held in locals, in
// that order. Left as member reads the compare goes against memory and the
// body comes out three bytes longer.

class Gen_000bb890
{
public:
	Gen_000bb890(const Gen_000bb890 &other);

private:

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

class Gen_000ce890
{
public:
	Gen_000ce890(const Gen_000ce890 &other);

private:

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

class Gen_0036e170
{
public:
	Gen_0036e170(const Gen_0036e170 &other);

private:

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

class Gen_005862c0
{
public:
	Gen_005862c0(const Gen_005862c0 &other);

private:

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

// ??0Gen_000bb890@@QAE@ABV0@@Z
Gen_000bb890::Gen_000bb890(const Gen_000bb890 &other)
{
	_STL::allocator<Gen_t_000bb4e0_p4cd> allocatorSlot;
	reinterpret_cast<_STL::_Vector_base<Gen_t_000bb4e0_p4cd, _STL::allocator<Gen_t_000bb4e0_p4cd> > *>(this)->_STL::_Vector_base<Gen_t_000bb4e0_p4cd, _STL::allocator<Gen_t_000bb4e0_p4cd> > ::_Vector_base(
		(unsigned int)(other.m_bfmeFinish - other.m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_000bb4e0_p4cd> *>(
			reinterpret_cast<Gen_000b9800 *>(const_cast<Gen_000bb890 *>(&other))->m(
				reinterpret_cast<int>(&allocatorSlot))));

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// ??0Gen_000ce890@@QAE@ABV0@@Z
Gen_000ce890::Gen_000ce890(const Gen_000ce890 &other)
{
	_STL::allocator<Gen_t_000cc740_p4cd> allocatorSlot;
	reinterpret_cast<_STL::_Vector_base<Gen_t_000cc740_p4cd, _STL::allocator<Gen_t_000cc740_p4cd> > *>(this)->_STL::_Vector_base<Gen_t_000cc740_p4cd, _STL::allocator<Gen_t_000cc740_p4cd> > ::_Vector_base(
		(unsigned int)(other.m_bfmeFinish - other.m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_000cc740_p4cd> *>(
			reinterpret_cast<Gen_000cc700 *>(const_cast<Gen_000ce890 *>(&other))->m(
				reinterpret_cast<int>(&allocatorSlot))));

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// ??0Gen_0036e170@@QAE@ABV0@@Z
Gen_0036e170::Gen_0036e170(const Gen_0036e170 &other)
{
	_STL::allocator<Gen_t_0036d7d0_p4cd> allocatorSlot;
	reinterpret_cast<_STL::_Vector_base<Gen_t_0036d7d0_p4cd, _STL::allocator<Gen_t_0036d7d0_p4cd> > *>(this)->_STL::_Vector_base<Gen_t_0036d7d0_p4cd, _STL::allocator<Gen_t_0036d7d0_p4cd> > ::_Vector_base(
		(unsigned int)(other.m_bfmeFinish - other.m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_0036d7d0_p4cd> *>(
			reinterpret_cast<Gen_0036c930 *>(const_cast<Gen_0036e170 *>(&other))->m(
				reinterpret_cast<int>(&allocatorSlot))));

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// ??0Gen_005862c0@@QAE@ABV0@@Z
Gen_005862c0::Gen_005862c0(const Gen_005862c0 &other)
{
	_STL::allocator<Gen_t_00585a70_p4cd> allocatorSlot;
	reinterpret_cast<_STL::_Vector_base<Gen_t_00585a70_p4cd, _STL::allocator<Gen_t_00585a70_p4cd> > *>(this)->_STL::_Vector_base<Gen_t_00585a70_p4cd, _STL::allocator<Gen_t_00585a70_p4cd> > ::_Vector_base(
		(unsigned int)(other.m_bfmeFinish - other.m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_00585a70_p4cd> *>(
			reinterpret_cast<Gen_005852f0 *>(const_cast<Gen_005862c0 *>(&other))->m(
				reinterpret_cast<int>(&allocatorSlot))));

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// stlport
#include <vector>

struct Gen_t_000955c0_p8cd { int a[2]; Gen_t_000955c0_p8cd(); Gen_t_000955c0_p8cd(const Gen_t_000955c0_p8cd&); ~Gen_t_000955c0_p8cd(); Gen_t_000955c0_p8cd& operator=(const Gen_t_000955c0_p8cd&); };
class Gen_00095130 { public: int m(int); };
struct Gen_t_000b5370_p8cd { int a[2]; Gen_t_000b5370_p8cd(); Gen_t_000b5370_p8cd(const Gen_t_000b5370_p8cd&); ~Gen_t_000b5370_p8cd(); Gen_t_000b5370_p8cd& operator=(const Gen_t_000b5370_p8cd&); };
class Gen_000b5200 { public: int m(int); };
struct Gen_t_003a8c60_p8cd { int a[2]; Gen_t_003a8c60_p8cd(); Gen_t_003a8c60_p8cd(const Gen_t_003a8c60_p8cd&); ~Gen_t_003a8c60_p8cd(); Gen_t_003a8c60_p8cd& operator=(const Gen_t_003a8c60_p8cd&); };
class Gen_003a63c0 { public: int m(int); };
namespace _STL
{
template <> _Vector_base<Gen_t_000955c0_p8cd, allocator<Gen_t_000955c0_p8cd> >::_Vector_base(unsigned int, const allocator<Gen_t_000955c0_p8cd> &);
template <> _Vector_base<Gen_t_000b5370_p8cd, allocator<Gen_t_000b5370_p8cd> >::_Vector_base(unsigned int, const allocator<Gen_t_000b5370_p8cd> &);
template <> _Vector_base<Gen_t_003a8c60_p8cd, allocator<Gen_t_003a8c60_p8cd> >::_Vector_base(unsigned int, const allocator<Gen_t_003a8c60_p8cd> &);
}

// Three vector assignments, 0x00095A50, 0x000B54C0 and 0x003A9560 (0x002F8980
// is the SolutionVec copy constructor, SolutionVecCopyConstructor.cpp).
//
// The first call is entered with the source as this and the ADDRESS OF THE
// PARAMETER SLOT as its argument -- there is no sub esp, so that address can
// only be the parameter itself. That is a reference-to-pointer parameter on
// the callee, not a local.
//
// The element count is (finish - start) >> 3, so the elements are eight bytes
// wide, and the bounds are re-read from the source after the reserve call.
// The copy walks two independent pointers rather than recomputing the
// destination, and the null test in front of each element is placement-new
// codegen. The finish pointer is written from the cursor at the end and this
// is handed back.

struct BfmePair
{
	BfmePair(const BfmePair &other)
	{
		m_bfmeFirst = other.m_bfmeFirst;
		m_bfmeSecond = other.m_bfmeSecond;
	}

	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct BfmeVectorRange
{
	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};


class Gen_00095A50
{
public:
	Gen_00095A50 *bfmeAssign(BfmeVectorRange *source);

private:

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

class Gen_000B54C0
{
public:
	Gen_000B54C0 *bfmeAssign(BfmeVectorRange *source);

private:

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

class Gen_003A9560
{
public:
	Gen_003A9560 *bfmeAssign(BfmeVectorRange *source);

private:

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

// ?bfmeAssign@Gen_00095A50@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_00095A50 *Gen_00095A50::bfmeAssign(BfmeVectorRange *source)
{
	_STL::allocator<Gen_t_000955c0_p8cd> allocatorSlot;
	void *grabbed = reinterpret_cast<void *>(reinterpret_cast<Gen_00095130 *>(source)->m(
		reinterpret_cast<int>(&allocatorSlot)));

	reinterpret_cast<_STL::_Vector_base<Gen_t_000955c0_p8cd, _STL::allocator<Gen_t_000955c0_p8cd> > *>(this)->_STL::_Vector_base<Gen_t_000955c0_p8cd, _STL::allocator<Gen_t_000955c0_p8cd> > ::_Vector_base(
		(unsigned int)(source->m_bfmeFinish - source->m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_000955c0_p8cd> *>(grabbed));

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}

// ?bfmeAssign@Gen_000B54C0@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_000B54C0 *Gen_000B54C0::bfmeAssign(BfmeVectorRange *source)
{
	_STL::allocator<Gen_t_000b5370_p8cd> allocatorSlot;
	void *grabbed = reinterpret_cast<void *>(reinterpret_cast<Gen_000b5200 *>(source)->m(
		reinterpret_cast<int>(&allocatorSlot)));

	reinterpret_cast<_STL::_Vector_base<Gen_t_000b5370_p8cd, _STL::allocator<Gen_t_000b5370_p8cd> > *>(this)->_STL::_Vector_base<Gen_t_000b5370_p8cd, _STL::allocator<Gen_t_000b5370_p8cd> > ::_Vector_base(
		(unsigned int)(source->m_bfmeFinish - source->m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_000b5370_p8cd> *>(grabbed));

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}

// ?bfmeAssign@Gen_003A9560@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_003A9560 *Gen_003A9560::bfmeAssign(BfmeVectorRange *source)
{
	_STL::allocator<Gen_t_003a8c60_p8cd> allocatorSlot;
	void *grabbed = reinterpret_cast<void *>(reinterpret_cast<Gen_003a63c0 *>(source)->m(
		reinterpret_cast<int>(&allocatorSlot)));

	reinterpret_cast<_STL::_Vector_base<Gen_t_003a8c60_p8cd, _STL::allocator<Gen_t_003a8c60_p8cd> > *>(this)->_STL::_Vector_base<Gen_t_003a8c60_p8cd, _STL::allocator<Gen_t_003a8c60_p8cd> > ::_Vector_base(
		(unsigned int)(source->m_bfmeFinish - source->m_bfmeStart),
		*reinterpret_cast<const _STL::allocator<Gen_t_003a8c60_p8cd> *>(grabbed));

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}

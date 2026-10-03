// Two vector destroys that hand the range to a destroy helper.
//
// Each passes start, finish and the address of a one-byte local to the helper,
// then frees the block by size the same way the matching allocate chooses its
// allocator. That third argument is a lea into the four bytes the prologue
// reserved -- an uninitialised char whose address is all the callee wants.
//
// The element is four bytes wide, which the shift pair around the size names,
// and each arm of the size test carries its own epilogue.

void __cdecl operator delete(void *block);			// retail 0x00881EB0
static inline void bfmeRelease(void *block, unsigned int bytes);

class Rva000BB5D0Ref;
class ThingRefB;

namespace _STL
{
template <bool __threads, int __inst> class __node_alloc;
template <> class __node_alloc<true, 0>
{
	friend void ::bfmeRelease(void *block, unsigned int bytes);
	static void __cdecl _M_deallocate(void *block, unsigned int bytes);
};

struct __false_type;
// Retail ILTs 0x000247E9 and 0x000096FB route to these ledger-owned bodies
// at 0x000BB5D0 and 0x0069F100 respectively.
void __cdecl __destroy_aux(Rva000BB5D0Ref *first, Rva000BB5D0Ref *last,
	const __false_type &tag);
void __cdecl __destroy_aux(ThingRefB *first, ThingRefB *last,
	const __false_type &tag);
}

static inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		::operator delete(block);
	else
		_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
}

class Gen_000BCBC0
{
public:
	void bfmeDestroy(void);

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

// ?bfmeDestroy@Gen_000BCBC0@@QAEXXZ
void Gen_000BCBC0::bfmeDestroy(void)
{
	char tag;

	_STL::__destroy_aux(reinterpret_cast<Rva000BB5D0Ref *>(m_bfmeStart),
		reinterpret_cast<Rva000BB5D0Ref *>(m_bfmeFinish),
		*reinterpret_cast<const _STL::__false_type *>(&tag));

	int *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
}

class Gen_006A76E0
{
public:
	void bfmeDestroy(void);

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

// ?bfmeDestroy@Gen_006A76E0@@QAEXXZ
void Gen_006A76E0::bfmeDestroy(void)
{
	char tag;

	_STL::__destroy_aux(reinterpret_cast<ThingRefB *>(m_bfmeStart),
		reinterpret_cast<ThingRefB *>(m_bfmeFinish),
		*reinterpret_cast<const _STL::__false_type *>(&tag));

	int *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
}

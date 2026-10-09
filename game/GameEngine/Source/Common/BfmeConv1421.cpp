// cl: /Od

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

// The 0x0082ECD0 body's two allocators, by the names the ledger defines at
// those addresses. 0x0082E540 is stlport's __node_alloc<true, 0>::_M_allocate (162 bytes,
// matched at game/Libraries/Source/WWVegas/WWLib/STL_new_alloc_allocateThunk.cpp);
// 0x00037C54 is the five-byte ILT thunk ?j_00037c54@@YAXXZ, reached through a
// `void(void)` gen-thunk declaration, so the call goes through a cast that
// supplies the one stack argument retail pushes and reads eax back.
namespace _STL
{
	// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}
}

extern void j_00037c54();

typedef void *(*BfmeBigAllocVLV)(unsigned n);

struct BfmeHdrVLV
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void *bfmeAllocVLV(unsigned n)
{
	BfmeHdrVLV *n1;
	unsigned n3;
	unsigned n2;

	n3 = n + 0x18;
	if (n3 > 0x80)
		n2 = (unsigned)reinterpret_cast<BfmeBigAllocVLV>(j_00037c54)(n3);
	else
		n2 = (unsigned)_STL::vectorSmallAllocate(n3);
	n1 = (BfmeHdrVLV *)n2;
	memset(n1, 0xa3, n3);
	n1->m_bfmeTag = 0xdeba;
	n1->m_bfmeVer = 1;
	n1->m_bfmeSize = n;
	return n1 + 1;
}

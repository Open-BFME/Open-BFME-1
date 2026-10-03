// cl: /Od

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

// Retail's large-block release: the five-byte ILT thunk at 0x0002AB35.  It is
// cdecl with the block pointer pushed, so the call goes through the thunk's own
// address, which is where retail's own call lands; whatever the thunk jumps to
// is retail's business, not this file's.
extern void j_0002ab35();

// The small-block release is STLport's own node-pool deallocator,
// _STL::__node_alloc<true, 0>::_M_deallocate at 0x0082E5F0, whose body is
// WWLib/node_alloc_M_deallocateThunk.cpp.  It is a private static member, so
// this TU reaches it under its real name through a TU-local friend, the shape
// WorldHeightMap_dtor.cpp uses for _M_allocate.

void bfmeFreeVLX(void *p, unsigned int n);

namespace _STL
{
template <bool __threads, int __inst> class __node_alloc;
template <bool __threads, int __inst>
class __node_alloc
{
	friend void ::bfmeFreeVLX(void *, unsigned int);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
}

struct BfmeHdrVLX
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void bfmeFreeVLX(void *p, unsigned n)
{
	BfmeHdrVLX *n1;
	unsigned n2;
	unsigned n3;

	n1 = (BfmeHdrVLX *)((char *)p - 0x10);
	for (n2 = (unsigned)n1 + 8; n2 < (unsigned)p; ++n2)
	{
	}
	n3 = n + 0x18;
	for (n2 = (unsigned)p + n; n2 < (unsigned)n1 + n3; ++n2)
	{
	}
	n1->m_bfmeTag = 0xdebd;
	memset(p, 0xa3, n);
	if (n3 > 0x80)
		reinterpret_cast<void (*)(void *)>(j_0002ab35)(n1);
	else
		_STL::__node_alloc<true, 0>::_M_deallocate(n1, n3);
}

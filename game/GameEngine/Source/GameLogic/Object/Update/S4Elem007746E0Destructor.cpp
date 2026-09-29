// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: destructor of the 44-byte S4Elem007746E0, retail 0x00753E80.
// Named from the STLport vector dtor at 0x007746E0 (11 dwords). Three
// pointer-vector members with inlined 0x80 node_alloc cutover, then 8 bytes POD.

void __cdecl operator delete(void *block);
namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		::operator delete(block);
	else
		_STL::nodePoolDeallocate(block, bytes);
}

class BfmeVecMember
{
public:
	~BfmeVecMember(void)
	{
		char *start = m_bfmeStart;
		char *end = m_bfmeEnd;
		unsigned int bytes = (unsigned int)(end - start);

		if (start)
			bfmeRelease(start, bytes);
	}

private:
	char *m_bfmeStart;
	char *m_bfmeFinish;
	char *m_bfmeEnd;
};

class S4Elem007746E0
{
public:
	~S4Elem007746E0(void);

private:
	BfmeVecMember m_bfmeList0;
	BfmeVecMember m_bfmeList1;
	BfmeVecMember m_bfmeList2;
	int m_bfmePad[2];
};

// ??1S4Elem007746E0@@QAE@XZ
S4Elem007746E0::~S4Elem007746E0(void)
{
}

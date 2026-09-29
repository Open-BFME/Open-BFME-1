// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: INIMemberA::~INIMemberA, retail 0x009CBFE0, 62 bytes. The body
// carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name
// with identity=real.
//
// A vtable store, one call on this, then a vector member released inline. The
// call comes before the release, which puts it in the destructor body rather
// than making it a base destructor -- those run after members, not before.
//
// The vector's three pointers are at +8, +0x0C and +0x10 and the element is
// eight bytes, from the halve-and-double the byte count goes through. The null
// check on the start pointer comes before that arithmetic here, the opposite
// order from the narrow-string reserve at 0x0053A100 where the count is taken
// first.

// The two frees are the ones the ledger already names: the large-block free at
// 0x00881EB0 and the node allocator's deallocate at 0x0082E5F0.
namespace _STL
{
static inline void vectorLargeDeallocate(void *block) { ::operator delete(block); }

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

struct BfmeIniMemberEntry
{
	int m_bfmeA;
	int m_bfmeB;
};

// The destructor is QAE, not UAE, so it is not virtual -- yet it stores a
// vtable pointer. That means the vptr comes from a base whose own destructor is
// non-virtual: an interface with pure virtuals and no virtual destructor.
class BfmeIniMemberInterface
{
public:
	virtual void bfmeSlot0(void) = 0;
};

class INIMemberA : public BfmeIniMemberInterface
{
public:
	__declspec(noinline) ~INIMemberA(void);

	virtual void bfmeSlot0(void);

private:
	void bfmeCleanup(void);					// retail 0x009CBF50

	int m_bfmeField4;					// +0x04
	BfmeIniMemberEntry *m_bfmeStart;			// +0x08
	BfmeIniMemberEntry *m_bfmeFinish;			// +0x0C
	BfmeIniMemberEntry *m_bfmeEndOfStorage;			// +0x10
};

// ??1INIMemberA@@QAE@XZ
INIMemberA::~INIMemberA(void)
{
	bfmeCleanup();

	if (m_bfmeStart != 0)
	{
		unsigned int bytes = (unsigned int)(m_bfmeEndOfStorage - m_bfmeStart)
			* sizeof(BfmeIniMemberEntry);
		if (bytes > 128)
			_STL::vectorLargeDeallocate(m_bfmeStart);
		else
			_STL::nodePoolDeallocate(m_bfmeStart, bytes);
	}
}

// Retail scalar-deleting wrapper at RVA 0x009CC200.
void DeleteINIMemberA(INIMemberA *member)
{
	delete member;
}

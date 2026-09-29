// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: destructor of the 0x88-byte attribute-pool entry, retail
// 0x0039DCC0, 280 bytes. The body was a gen_asm dump. symbols.csv pins this
// address as ??1S4Elem0039EBE0@@QAE@XZ from the S4 vector element dtor, and
// the ILT at 0x00043699 as ??1Gen00043699@@QAE@XZ from the 136-byte-stride
// pool vector. Layout matches Gen_t_0039e9d0_p128pod: two 12-byte members
// (ILT 0x00026AB2) then four pointer vectors whose inline dtors size-dispatch
// at the 0x80 node_alloc threshold.

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
		int *start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
	}

private:
	int *m_bfmeStart;
	int *m_bfmeFinish;
	int *m_bfmeEnd;
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB(void);

private:
	int m_bfmePad[3];
};

class S4Elem0039EBE0
{
public:
	~S4Elem0039EBE0(void);

private:
	AttributeModifierAuraUpdateModuleDataMemberB m_bfmeNames;
	AttributeModifierAuraUpdateModuleDataMemberB m_bfmeValues;
	BfmeVecMember m_bfmeList0;
	BfmeVecMember m_bfmeList1;
	BfmeVecMember m_bfmeList2;
	BfmeVecMember m_bfmeList3;
};

S4Elem0039EBE0::~S4Elem0039EBE0(void)
{
}

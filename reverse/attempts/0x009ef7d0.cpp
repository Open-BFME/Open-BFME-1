// ?copy@Rva009EF7D0@@QAEPAV1@PAV1@@Z
// partial score=0.85 date=2026-09-13
// ?copy@Rva009EF7D0@@QAEPAV1@PAV1@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void __cdecl _ReadWriteBarrier(void);

struct Rva0013FA60Target;
typedef Rva0013FA60Target *Rva0013FA60Key;

typedef _STL::_Rb_tree<Rva0013FA60Key, Rva0013FA60Key,
	_STL::_Identity<Rva0013FA60Key>, _STL::less<Rva0013FA60Key>,
	_STL::allocator<Rva0013FA60Key> > PointerIdentityTree0013FA60;

struct Gen_t_009ee8e0_k4
{
	int a[1];
};

typedef _STL::_Rb_tree<Gen_t_009ee8e0_k4, Gen_t_009ee8e0_k4,
	_STL::_Identity<Gen_t_009ee8e0_k4>, _STL::less<Gen_t_009ee8e0_k4>,
	_STL::allocator<Gen_t_009ee8e0_k4> > Rva009EF7D0Tree;

struct BfmeLockTEA;
extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA *lock);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveTEA(BfmeLockTEA *lock);

struct Rva009EF7D0Node
{
	Rva009EF7D0Node *m_next;
	Rva0013FA60Key m_value;
};

struct Rva009EF7D0Table
{
	unsigned char m_unused_000[4];
	Rva009EF7D0Node **m_bucketStart;
	Rva009EF7D0Node **m_bucketFinish;
};

struct Rva009EF7D0Range
{
	Rva009EF7D0Node *m_head;
	Rva009EF7D0Table *m_table;
};

class BfmeF1172
{
public:
	void bfmeFill1172(int *range);
};

struct Rva009EF7D0Output
{
	Rva009EF7D0Tree m_tree;
	int m_value;
	bool m_active;
};

class Rva009EF7D0
{
public:
	Rva009EF7D0 *copy(Rva009EF7D0 *out);

private:
	unsigned char m_unmodelled_000[0x2C];
	unsigned char m_lock[0x18];
	unsigned char m_unmodelled_044[0x88];
};

class TeaLockGuard009EF7D0
{
public:
	explicit TeaLockGuard009EF7D0(BfmeLockTEA *lock) : m_lock(lock), m_flag(0)
	{
		bfmeEnterTEA(m_lock);
	}
	~TeaLockGuard009EF7D0()
	{
		bfmeLeaveTEA(m_lock);
	}

	BfmeLockTEA *m_lock;
	int m_flag;
};

Rva009EF7D0 *Rva009EF7D0::copy(Rva009EF7D0 *out)
{
	TeaLockGuard009EF7D0 lock((BfmeLockTEA *)((unsigned char *)this + 0x2C));

	Rva009EF7D0Range range;
	((BfmeF1172 *)((unsigned char *)this + 0x44))->bfmeFill1172((int *)&range);

	PointerIdentityTree0013FA60 localSet;
	for (Rva009EF7D0Node *node = range.m_head; node != 0; )
	{
		localSet.insert_unique(node->m_value);

		Rva009EF7D0Node *next = node->m_next;
		if (next == 0)
		{
			unsigned int bucket = (unsigned int)node->m_value % (unsigned int)
				(range.m_table->m_bucketFinish - range.m_table->m_bucketStart);
			_ReadWriteBarrier();
			unsigned int bucketCount = (unsigned int)
				(range.m_table->m_bucketFinish - range.m_table->m_bucketStart);
			next = 0;
			while (next == 0 && ++bucket < bucketCount)
			{
				next = range.m_table->m_bucketStart[bucket];
			}
		}
		node = next;
	}

	Rva009EF7D0Output *output = (Rva009EF7D0Output *)out;
	new (&output->m_tree) Rva009EF7D0Tree(
		*(const Rva009EF7D0Tree *)&localSet);
	output->m_value = 0;
	output->m_active = true;

	return out;
}

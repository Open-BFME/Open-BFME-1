// ?bfmeSmallAllocPR@@YAPAXI@Z
// partial score=0.95 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc /Og-
// readable callee of ?bfmeAllocPR@@YAPAXI@Z: Code/GameEngine/Source/Common/BfmeTwoHundredSeventySeven.cpp
// Open-BFME: STLport __node_alloc<false,0>::_M_allocate, retail 0x0082E450, 152 bytes.
//
// False-thread sibling of the true-thread body at 0x0082E540 and of
// bfmeSmallFreePM at 0x0082E4F0. Same RAII _Node_Alloc_Lock: __threads is
// false, so acquire/release compile to xor/je over the dead lock calls.
// Freelist base 0x0130B210; empty-list refill at 0x0082C870.

namespace _STL
{

class NodeAllocMutex
{
public:
	void _M_acquire_lock(void);
	void _M_release_lock(void);
};

template <bool __threads, int __inst>
class _Node_Alloc_Lock
{
	int m_dummy;
	int m_dummy2;

public:
	_Node_Alloc_Lock()
	{
		if (__threads)
			_S_lock._M_acquire_lock();
	}
	~_Node_Alloc_Lock()
	{
		if (__threads)
			_S_lock._M_release_lock();
	}

	static NodeAllocMutex _S_lock;
};

template <bool __threads, int __inst>
NodeAllocMutex _Node_Alloc_Lock<__threads, __inst>::_S_lock;

}

struct BfmeFreeListNode
{
	BfmeFreeListNode *m_next;
};

extern BfmeFreeListNode *bfmeFreeList[0x10];

void *bfmeSmallRefillPR(unsigned int bytes);

void *bfmeSmallAllocPR(unsigned int bytes)
{
	void *block;
	BfmeFreeListNode * volatile *my_free_list =
		bfmeFreeList + ((bytes - 1) >> 3);
	_STL::_Node_Alloc_Lock<false, 0> lock_instance;
	if ((block = *my_free_list) != 0)
		*my_free_list = ((BfmeFreeListNode *)block)->m_next;
	else
		block = bfmeSmallRefillPR(bytes);
	return block;
}

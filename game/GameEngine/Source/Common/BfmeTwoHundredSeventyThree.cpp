// cl: /DNDEBUG /MD /EHsc /Og-
// A block let go of through one of two paths according to how big it is. The
// small-block arm is STLport's node allocator, with the false-thread
// specialization's constant lock tests retained by this compiler mode.

void bfmeBigFreePM(void *at);

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

void bfmeSmallFreePM(void *at, unsigned int bytes)
{
	BfmeFreeListNode * volatile *my_free_list =
		bfmeFreeList + ((bytes - 1) >> 3);
	_STL::_Node_Alloc_Lock<false, 0> lock_instance;
	((BfmeFreeListNode *)at)->m_next = *my_free_list;
	*my_free_list = (BfmeFreeListNode *)at;
}

void bfmeFreePM(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeBigFreePM(at);
	else
		bfmeSmallFreePM(at, bytes);
}

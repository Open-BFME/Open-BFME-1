void __cdecl operator delete(void *);

void __stdcall rva784C30Deallocate(void *block, unsigned int count);

// Retail's callee at 0x0082E5F0 is _STL::__node_alloc<true,0>::_M_deallocate,
// defined by game/Libraries/Source/WWVegas/WWLib/node_alloc_M_deallocateThunk.cpp.
// The ledger's owning spelling is the private-static CAXPAXI@Z form, so declare
// the member private too and keep this TU's own helper as the friend.
namespace _STL
{

class NodeAllocMutex
{
public:
	void _M_acquire_lock();
	void _M_release_lock();
};

template <bool __threads, int __inst>
class _Node_Alloc_Lock
{
	int m_dummy;
	int m_dummy2;

public:
	_Node_Alloc_Lock()
	{
		if (__threads) {
			_S_lock._M_acquire_lock();
		}
	}
	~_Node_Alloc_Lock()
	{
		if (__threads) {
			_S_lock._M_release_lock();
		}
	}

	static NodeAllocMutex _S_lock;
};

template <bool __threads, int __inst>
class __node_alloc
{
	struct _Obj
	{
		_Obj *_M_free_list_link;
	};

	friend void __stdcall ::rva784C30Deallocate(void *block, unsigned int count);

private:
	static void _M_deallocate(void *p, unsigned int n);
};

}

void __stdcall rva784C30Deallocate(void *block, unsigned int count)
{
	if (block != 0) {
		const unsigned int bytes = count * 16;
		if (bytes > 128) {
			operator delete(block);
		} else {
			_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
		}
	}
}

// cl: /DNDEBUG /MD /EHs-c- /O1

// Retail 0x0082DA10, eight bytes: the node allocator's lock acquire is a
// wrapper that hands its own this to a 267-byte __cdecl worker at 0x0082C760
// and lets a pop clean the one argument off -- which is /O1's way of undoing a
// four-byte push, /O2 emits add esp,4 instead.
//
//   push ecx
//   call 0x0082C760
//   pop ecx
//   ret

extern "C" void __cdecl BfmeNodeAllocLockAcquire(void *mutex);

namespace _STL
{

class NodeAllocMutex
{
public:
	void _M_acquire_lock(void);
};

// ?_M_acquire_lock@NodeAllocMutex@_STL@@QAEXXZ
void NodeAllocMutex::_M_acquire_lock(void)
{
	BfmeNodeAllocLockAcquire(this);
}

}  // namespace _STL

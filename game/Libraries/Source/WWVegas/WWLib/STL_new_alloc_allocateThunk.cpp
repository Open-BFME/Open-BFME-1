// cl: /DNDEBUG /MD /EHsc /Og-
// Open-BFME7: STLport 4.5.3 __node_alloc<true,0>::_M_allocate, retail
// 0x0082E540, 162 bytes. Retail has no identical-code folding: the
// ?allocate@__new_alloc@_STL@@SAPAXI@Z name belongs to the 5-byte
// `jmp operator new` body at 0x0082AD80 (callee of __debug_alloc<__new_alloc>
// ::allocate 0x0082B700), which TUs emit as STLport's inline COMDAT. The
// body follows inputs/vendor/stlport/stl/_alloc.c: the result pointer is the first local, the lock guard has no
// data members, and the node mutex acquire/release are the out-of-line
// thiscall members retail keeps. The one frame slot the earlier
// reconstructions could not place is an unreferenced local inside the
// inlined guard destructor: under /Og- it still gets a home, and because the
// destructor is inlined after the return value has been copied to its
// temporary, that home lands below the temporary.

// Retail's spinlock release (0x0082AD50, `mov [ecx],0; ret`) is ledgered as
// this class; the mutex inherits it so the unlock call names that row.
struct Gen_0082ad50 { void m(); };

namespace _STL
{

class NodeAllocMutex : public Gen_0082ad50
{
public:
    void _M_acquire_lock();
};

template <bool __threads, int __inst>
class _Node_Alloc_Lock
{
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
            _S_lock.m();
        }
        int unused;
    }

    static NodeAllocMutex _S_lock;
};

template <bool __threads, int __inst>
NodeAllocMutex _Node_Alloc_Lock<__threads, __inst>::_S_lock;

template <bool __threads, int __inst>
class __node_alloc
{
    struct _Obj
    {
        _Obj *_M_free_list_link;
    };

    static _Obj *_S_free_list[0x10];

    static void *_S_refill(unsigned int n);

    static void *_M_allocate(unsigned int n);
};

template <bool __threads, int __inst>
void *__node_alloc<__threads, __inst>::_M_allocate(unsigned int n)
{
    void *result;
    _Obj * volatile *my_free_list = _S_free_list + ((n - 1) >> 3);

    _Node_Alloc_Lock<__threads, __inst> lock_instance;
    if ((result = *my_free_list) != 0) {
        *my_free_list = ((_Obj *)result)->_M_free_list_link;
    } else {
        result = _S_refill(n);
    }

    return result;
}

template <bool __threads, int __inst>
typename __node_alloc<__threads, __inst>::_Obj * __node_alloc<__threads, __inst>::_S_free_list[0x10];

template class __node_alloc<true, 0>;

}

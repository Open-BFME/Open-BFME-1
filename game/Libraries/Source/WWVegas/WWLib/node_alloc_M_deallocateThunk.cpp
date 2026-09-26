// cl: /DNDEBUG /MD /EHsc /Og-
// Open-BFME5: lift _STL::__node_alloc::_M_deallocate __emit thunk to clean
// C++, mirroring the vendored stlport source: RAII _Node_Alloc_Lock whose
// ctor/dtor guard acquire/release behind `if (__threads)` (emitted as
// constant tests), free-list link updates in between.

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
NodeAllocMutex _Node_Alloc_Lock<__threads, __inst>::_S_lock;

template <bool __threads, int __inst>
class __node_alloc
{
    struct _Obj
    {
        _Obj *_M_free_list_link;
    };

    static _Obj *_S_free_list[0x10];

    static void _M_deallocate(void *p, unsigned int n);
};

template <bool __threads, int __inst>
void __node_alloc<__threads, __inst>::_M_deallocate(void *p, unsigned int n)
{
    _Obj * volatile *my_free_list = _S_free_list + ((n - 1) >> 3);
    _Node_Alloc_Lock<__threads, __inst> lock_instance;
    ((_Obj *)p)->_M_free_list_link = *my_free_list;
    *my_free_list = (_Obj *)p;
}

template void __node_alloc<true, 0>::_M_deallocate(void *, unsigned int);

}

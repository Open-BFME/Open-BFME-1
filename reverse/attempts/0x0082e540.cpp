// ?allocate@__new_alloc@_STL@@SAPAXI@Z
// partial score=0.97 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /Og-
// NEAR MISS - 160/162 bytes exact (0x0082E540, ?allocate@__new_alloc@_STL@@SAPAXI@Z,
// ICF-aliased to ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z at the same
// address/size). This is the real STLport __node_alloc<true,0>::_M_allocate
// free-list allocator body (NOT a plain __new_alloc, despite the row's public
// spelling) -- confirmed via the sibling node_alloc_M_deallocateThunk.cpp
// (same NodeAllocMutex/_Node_Alloc_Lock shape, same lock addresses 0x0082DA10
// acquire / 0x0082AD50 release) and via decode_calls.py resolving the unknown
// callee at +0x67 to 0x0082C920 (still an unconverted gen-dump, d_0082c920 /
// Code/gen_asm/d_0081de40.asm -- pin it as `_S_refill` when converting).
//
// Every branch, register, and call site below is byte-identical to retail
// EXCEPT the final return-value copy slot: retail stores the computed
// freelist/refill result at [ebp-0x1c] before running ~_Node_Alloc_Lock();
// this reconstruction consistently lands it at [ebp-0x20] -- exactly one
// missing 4-byte stack slot. Tried and rejected:
//   - if/else arm order (retail wants `if (result != 0) ... else refill`,
//     confirmed correct -- the OTHER order produces a much larger diff)
//   - inner nested `{ }` scope around the lock: makes it WORSE (shifts
//     my_free_list's own slot too)
//   - _Node_Alloc_Lock with 1 vs 2 "int m_dummy" padding fields: 2 dummies
//     gives the CORRECT total frame size (0x14) but wrong copy slot (e0);
//     1 dummy gives the CORRECT copy slot (e4) but frame short by exactly 4
//     (0x10) -- these two symptoms have never been reproduced simultaneously
//   - explicit named temp for the return value, declared before/after/inside
//     the lock's scope, at top-of-function, or via a named "index" local for
//     the freelist shift computation -- none change the outcome except to
//     make things worse
//   - dropping `volatile` on my_free_list, declaration order swaps of
//     my_free_list/result -- byte-identical either way (not the culprit)
//
// The missing 4 bytes almost certainly come from ONE more real STLport local
// this reconstruction is missing entirely (a genuine variable in the vendored
// source, not padding) whose lifetime doesn't overlap any of the ones here,
// so no visible instruction sets it, but MSVC 7.1 still reserves its slot.
// Worth trying: an unused/never-read explicit `_Obj *__unused;` OR a genuine
// second freelist-index-shaped local matching a slightly different (but
// equivalent) STLport source shape than the one below; or building the real
// upstream STLport `stl/_alloc.c` __node_alloc<>::allocate for this exact
// compiler and diffing its frame layout directly instead of guessing blind.

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

class __new_alloc
{
    struct _Obj
    {
        _Obj *_M_free_list_link;
    };

    static _Obj *_S_free_list[0x10];

    static _Obj *_S_refill(unsigned int n);

public:
    static void *allocate(unsigned int n);
};

void *__new_alloc::allocate(unsigned int n)
{
    _Obj * volatile *my_free_list = _S_free_list + ((n - 1) >> 3);
    _Obj *result;

    _Node_Alloc_Lock<true, 0> lock_instance;
    result = *my_free_list;
    if (result != 0) {
        *my_free_list = result->_M_free_list_link;
    } else {
        result = _S_refill(n);
    }

    return result;
}

}

// cl: /O2 /DNDEBUG /MD /EHs-c-
// The call at +0x12 is STLport's private pool deallocator
// _STL::__node_alloc<true,0>::_M_deallocate (0x0082E5F0).  Its real body is
// game/Libraries/Source/WWVegas/WWLib/node_alloc_M_deallocateThunk.cpp, under
// the mangled name this file must therefore spell; the TU-local mirror of the
// template plus the inline friend wrapper is the established way to reach it
// (same shape as WorldHeightMap_dtor.cpp).

namespace _STL
{
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

struct Rva14BA40ListNode
{
    Rva14BA40ListNode *next;
    Rva14BA40ListNode *previous;
    int value;
};

struct Rva14BA40ListIterator
{
    Rva14BA40ListNode *node;
};

struct Rva14BA40List
{
    Rva14BA40ListIterator *erase(Rva14BA40ListIterator *result, Rva14BA40ListNode *node);
};

// ?d_0014ba40@@YAXXZ
Rva14BA40ListIterator *Rva14BA40List::erase(Rva14BA40ListIterator *result, Rva14BA40ListNode *node)
{
    Rva14BA40ListNode *next = node->next;
    Rva14BA40ListNode *previous = node->previous;
    previous->next = next;
    next->previous = previous;
    _STL::nodePoolDeallocate(node, 12);
    result->node = next;
    return result;
}
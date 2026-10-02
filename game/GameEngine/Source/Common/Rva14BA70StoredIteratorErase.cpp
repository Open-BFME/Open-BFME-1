// The node is handed back to STLport's __node_alloc<true,0>::_M_deallocate
// (0x0082E5F0), spelled the way Q2NodePoolReleases.cpp and BigBlockReleases.cpp
// spell it; the previous placeholder invented rva423670SmallDeallocate, which
// nothing defines.

struct Rva14BA70StoredIterator;

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	friend struct ::Rva14BA70StoredIterator;
private:
	static void _M_deallocate(void *p, unsigned int n);
};
}

struct Rva14BA70ListNode
{
    Rva14BA70ListNode *next;
    Rva14BA70ListNode *previous;
    int value;
};

struct Rva14BA70ListIterator
{
    Rva14BA70ListNode *node;
};

struct Rva14BA70StoredIterator
{
    Rva14BA70ListIterator *iterator;

    void eraseCurrent();
};

// ?d_0014ba70@@YAXXZ
void Rva14BA70StoredIterator::eraseCurrent()
{
    Rva14BA70ListNode *node = iterator->node;
    Rva14BA70ListNode *next = node->next;
    Rva14BA70ListNode *previous = node->previous;
    previous->next = next;
    next->previous = previous;
    _STL::__node_alloc<true, 0>::_M_deallocate(node, 12);
}
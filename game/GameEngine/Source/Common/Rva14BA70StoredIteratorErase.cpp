void __cdecl rva423670SmallDeallocate(void *block, unsigned int size);

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
    rva423670SmallDeallocate(node, 12);
}

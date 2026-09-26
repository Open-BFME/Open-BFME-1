void __cdecl rva423670SmallDeallocate(void *block, unsigned int size);

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
    rva423670SmallDeallocate(node, 12);
    result->node = next;
    return result;
}

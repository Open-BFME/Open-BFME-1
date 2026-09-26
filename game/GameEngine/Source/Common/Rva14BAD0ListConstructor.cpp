namespace _STL
{
void *__cdecl vectorSmallAllocate(unsigned int size);
}

struct Rva14BAD0ListNode
{
    Rva14BAD0ListNode *next;
    Rva14BAD0ListNode *previous;
    int value;
};

struct Rva14BAD0List
{
    Rva14BAD0ListNode *head;

    Rva14BAD0List(int unused);
    Rva14BAD0List *initialize(char *flag, int value);
};

// ?d_0014bad0@@YAXXZ
Rva14BAD0List::Rva14BAD0List(int)
{
    char flag;
    initialize(&flag, 0);

    Rva14BAD0ListNode *sentinel = static_cast<Rva14BAD0ListNode *>(_STL::vectorSmallAllocate(12));
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
    head = sentinel;
}

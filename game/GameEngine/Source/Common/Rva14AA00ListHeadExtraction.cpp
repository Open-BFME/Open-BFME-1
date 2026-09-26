struct Rva14AA00ListNode
{
    Rva14AA00ListNode *next;
};

struct Rva14AA00ListHead
{
    Rva14AA00ListNode *head;

    Rva14AA00ListNode **extract(Rva14AA00ListNode **destination, int unused);
};

// ?d_0014aa00@@YAXXZ
Rva14AA00ListNode **Rva14AA00ListHead::extract(Rva14AA00ListNode **destination, int)
{
    Rva14AA00ListNode *node = head;
    head = node->next;
    *destination = node;
    return destination;
}

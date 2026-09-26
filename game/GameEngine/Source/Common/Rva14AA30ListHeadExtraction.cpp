struct Rva14AA30ListNode
{
    Rva14AA30ListNode *next;
};

struct Rva14AA30ListHead
{
    Rva14AA30ListNode *head;

    Rva14AA30ListNode **extract(Rva14AA30ListNode **destination, int unused);
};

// ?d_0014aa30@@YAXXZ
Rva14AA30ListNode **Rva14AA30ListHead::extract(Rva14AA30ListNode **destination, int)
{
    Rva14AA30ListNode *node = head;
    head = node->next;
    *destination = node;
    return destination;
}

struct Rva14AAB0ListNode
{
    Rva14AAB0ListNode *next;
};

struct Rva14AAB0ListHead
{
    Rva14AAB0ListNode *head;

    Rva14AAB0ListHead *advance();
};

// ?d_0014aab0@@YAXXZ
Rva14AAB0ListHead *Rva14AAB0ListHead::advance()
{
    head = head->next;
    return this;
}

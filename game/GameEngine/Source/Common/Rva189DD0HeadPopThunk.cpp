struct Rva189DD0Node
{
    Rva189DD0Node *next;
};

struct Rva189DD0HeadPopThunk
{
    Rva189DD0Node *head;

    Rva189DD0Node **pop(Rva189DD0Node **destination, int unused);
};

Rva189DD0Node **Rva189DD0HeadPopThunk::pop(Rva189DD0Node **destination, int)
{
    Rva189DD0Node *removed = head;
    head = removed->next;
    *destination = removed;
    return destination;
}

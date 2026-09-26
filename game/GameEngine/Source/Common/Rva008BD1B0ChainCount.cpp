// Identity is derived from the retail address; the dump exposes a linked-chain count.
struct Rva008BD1B0Node
{
    Rva008BD1B0Node *m_next;
    char m_pad[0x54];
    Rva008BD1B0Node *m_link;

    int count() const;
};

int Rva008BD1B0Node::count() const
{
    const Rva008BD1B0Node *node = m_next;
    int count = 0;
    while (node != 0)
    {
        node = node->m_link;
        ++count;
    }
    return count;
}

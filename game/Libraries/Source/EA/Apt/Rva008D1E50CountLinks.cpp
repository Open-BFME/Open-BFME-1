// Address-derived node view: retail follows the pointer at +0x4C.
struct Rva008D1E50Node {
    char m_pad[0x4c];
    Rva008D1E50Node *m_link4C;
    int rva008D1E50CountLinks() const;
};
int Rva008D1E50Node::rva008D1E50CountLinks() const
{
    int count = 0;
    const Rva008D1E50Node *node = m_link4C;
    while (node) {
        node = node->m_link4C;
        ++count;
    }
    return count;
}

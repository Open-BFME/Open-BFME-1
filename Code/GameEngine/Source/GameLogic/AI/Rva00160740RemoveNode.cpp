// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2

class Rva00160740Node
{
public:
    char m_pad00[4];
    Rva00160740Node *m_next;
    Rva00160740Node *m_prev;
};

class Rva00160740
{
public:
    void remove(Rva00160740Node *node);

private:
    char m_pad00[4];
    Rva00160740Node *m_head;
};

void Rva00160740::remove(Rva00160740Node *node)
{
    if (m_head != node && node->m_next == 0 && node->m_prev == 0)
        return;

    if (node->m_prev != 0)
        node->m_prev->m_next = node->m_next;

    if (node->m_next != 0)
        node->m_next->m_prev = node->m_prev;
    else
        m_head = node->m_prev;

    node->m_next = 0;
    node->m_prev = 0;
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
// Near-twin of ?remove@Rva00160740@@QAEXPAVRva00160740Node@@@Z
// (Code/GameEngine/Source/GameLogic/AI/Rva00160740RemoveNode.cpp): same
// intrusive doubly-linked-list layout, head field at +0x4, node next/prev
// at +0x4/+0x8. Address-derived; identity not recovered beyond retail bytes.

class Rva00160700Node
{
public:
    char m_pad00[4];
    Rva00160700Node *m_next;
    Rva00160700Node *m_prev;
};

class Rva00160700
{
public:
    void add(register Rva00160700Node *node);

private:
    char m_pad00[4];
    Rva00160700Node *volatile m_head;
};

void Rva00160700::add(register Rva00160700Node *node)
{
    if (m_head == node)
        return;
    if (node->m_next != 0)
        return;
    if (node->m_prev != 0)
        return;
    node->m_prev = m_head;
    Rva00160700Node *head = m_head;
    if (head != 0)
        head->m_next = node;
    m_head = node;
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
// Near-twin of ?remove@Rva00160740@@QAEXPAVRva00160740Node@@@Z
// (Code/GameEngine/Source/GameLogic/AI/Rva00160740RemoveNode.cpp): identical
// intrusive doubly-linked-list remove(): owner's head field at +0x8 (twin: +0x4)
// and node's next/prev at +0xc/+0x10 (twin: +0x4/+0x8). Address-derived;
// identity not recovered beyond the retail bytes.

class Rva00160910Node
{
public:
    char m_pad00[0xc];
    Rva00160910Node *m_next;
    Rva00160910Node *m_prev;
};

class Rva00160910
{
public:
    void remove(Rva00160910Node *node);

private:
    char m_pad00[8];
    Rva00160910Node *m_head;
};

void Rva00160910::remove(Rva00160910Node *node)
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

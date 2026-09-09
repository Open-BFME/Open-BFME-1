// ?isLinked@Rva001606D0@@QAEPAVRva001606D0Node@@PAV2@@Z
// partial score=0.89 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
// Near-twin of ?remove@Rva00160740@@QAEXPAVRva00160740Node@@@Z
// (Code/GameEngine/Source/GameLogic/AI/Rva00160740RemoveNode.cpp): same
// intrusive doubly-linked-list layout, head field at +0x4, node next/prev
// at +0x4/+0x8. Address-derived; identity not recovered beyond retail bytes.

class Rva001606D0Node
{
public:
    char m_pad00[4];
    Rva001606D0Node *m_next;
    Rva001606D0Node *m_prev;
};

class Rva001606D0
{
public:
    Rva001606D0Node *isLinked(Rva001606D0Node *node);

private:
    char m_pad00[4];
    Rva001606D0Node *m_head;
};

Rva001606D0Node *Rva001606D0::isLinked(Rva001606D0Node *node)
{
    if (m_head == node)
        goto found;
    if (node->m_next != 0)
        goto found;
    if (node->m_prev != 0)
        goto found;
    return 0;
found:
    return node;
}

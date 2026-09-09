// ?isLinked@Rva001608A0@@QAEPAVRva001608A0Node@@PAV2@@Z
// partial score=0.89 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob0
// Near-twin of ?add@Rva001608D0@@QAEXPAVRva001608D0Node@@@Z
// (Code/GameEngine/Source/GameLogic/AI/Rva001608D0AddNode.cpp): same
// intrusive doubly-linked-list layout, head field at +0x8, node prev/next
// at +0xc/+0x10. Address-derived; identity not recovered beyond retail bytes.

class Rva001608A0Node
{
public:
    char m_pad00[0xc];
    Rva001608A0Node *m_prev;
    Rva001608A0Node *m_next;
};

class Rva001608A0
{
public:
    Rva001608A0Node *isLinked(Rva001608A0Node *node);

private:
    char m_pad00[8];
    Rva001608A0Node *m_head;
};

Rva001608A0Node *Rva001608A0::isLinked(Rva001608A0Node *node)
{
    if (m_head == node)
        goto found;
    if (node->m_prev != 0)
        goto found;
    if (node->m_next != 0)
        goto found;
    return 0;
found:
    return node;
}

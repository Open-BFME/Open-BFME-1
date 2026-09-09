// ?Rva00698730Remainder@@YGIPAPAURva00698730Node@@I@Z
// partial score=0.85 date=2026-09-09
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00698730Node
{
    char m_pad[8];
    unsigned int m_key;
};

unsigned int __stdcall Rva00698730Remainder(Rva00698730Node **head, unsigned int m)
{
    Rva00698730Node *node = *head;
    if (!node)
        return (unsigned int)node % m;
    return node->m_key % m;
}

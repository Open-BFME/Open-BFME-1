// ?Rva00698730Remainder@@YGIPAPAURva00698730Node@@I@Z (identity unknown)
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva00698730Node
{
    char m_pad[8];
    unsigned int m_key;
};

unsigned int __stdcall Rva00698730Remainder(Rva00698730Node **head, unsigned int m)
{
    Rva00698730Node *node = *head;
    if (!node)
    {
        _ReadWriteBarrier();
        return (unsigned int)node % m;
    }
    return node->m_key % m;
}

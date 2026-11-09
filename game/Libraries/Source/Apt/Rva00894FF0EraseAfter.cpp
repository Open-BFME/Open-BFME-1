// cl: /Os
extern void (__cdecl *g_bfmeFreeDWF)(void *);
struct Rva00894FF0Node {
    void *m_at000;
    Rva00894FF0Node *m_next;
};
// ?Rva00894FF0@@YGXPAPAURva00894FF0Node@@@Z
// Open BFME 2 Code/Libraries/Source/Apt/AptLoadCountedOwner.cpp.
void __stdcall Rva00894FF0(Rva00894FF0Node **arg) {
    Rva00894FF0Node *owner = *arg;
    Rva00894FF0Node *node = owner->m_next;
    if ((*arg)->m_next)
        (*arg)->m_next = (*arg)->m_next->m_next;
    g_bfmeFreeDWF(node);
}

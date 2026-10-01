// ?Rva00894FF0@@YGXPAPAURva00894FF0Node@@@Z
// partial score=0.4688 date=2026-10-01
// cl: /Os
// Native RVA 0x00894FF0, 32-byte boundary ending RET 4.
// Emission view: one stack pointer argument. Lexical owner and types unknown.
extern void (__cdecl *g_bfmeFreeDWF)(void *);
struct Rva00894FF0Node {
    void *m_at000;
    Rva00894FF0Node *m_at004;
};
void __stdcall Rva00894FF0(Rva00894FF0Node **arg) {
    Rva00894FF0Node *owner = *arg;
    Rva00894FF0Node *node = owner->m_at004;
    if (node) {
        Rva00894FF0Node *next = node->m_at004;
        owner->m_at004 = next;
    }
    g_bfmeFreeDWF(node);
}

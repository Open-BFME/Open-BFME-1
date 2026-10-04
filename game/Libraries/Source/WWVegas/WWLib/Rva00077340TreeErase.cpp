// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <memory>
#include "ascii_string.h"

// Keep the exact retail ILT route: 0x479D3 -> 0x723D0 ->
// StringBase<char>::releaseBuffer at 0x887940. It consumes ECX only, returns
// void, and leaves the stack untouched. The anonymous thunk has no C++ type.
void j_000479d3();

// Retail 0x00077340, reached by MapCache::loadUserMaps through ILT 0x0000DB2A.
// Evidence: targets/game/reverse/identity_evidence/00077340-tree-erase.md.
// The caller proves an AsciiString key; the mapped value's identity is unknown.
// This partial physical node view deliberately makes no template-specialization
// claim. The four bytes after the key include the unproven mapped field/padding.
struct Rva00077340Node
{
    char m_unknown00[8];
    Rva00077340Node *m_left;
    Rva00077340Node *m_right;
    AsciiString m_key;
    char m_unknown14[4];
};

class Rva00077340Owner
{
public:
    void erase(Rva00077340Node *node);
};

void Rva00077340Owner::erase(Rva00077340Node *node)
{
    while (node != 0)
    {
        erase(node->m_right);
        Rva00077340Node *left = node->m_left;
        union { void (*raw)(); void (AsciiString::*member)(); } release;
        release.raw = j_000479d3;
        (node->m_key.*release.member)();
        _STL::__node_alloc<true, 0>::deallocate(node, sizeof(Rva00077340Node));
        node = left;
    }
}

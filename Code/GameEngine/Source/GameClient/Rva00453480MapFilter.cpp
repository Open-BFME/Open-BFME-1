// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x00453480: cdecl(flags, vector*) as witnessed by getDefaultMap.
// MapMetaData_ctor/assign witness flags at +0x24/+0x25/+0x26.
// Overflow call +0xBD reaches 0x00452300 via ILT 0x0002F3EC: thiscall,
// five stack arguments, ret 0x14, four-byte pointer copies and stride.

#include <cstring>

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)
#include <vector>
#undef memmove

struct Rva00453480MapMetaData {
    unsigned char m_opaque[0x24];
    unsigned char m_isMultiplayer;
    unsigned char m_isScenarioMP;
    unsigned char m_isOfficial;
};

struct Rva00453480MapNode {
    unsigned char m_opaque[0x14];
    Rva00453480MapMetaData m_value;
};

struct Rva00453480MapTree {
    unsigned char m_opaque[8];
    Rva00453480MapNode *m_left;
};

struct Rva00453480MapCache {
    Rva00453480MapTree *m_tree;
};

#define TheMapCache (*(Rva00453480MapCache **)0x012F1594)

namespace _STL {
struct _Rb_tree_node_base;
template <class Dummy> class _Rb_global;
template <> class _Rb_global<bool> {
public:
    static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}

typedef _STL::vector<Rva00453480MapMetaData *> Rva00453480Vector;


extern "C" __declspec(dllexport) void Rva00453480Collect(
    unsigned int flags, Rva00453480Vector *out)
{
    if ((flags & 0x40) == 0)
        out->clear();

    Rva00453480MapTree *tree = TheMapCache->m_tree;
    Rva00453480MapNode *node = tree->m_left;
    while (node != (Rva00453480MapNode *)tree) {
        Rva00453480MapMetaData *metadata = &node->m_value;

        if ((flags & 1) && metadata->m_isOfficial)
            goto filter_multiplayer;
        if ((flags & 2) == 0)
            goto next;
        if (metadata->m_isOfficial)
            goto next;

filter_multiplayer:

        if (metadata->m_isMultiplayer && (flags & 4))
            goto next;
        if (metadata->m_isMultiplayer)
            goto filter_scenario;
        if (flags & 8)
            goto next;

filter_scenario:
        if (metadata->m_isScenarioMP && (flags & 0x10))
            goto next;
        if (metadata->m_isScenarioMP)
            goto append;
        if (flags & 0x20)
            goto next;

append:
        {
            Rva00453480MapMetaData *selected = metadata;
            out->push_back(selected);
        }

    next:
        node = (Rva00453480MapNode *)_STL::_Rb_global<bool>::_M_increment(
            (_STL::_Rb_tree_node_base *)node);
        tree = TheMapCache->m_tree;
    }
}

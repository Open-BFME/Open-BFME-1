#ifndef RVA00453480_MAP_POINTER_COLLECTOR_H
#define RVA00453480_MAP_POINTER_COLLECTOR_H

// This real collector remains visible to population: MSVC 7.1 otherwise
// treats the local vector address as escaped and changes the caller's code.
// Inline gives both natural users the same foldable native COMDAT body.
// Retail 0x00453480: cdecl(flags, vector*) as witnessed by getDefaultMap.
// MapMetaData_ctor/assign witness flags at +0x24/+0x25/+0x26.
// Overflow call +0xBD reaches 0x00452300 via ILT 0x0002F3EC: thiscall,
// five stack arguments, ret 0x14, four-byte pointer copies and stride.

#include <cstring>

extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned int);
#include <vector>
#include <map>

class MapMetaData;

// Address-qualified read-only prefix; this does not declare a competing MapMetaData.
struct Rva00453480MapFlags {
    unsigned char m_opaque[0x24];
    unsigned char m_isMultiplayer;
    unsigned char m_isScenarioMP;
    unsigned char m_isOfficial;
};

struct Rva00453480MapNode {
    unsigned char m_opaque[0x14];
    Rva00453480MapFlags m_value;
};

struct Rva00453480MapTree {
    unsigned char m_opaque[8];
    Rva00453480MapNode *m_left;
};

struct Rva00453480MapCache {
    Rva00453480MapTree *m_tree;
};

// The canonical global retains its real class type. Only the observed first
// field is viewed through the address-qualified prefix above.
class MapCache;
extern MapCache *TheMapCache;

typedef _STL::vector<const MapMetaData *> Rva00453480Vector;

extern "C" __declspec(dllexport) inline void Rva00453480Collect(
    unsigned int flags, Rva00453480Vector *out)
{
    if ((flags & 0x40) == 0)
        out->clear();

    Rva00453480MapTree *tree = ((Rva00453480MapCache *)TheMapCache)->m_tree;
    Rva00453480MapNode *node = tree->m_left;
    while (node != (Rva00453480MapNode *)tree) {
        const Rva00453480MapFlags *metadata = &node->m_value;

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
            const MapMetaData *selected = reinterpret_cast<const MapMetaData *>(metadata);
            out->push_back(selected);
        }

    next:
        node = (Rva00453480MapNode *)_STL::_Rb_global<bool>::_M_increment(
            (_STL::_Rb_tree_node_base *)node);
        tree = ((Rva00453480MapCache *)TheMapCache)->m_tree;
    }
}

#endif

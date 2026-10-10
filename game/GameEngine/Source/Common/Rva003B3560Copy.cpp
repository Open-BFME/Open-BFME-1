// ??$__copy@PBURva003B3560Elem32@@PAU1@H@_STL@@YAPAURva003B3560Elem32@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <algorithm>

// Payload mapping: targets/game/reverse/identity_evidence/003b3560-nested-payload-copy.md
struct Rva003B3560Elem32
{
    virtual ~Rva003B3560Elem32();
    unsigned int m_a;
    Coord3D m_triple;
    float m_e;
    unsigned int m_f;
    bool m_flag;
};

template Rva003B3560Elem32 *_STL::__copy<
    const Rva003B3560Elem32 *, Rva003B3560Elem32 *, int>(
    const Rva003B3560Elem32 *, const Rva003B3560Elem32 *,
    Rva003B3560Elem32 *, const _STL::random_access_iterator_tag &, int *);

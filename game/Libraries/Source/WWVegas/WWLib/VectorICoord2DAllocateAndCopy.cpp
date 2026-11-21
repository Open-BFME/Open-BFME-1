// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail 0x009F5370,94B: the authentic STLport 4.6 member-template body.
// Implementation: inputs/vendor/stlport/stl/_vector.h::_M_allocate_and_copy;
// native type contract: targets/game/reverse/class_contracts/ICoord2D.json.
// The allocator/copy caller chain and the two-int native element layout are
// documented in targets/game/reverse/identity_evidence/20261120-009f5370-vector-allocate-copy.md.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include "../../../Include/Lib/ICoord2D.h"
#include <vector>

template ICoord2D *_STL::vector<ICoord2D,_STL::allocator<ICoord2D> >::_M_allocate_and_copy<const ICoord2D *>(
    unsigned int,const ICoord2D *,const ICoord2D *);

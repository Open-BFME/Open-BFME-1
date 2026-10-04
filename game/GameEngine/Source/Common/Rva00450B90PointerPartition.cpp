// cl: /O2 /D_STLP_USE_STATIC_LIB
// stlport
// Four-slot cdecl leaf reached through ILT 0x00043004; returns the partition
// iterator. fillMapMask passes pointers returned by MapCache::findMap.
#include <algorithm>
#include "Rva0055AE10MapPredicate.h"

// ??$__partition@PAPBVMapMetaData@@URva0055AE10MapPredicate@@@_STL@@YAPAPBVMapMetaData@@PAPBV1@0URva0055AE10MapPredicate@@ABUbidirectional_iterator_tag@0@@Z
template const MapMetaData **_STL::__partition(const MapMetaData **,
    const MapMetaData **, Rva0055AE10MapPredicate,
    const _STL::bidirectional_iterator_tag &);

// Native three-slot wrapper at 0x00451E60. Identical template wrappers cannot
// establish its original name. The empty category's address is the fourth slot.
const MapMetaData **rva00451E60Partition(const MapMetaData **first,
    const MapMetaData **last, Rva0055AE10MapPredicate predicate)
{
    return _STL::__partition(first, last, predicate, _STL::random_access_iterator_tag());
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <iterator>
#include "Rva0055AE10MapPredicate.h"

struct Rva00452120Range
{
    const MapMetaData **first;
    const MapMetaData **last;
};
namespace _STL
{
template<class Iterator, class Predicate>
Iterator __partition(Iterator first, Iterator last, Predicate predicate,
                     const bidirectional_iterator_tag &category);
}
// Two-slot cdecl ABI: predicate by value, then a read-only iterator prefix.
// No vector capacity, receiver, or original semantic class is established.
const MapMetaData **rva00452120Partition(Rva0055AE10MapPredicate predicate,
                                       const Rva00452120Range *range)
{
    const MapMetaData **last = range->last;
    const MapMetaData **first = range->first;
    _STL::bidirectional_iterator_tag category;
    return _STL::__partition(first, last, predicate, category);
}

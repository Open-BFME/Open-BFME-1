// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <iterator>
#include <set>
#include "ascii_string.h"

typedef _STL::insert_iterator<_STL::set<AsciiString> > Rva000C11D0Inserter;

// STLport 4.5.3 inputs/vendor/stlport/stl/_algobase.h:136 random-access __copy.
// Retail 0x000C11D0 divides the AsciiString-pointer range by four, calls the
// matched hinted set insertion at 0x000C05C0, advances its tree iterator
// through 0x0082B870, and returns the two-word insert_iterator by value.
// The tag and distance-pointer arguments are unused exactly as in the header.
template Rva000C11D0Inserter _STL::__copy<AsciiString *, Rva000C11D0Inserter, ptrdiff_t>(
    AsciiString *first, AsciiString *last, Rva000C11D0Inserter output,
    const _STL::random_access_iterator_tag &tag, ptrdiff_t *distance);

// The image has two byte-identical copies of the __copy_aux forwarding shape
// at 0x000C13E0 and 0x000C1500. Their address-qualified names retain separate
// ledger identities while using the native insertion-iterator ABI.
// inputs/vendor/stlport/stl/_algobase.h:204-210 supplies the forwarding expression.
Rva000C11D0Inserter Rva000C13E0(AsciiString *first, AsciiString *last,
    Rva000C11D0Inserter output, const _STL::__false_type &)
{
    return _STL::__copy(first, last, output, _STL::random_access_iterator_tag(), (ptrdiff_t *)0);
}

Rva000C11D0Inserter Rva000C1500(AsciiString *first, AsciiString *last,
    Rva000C11D0Inserter output, const _STL::__false_type &)
{
    return _STL::__copy(first, last, output, _STL::random_access_iterator_tag(), (ptrdiff_t *)0);
}

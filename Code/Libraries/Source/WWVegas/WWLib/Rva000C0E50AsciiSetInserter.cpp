// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <set>
#include "ascii_string.h"

typedef _STL::set<AsciiString> Rva000C0E50AsciiSet;

// vendor/stlport/stl/_iterator.h:229-248 supplies this operator= shape.
// Retail this+0 and this+4 are the container and iterator; its calls reach
// the matched hinted AsciiString-set insertion (0x000C05C0 via 0x00039838)
// and iterator increment (0x0082B870). The ret 4 at +0x32 is followed by INT3.
// No caller names the instantiated owner, so this view keeps its address.
class Rva000C0E50AsciiSetInserter
{
public:
    Rva000C0E50AsciiSet *container;
    Rva000C0E50AsciiSet::iterator iter;
    Rva000C0E50AsciiSetInserter &operator=(const AsciiString &value);
};

Rva000C0E50AsciiSetInserter &
Rva000C0E50AsciiSetInserter::operator=(const AsciiString &value)
{
    iter = container->insert(iter, value);
    ++iter;
    return *this;
}

// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

class Rva001E4ED0Target;

typedef _STL::list<Rva001E4ED0Target *> WtTailList;

template WtTailList &WtTailList::operator=(const WtTailList &);

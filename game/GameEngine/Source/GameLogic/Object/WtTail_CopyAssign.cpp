// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// _STLP_NO_EXCEPTIONS as in RvaListInsertRange.cpp: without it the
// list<Rva001E4ED0Target *>::_M_insert_dispatch COMDAT emitted here is a
// 59-byte copy, not retail's 66-byte 0x001E4ED0.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Rva001E4ED0Target;

typedef _STL::list<Rva001E4ED0Target *> WtTailList;

template WtTailList &WtTailList::operator=(const WtTailList &);

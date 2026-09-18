// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

class Rva001E4ED0Target;

typedef _STL::list<Rva001E4ED0Target *> WtTailList;

template WtTailList &WtTailList::operator=(const WtTailList &);

#pragma comment(linker, "/alternatename:??4WtTail@@QAEAAV0@ABV0@@Z=??4?$list@PAVRva001E4ED0Target@@V?$allocator@PAVRva001E4ED0Target@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z")

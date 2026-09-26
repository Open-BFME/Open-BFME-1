// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The big-command factory returns the game's actual STLport list<NetPacket *>.
// Keep these lifetime bodies as the vendor's explicit typed instantiation:
// retail allocates 12-byte NetPacket* list nodes and dispatches insertion and
// deallocation through that specialization's existing STLport helpers.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class NetPacket;

template class _STL::list<NetPacket *>;

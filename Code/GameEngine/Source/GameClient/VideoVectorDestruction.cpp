// cl: -GX-
// stlport
#include "../../Include/GameClient/Video.h"
#include <vector>

// These two retail bodies walk 28-byte Video records and call the destructor
// through ILT 0x167CF  -> 0xC3410. This no-EH vector destructor at 0x81D0F0 is a
// distinct compiler variant of the retained EH-framed body at 0x81D040;
// the ledger keeps its address-qualified identity to distinguish the bodies.
template class _STL::vector<Video>;

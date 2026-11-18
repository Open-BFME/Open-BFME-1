// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: SetLookAtPlayer, retail 0x004DBB50, 120 bytes. Converted from
// gen-dump d_004dbb50. ZH twin stores lookAtPlayerID then assigns
// lookAtPlayerName from the by-value AsciiString's str(). BFME keeps the
// name as STLport std::string (assign first/last after a strlen walk) and
// the id as a TU-scope Int. Callers: WOLWelcomeMenu.cpp and WOLBuddyOverlay.cpp.
// The name's dynamic initializer (_$E1: default-construct through the string
// ctor ILT 0x0004048A, then atexit) is retail 0x00C6BAF0.

#include <string>
#include "ascii_string.h"

#include "../../../../../Include/Common/ScalarTypes.h"

Int lookAtPlayerID = 0;
std::string lookAtPlayerName;

void SetLookAtPlayer( Int id, AsciiString nick )
{
	lookAtPlayerID = id;
	lookAtPlayerName = nick.str();
}

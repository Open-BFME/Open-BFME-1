// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: map<Int, UnsignedInt>'s tree members -- the map type of
// PSPlayerStats' PerGeneralMap (Zero Hour PersistentStorageThread.h). Retail
// keeps them at _M_copy 0x000A3E50, _M_erase 0x000A3660 (and the destructor
// 0x000A3C70 and operator= 0x000A4BB0 that PSPlayerStats reaches through ILTs
// 0x9895 and 0x13B33). Each clone's pair goes through the out-of-line
// _Construct behind ILT 0x2C3A4. The int-keyed AsciiString map (the ignore
// list) has its own copies at 0x000AAC70/0x000AA7B0; evidence in
// targets/game/reverse/identity_evidence/000a3c70-000ab1c0-int-map-unsigned-vs-asciistring.md.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "../../Include/Common/ScalarTypes.h"


typedef _STL::map<Int, UnsignedInt> BfmeIntMap;

void BfmeIntMapCopyAnchor(BfmeIntMap &out, const BfmeIntMap &in)
{
	out = in;
}

// The int-keyed AsciiString map (Zero Hour PeerDefs.h SavedIgnoreMap) keeps
// its _M_copy at 0x000AAC70 in this same non-EH shape: the AsciiString copy
// lives in the out-of-line _Construct behind ILT 0x1C67A.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef _STL::map<Int, AsciiString> BfmeIntAsciiMap;

void BfmeIntAsciiMapCopyAnchor(BfmeIntAsciiMap &out, const BfmeIntAsciiMap &in)
{
	out = in;
}

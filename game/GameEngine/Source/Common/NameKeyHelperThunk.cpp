// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: NAMEKEY(const AsciiString&)
// Retail: if data non-null, nameToKey(data+8); else nameToKey(empty literal).

#include "../GameLogic/ScriptEngine/game_logic_dispatch.h"

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h


// DIR32: TheNameKeyGenerator
extern NameKeyGenerator *g_theNameKeyGenerator;
// empty string literal for null AsciiString data


// ?NAMEKEY@@YA?AW4NameKeyType@@ABVAsciiString@@@Z
NameKeyType NAMEKEY(const AsciiString &s)
{
	const char *p = s.str();
	return g_theNameKeyGenerator->nameToKey(p);
}

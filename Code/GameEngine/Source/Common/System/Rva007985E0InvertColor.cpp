// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/GameClient /ICode/GameEngine/Include/Precompiled
//
// Retail 0x007985E0 splits a packed color, complements its RGB components,
// preserves alpha, and packs the result again.  The address-derived name is
// intentional: the retail call graph identifies the operation and its
// GameGetColorComponents callee, but not a recovered public symbol.

#include "prerts.h"
#include "color.h"

Color Rva007985E0( Color color )
{
	UnsignedByte red, green, blue, alpha;
	GameGetColorComponents( color, &red, &green, &blue, &alpha );
	return GameMakeColor( 255 - red, 255 - green, 255 - blue, alpha );
}

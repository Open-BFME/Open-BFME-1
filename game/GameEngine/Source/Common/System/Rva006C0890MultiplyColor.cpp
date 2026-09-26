// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/GameClient /Igame/GameEngine/Include/Precompiled
//
// Retail 0x006C0890 multiplies the alpha, red, green, and blue components of
// two packed colors and returns the packed result.  W3DRadar::renderObjectList
// at 0x006C43F0 is the only caller, so the address-derived name preserves the
// identity that the retail call graph proves without inventing a public name.

#include "prerts.h"
#include "color.h"

Color Rva006C0890( Color first, Color second )
{
	UnsignedByte firstRed, firstGreen, firstBlue, firstAlpha;
	UnsignedByte secondRed, secondGreen, secondBlue, secondAlpha;
	GameGetColorComponents( first, &firstRed, &firstGreen, &firstBlue, &firstAlpha );
	GameGetColorComponents( second, &secondRed, &secondGreen, &secondBlue, &secondAlpha );
	return GameMakeColor( firstRed * secondRed / 255,
											 firstGreen * secondGreen / 255,
											 firstBlue * secondBlue / 255,
											 firstAlpha * secondAlpha / 255 );
}

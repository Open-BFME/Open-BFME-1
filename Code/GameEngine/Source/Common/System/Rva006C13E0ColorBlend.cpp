// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/GameClient /ICode/GameEngine/Include/Precompiled
// ?Rva006C13E0@@YAHPAHHE@Z
// Retail 0x006C13E0 blends the packed color already stored at the destination
// with a packed source color scaled by an extra alpha byte.

#include "prerts.h"
#include "color.h"

Color Rva006C13E0(Color *color, Color source, UnsignedByte alpha)
{
	Color *out = color;
	UnsignedByte oldAlpha, blue, green, red;
	UnsignedByte sourceAlpha, sourceBlue, sourceGreen, sourceRed;

	GameGetColorComponents(*out, &red, &green, &blue, &oldAlpha);
	GameGetColorComponents(source, &sourceRed, &sourceGreen, &sourceBlue, &sourceAlpha);

	UnsignedByte effectiveAlpha = (UnsignedInt)(sourceAlpha * alpha) / 255;
	if (oldAlpha == 0 || effectiveAlpha == 255)
		return *out = GameMakeColor(sourceRed, sourceGreen, sourceBlue, effectiveAlpha);

	red = (UnsignedInt)(red * oldAlpha + sourceRed * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	green = (UnsignedInt)(green * oldAlpha + sourceGreen * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	blue = (UnsignedInt)(blue * oldAlpha + sourceBlue * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	oldAlpha = 255 - (UnsignedInt)((255 - oldAlpha) * (255 - effectiveAlpha)) / 255;
	Color result = (Color)(UnsignedInt)blue;
	result |= (oldAlpha << 24) | (red << 16) | (green << 8);
	return *out = result;
}

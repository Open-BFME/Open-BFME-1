// ?d_006c13e0@@YAXXZ
// partial score=0.95 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/GameClient /ICode/GameEngine/Include/Precompiled
//
// Retail 0x006C13E0 blends the color already stored at the destination with a
// packed source color.  The owner is not named in the retail call graph, so
// this address-derived free-function identity preserves the proven behavior.

#include "prerts.h"
#include "color.h"

// ?Rva006C13E0@@YAXPAHHE@Z
void Rva006C13E0(Color *color, Color source, UnsignedByte alpha)
{
	Color *out = color;
	UnsignedByte oldAlpha, blue, green, red;
	UnsignedByte sourceAlpha, sourceBlue, sourceGreen, sourceRed;

	GameGetColorComponents(*out, &red, &green, &blue, &oldAlpha);
	GameGetColorComponents(source, &sourceRed, &sourceGreen, &sourceBlue, &sourceAlpha);

	UnsignedByte effectiveAlpha = (UnsignedInt)(sourceAlpha * alpha) / 255;
	if (oldAlpha == 0 || effectiveAlpha == 255)
	{
		UnsignedInt packed = (effectiveAlpha << 24) | (sourceRed << 16) |
			(sourceGreen << 8) | sourceBlue;
		*out = (Color)packed;
		return;
	}

	red = (UnsignedInt)(red * oldAlpha + sourceRed * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	green = (UnsignedInt)(green * oldAlpha + sourceGreen * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	blue = (UnsignedInt)(blue * oldAlpha + sourceBlue * effectiveAlpha) /
		(oldAlpha + effectiveAlpha);
	oldAlpha = 255 - (UnsignedInt)((255 - oldAlpha) * (255 - effectiveAlpha)) / 255;
	UnsignedInt packed = (oldAlpha << 24) | (red << 16) | (green << 8) | blue;
	*out = (Color)packed;
}

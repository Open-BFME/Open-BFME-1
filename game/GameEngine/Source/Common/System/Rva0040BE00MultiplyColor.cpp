// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/GameClient /Igame/GameEngine/Include/Precompiled
// Retail 0x0040BE00 multiplies the four packed-color channels.

#include "prerts.h"
#include "color.h"

Color Rva0040BE00MultiplyColor(Color first, Color second)
{
	unsigned int alpha = ((first >> 24) & 0xff) * ((second >> 24) & 0xff) / 255;
	unsigned int red = ((first >> 16) & 0xff) * ((second >> 16) & 0xff) / 255;
	unsigned int green = ((first >> 8) & 0xff) * ((second >> 8) & 0xff) / 255;
	unsigned int blue = (first & 0xff) * (second & 0xff) / 255;
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

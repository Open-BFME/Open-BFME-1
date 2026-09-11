// cl: /O2 /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef int Int;
typedef short Short;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long Rva0074A0D0FloorToInt(Real value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

struct Rva0074A0D0TextureClass
{
	Int globalTextureClass;
	Int firstTile;
	Int numTiles;
	Int width;
	Int isBlendEdgeTile;
	AsciiString name;
	Int positionX;
	Int positionY;
	char padding20[8];
};

class Rva0074A0D0WorldHeightMap
{
public:
	AsciiString getTerrainNameAt(Real x, Real y);
};

// ?getTerrainNameAt@WorldHeightMap@@QAE?AVAsciiString@@MM@Z
AsciiString Rva0074A0D0WorldHeightMap::getTerrainNameAt(Real x, Real y)
{
	unsigned char *self = (unsigned char *)this;
	Int xIndex = Rva0074A0D0FloorToInt((Real)floor((double)(x * *(const Real *)0x01075C70)));
	Int yIndex = Rva0074A0D0FloorToInt((Real)floor((double)(y * *(const Real *)0x01075C70)));
	xIndex += *(Int *)(self + 0x10);
	yIndex += *(Int *)(self + 0x10);
	if (xIndex < 0) xIndex = 0;
	if (yIndex < 0) yIndex = 0;
	Int width = *(Int *)(self + 0x08);
	if (xIndex >= width) xIndex = width - 1;
	Int height = *(Int *)(self + 0x0c);
	if (yIndex >= height) yIndex = height - 1;
	Int ndx = (yIndex * width) + xIndex;
	if (ndx < 0 || ndx >= *(Int *)(self + 0x20))
		return *(const AsciiString *)0x01336E50;
	Int tileNdx = (*(Short **)(self + 0x8c))[ndx];
	tileNdx = tileNdx >> 2;
	Rva0074A0D0TextureClass *textureClasses =
		(Rva0074A0D0TextureClass *)(self + 0x80c0);
	Int numTextureClasses = *(Int *)(self + 0x80bc);
	Int i;
	for (i = 0; i < numTextureClasses; ++i) {
		if (tileNdx >= textureClasses[i].firstTile &&
			tileNdx < textureClasses[i].firstTile + textureClasses[i].numTiles)
			return textureClasses[i].name;
	}
	return *(const AsciiString *)0x01336E50;
}

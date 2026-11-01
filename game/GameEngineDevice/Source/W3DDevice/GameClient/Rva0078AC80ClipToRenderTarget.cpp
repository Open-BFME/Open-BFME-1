// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
//
// Retail RVA 0x0078AC80 (207 bytes, ret 0x10): a free __stdcall helper that
// clips a screen-space rect against the current render target.  It clamps
// the two input axes at zero into outMin, then for each axis caps the size
// at (render target width - outMin) once outMin plus the requested size
// would pass it.  Retail fetches the height too but compares both axes
// against the width.  No named caller or owner: address-derived name.

typedef bool Bool;
typedef float Real;

#include "Lib/Coord2D.h"

class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &width, int &height,
		int &bitDepth, Bool &windowed);
};

// ?rva0078ac80@@YGXPAUCoord2D@@000@Z
void __stdcall rva0078ac80(Coord2D *in, Coord2D *size, Coord2D *outMin, Coord2D *outSize)
{
	int width = 0;
	int height = 0;
	int bitDepth = 0;
	Bool windowed = false;
	WW3D::Get_Render_Target_Resolution(width, height, bitDepth, windowed);

	outMin->x = (in->x <= 0.0f) ? 0.0f : in->x;
	outMin->y = (in->y <= 0.0f) ? 0.0f : in->y;

	Real screenWidth = (Real)width;
	outSize->x = (outMin->x + size->x > screenWidth) ? screenWidth - outMin->x : size->x;
	outSize->y = (outMin->y + size->y > screenWidth) ? screenWidth - outMin->y : size->y;
}

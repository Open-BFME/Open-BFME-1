// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the bounds initialiser at retail 0x00C6C350, 68 bytes.  There is
// no one-time guard here, so this is a namespace-scope dynamic initialiser
// rather than a function-local static: the two corner temporaries are built on
// the stack right to left and passed by reference.

#include "../../../Libraries/Source/WWVegas/WWMath/region.h"

struct BfmePairYP
{
	BfmePairYP(float x, float y) : X(x), Y(y) {}

	float X;						// +0x00
	float Y;						// +0x04
};
// ??__Eg_bfmeBoxYP@@YAXXZ
Region2D g_bfmeBoxYP((const Coord2D &)BfmePairYP(-3.402823466e+38F, -3.402823466e+38F),
	(const Coord2D &)BfmePairYP(3.402823466e+38F, 3.402823466e+38F));

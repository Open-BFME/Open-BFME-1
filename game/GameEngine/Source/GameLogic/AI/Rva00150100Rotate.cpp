// ?Rva00150100Rotate@@YAXPBUCoord3D@@0PAUCoord2D@@@Z
// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /DNDEBUG /DWIN32 /MD
#include "Lib/BaseType.h"

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern const Real g_rva01075350;
extern Real g_bfmeDefaultBU;

// Retail RVA 0x00150100. The matched waypoint caller reaches it through ILT
// 0x0003D104 with two Coord3D inputs and one Coord2D output. This address-
// derived name keeps the helper's unproven owner and semantic name opaque.
void Rva00150100Rotate(const Coord3D *pB, const Coord3D *pA, Coord2D *vec)
{
	volatile Real scratch[6];
	Real dx = pA->x;
	_ReadWriteBarrier();
	scratch[4] = pA->y;
	dx -= pB->x;
	Real dy = scratch[4];
	dy -= pB->y;
	Real len = (Real)sqrt(dy * dy + dx * dx);
	if (len != g_rva01075350)
	{
		Real scale = g_bfmeDefaultBU / len;
		dx *= scale;
		dy *= scale;
	}
	scratch[0] = -dy;
	scratch[1] = dx;
	Real inputX = vec->x;
	scratch[3] = inputX * dx;
	scratch[4] = inputX * dy;
	Real inputY = vec->y;
	scratch[0] *= inputY;
	scratch[1] *= inputY;
	Real outX = scratch[0];
	outX += scratch[3];
	Real outY = scratch[1];
	outY += scratch[4];
	vec->x = outX;
	vec->y = outY;
}

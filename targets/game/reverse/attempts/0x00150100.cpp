// ?Rva00150100Rotate@@YAXPBUCoord3D@@0PAUCoord2D@@@Z
// partial score=0.3375 date=2026-09-28
// cl: /DNDEBUG /MD

// Retail 0x00150100, 160 bytes. Leaf x87 helper, no calls: two prior blocked
// passes proved the math (rotate a 2D vector by the direction between two
// points, with a minimum-magnitude fallback for near-coincident points) but
// found no named caller, vtable slot, or source owner, so identity stays
// address-derived. Callers (5 sites, all via ILT thunk) include
// d_0014af50.asm/d_00150a70 and d_00177320.asm/d_0017a600.
//
// PARTIAL / banked: the algebra byte-traces exactly (see below) but retail
// reserves a 0x18-byte frame (six spill slots -- pA->y is stashed via an
// INTEGER mov to [esp+0x10] while pA->x stays live on the x87 stack, and
// that same slot is later reused for vx*y once pA->y is dead) while every
// source shape tried here keeps dx/dy/x/y on the FPU register stack and
// only spills one 4-byte slot (`push ecx`, 142-151 B compiled). Multiplication
// order, an explicit outX/outY temp, and `volatile dx/dy` were all tried;
// none forces the wider retail frame. Needs a lever nobody has named yet for
// "MSVC 7.1 spills more x87 temporaries than the value count requires."
//
// Byte-for-byte trace of the retail sequence:
//   dx = pA->x - pB->x;  dy = pA->y - pB->y;  len = sqrt(dx*dx+dy*dy)
//   if (len <= BfmeZeroRange) { k = g_bfmeDefaultBU/len; x=dx*k; y=dy*k; }
//   else                      { x = dx;        y = dy; }
//   outX = vec->x*x - vec->y*y;
//   outY = vec->x*y + vec->y*x;
//   *vec = { outX, outY };

typedef float Real;

struct Coord2D
{
	Real x, y;
};
struct Coord3D
{
	Real x, y, z;
};

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

extern const Real BfmeZeroRange;		// 0x01075350
extern Real g_bfmeDefaultBU;			// 0x01075334
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void Rva00150100Rotate(const Coord3D *pB, const Coord3D *pA, Coord2D *vec)
{
	union Scratch
	{
		struct { Real negY, savedY, unused08, productX, productY, unused14; } products;
		struct { int unused00[4], pAyBits, unused14; } input;
	} temp;
	register Real dx = pA->x;
	register Real dy;
	_ReadWriteBarrier();
	temp.input.pAyBits = *(const int *)&pA->y;
	dx -= pB->x;
	dy = *(const Real *)&temp.input.pAyBits - pB->y;
	Real len = (Real)sqrt(dy * dy + dx * dx);

	Real x, y;
	if (len != BfmeZeroRange)
	{
		Real k = g_bfmeDefaultBU / len;
		y = dy * k;
		x = dx * k;
	}
	else
	{
		x = dx;
		y = dy;
	}

	temp.products.negY = -y;
	temp.products.savedY = x;
	Real vx = vec->x;
	temp.products.productX = vx * x;
	temp.products.productY = vx * y;
	Real vy = vec->y;
	Real outX = temp.products.negY * vy + temp.products.productX;
	Real outY = temp.products.savedY * vy + temp.products.productY;
	vec->x = outX;
	vec->y = outY;
}

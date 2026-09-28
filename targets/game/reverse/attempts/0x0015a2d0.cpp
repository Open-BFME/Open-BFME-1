// ?Rva0015A2D0Rotate@@YAXPBUCoord2D@@0PAU1@@Z
// partial score=0.85 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: static helper at retail 0x0015A2D0 (150 B), called only from
// AIGroup::prepFollow (0x0015AB50, +0x587 and +0x66A) with start in ECX,
// end in EAX and pt in EDX: VC7.1's private register convention for a
// same-TU static.  Declaring the parameters (start, end, pt) reproduces that
// assignment; an extern declaration cannot.  Rotates pt into the frame whose
// x axis is the normalised end-start direction.  Address-derived name.
// Two Coord3D locals reproduce retail's 0x18 frame (perp at -24, dir at -12,
// both z dwords dead).  Remaining 29 bytes: the x*x/y*y operand order inside
// the normalise (+0x15) and retail keeping py live across both perp products
// (+0x70); flag_sweep (90 variants) moves neither.
#include <math.h>
typedef float Real;
struct Coord3D
{
	Real x, y, z;
	Real length2D( void ) const { return (Real)sqrt( x*x + y*y ); }
	void normalize2D( void )
	{
		Real len = length2D();
		if( len != 0 )
		{
			x /= len;
			y /= len;
		}
	}
};

struct Coord2D
{
	Real x, y;
	Real length( void ) const { return (Real)sqrt( x*x + y*y ); }
	void normalize( void )
	{
		Real len = length();
		if( len != 0 )
		{
			x /= len;
			y /= len;
		}
	}
};

static void Rva0015A2D0Rotate(const Coord2D *start, const Coord2D *end, Coord2D *pt)
{
	Coord3D dir;
	dir.x = end->x;
	dir.y = end->y;
	dir.x -= start->x;
	dir.y -= start->y;
	dir.normalize2D();
	dir.y = -dir.y;
	Coord3D perp;
	perp.x = -dir.y;
	perp.y = dir.x;
	Real px = pt->x;
	dir.x *= px;
	dir.y *= px;
	Real py = pt->y;
	perp.x *= py;
	perp.y *= py;
	Coord2D result;
	result.x = perp.x + dir.x;
	result.y = perp.y + dir.y;
	pt->x = result.x;
	pt->y = result.y;
}

// absent-from-retail: TU-local caller that keeps the static alive and gives
// it the private register convention the prepFollow call sites use.
void Rva0015A2D0Caller(const Coord2D *a, const Coord2D *b, Coord2D *p, Coord2D *q)
{
	Rva0015A2D0Rotate(a, b, p);
	Rva0015A2D0Rotate(a, b, q);
}

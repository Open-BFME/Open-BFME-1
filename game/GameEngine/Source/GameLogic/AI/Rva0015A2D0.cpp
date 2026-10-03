// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail RVA 0x0015A2D0, 150 bytes; address-derived identity.
// AIGroup::prepFollow calls this TU-private helper with start=ECX, end=EAX,
// point=EDX. The explicitly absent-from-retail caller below retains the same
// MSVC 7.1 private register convention; only this helper is claimed.
// Genuine EA coordinate types follow AIGroup.cpp's Lib/BaseType.h contract.
// The X square precedes the Y square; the point Y scale remains live in x87
// through both perpendicular products. Both output floats are computed before
// either output store, preserving overlapping-input behavior.
#include "Lib/BaseType.h"

inline void Rva0015A2D0Normalize2D(Coord3D &dir)
{
    Real xSquared = dir.x * dir.x;
    xSquared += dir.y * dir.y;
    Real len = (Real)sqrt(xSquared);
    if (len != 0) {
        dir.x /= len;
        dir.y /= len;
    }
}

static void Rva0015A2D0Rotate(const Coord2D *start, const Coord2D *end, Coord2D *pt)
{
	Coord3D dir;
	dir.x = end->x;
	dir.y = end->y;
	dir.x -= start->x;
	dir.y -= start->y;
	Rva0015A2D0Normalize2D(dir);
	dir.y = -dir.y;
	Coord3D perp;
	perp.x = -dir.y;
	perp.y = dir.x;
	Real px = pt->x;
	dir.x *= px;
	dir.y *= px;
	double py = pt->y;
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

// cl: /DNDEBUG /MD /EHsc
// Retail 0x003D60E0, 152 bytes: the file-scope radial-offset helper of the
// BFME pathfinder.  Its only caller, the tall-building segment check at
// 0x003ECC70, calls it three times with from/insert/to in EAX/EDX/ECX and the
// building and radius on the stack.  Zero Hour's AIPathfind.cpp has the same
// helper (computeNormalRadialOffset); BFME's builds the normal as a 2D vector
// and multiplies by the reciprocal length.  The name keeps the address token.
// Object +0x38 is the position the caller reads the same way.
#include <math.h>

typedef int Int;
typedef bool Bool;
typedef float Real;


struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
};
// Plain two-float holder: retail's Coord2D::length/normalize are owned by
// WWMath/coord2d.cpp, so this TU spells the reciprocal-length math out inline
// instead of declaring a second Coord2D that emits those symbols.
struct Coord2D
{
	Real x, y;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
private:
	char m_beforePosition[0x38];
	Coord3D m_pos;
	char m_beforeGeometryInfo[0xbc - 0x44];
	Real m_boundingCircleRadius;
};

static void rva003d60e0RadialOffset(const Coord3D &from, Coord3D &insert, const Coord3D &to, Object *obj, Real radius)
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Coord3D objPos = *obj->getPosition();
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;
	Real cross = dx * objDy - dy * objDx;
	Coord2D normal;
	if (cross > 0.0f)
	{
		normal.x = dy;
		normal.y = -dx;
	}
	else
	{
		normal.x = -dy;
		normal.y = dx;
	}
	// Coord2D::normalize's body, spelled out (see the struct comment).
	Real normalLen = (Real)sqrt(normal.x * normal.x + normal.y * normal.y);
	if (normalLen != 0.0f)
	{
		Real inv = 1.0f / normalLen;
		normal.x *= inv;
		normal.y *= inv;
	}
	insert = *obj->getPosition();
	insert.x += normal.x * radius;
	insert.y += normal.y * radius;
}

// absent-from-retail: gives the static helper retail's private register
// convention (from in EAX, insert in EDX, to in ECX, object and radius on the
// stack), which MSVC 7.1 picks only for a static function with a TU caller.
// ?rva003D60E0RadialOffsetCaller@@YAXPBUCoord3D@@PAU1@110PAVObject@@M@Z absent-from-retail
void rva003D60E0RadialOffsetCaller(const Coord3D *from, Coord3D *insert1, Coord3D *insert2,
	Coord3D *insert3, const Coord3D *to, Object *obj, Real radius)
{
	rva003d60e0RadialOffset(*from, *insert2, *to, obj, radius);
	rva003d60e0RadialOffset(*from, *insert1, *insert2, obj, radius);
	rva003d60e0RadialOffset(*insert2, *insert3, *to, obj, radius);
}

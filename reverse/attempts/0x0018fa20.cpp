// ?d_0018fa20@@YAXXZ
// partial score=0.97 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /O2 /G6
// NOT PolygonTrigger::pointInTrigger(ICoord3D&) -- that real, caller-proven
// identity is a separate, still-unlanded address (0x0018F8A0, 307B). This is
// a distinct PolygonTrigger method (this+0x10/+0x14/+0x1c/+0x30 match the
// matched updateBounds sibling exactly) taking a Coord3D& (float) point;
// its real name is not recovered. Method renamed to avoid an invented-identity
// collision with the real pointInTrigger symbol.
// Size now matches retail exactly (367B); only 4 non-reloc bytes remain
// (see attempt log): a spilled-reload operand swap immune to source reordering.

#include <algorithm>

typedef bool Bool;
typedef int Int;
typedef float Real;

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class PolygonTrigger
{
public:
	Bool containsPointF(Coord3D &point) const;

protected:
	void updateBounds() const;

private:
	unsigned char m_unmodelled00[0x10];
	ICoord3D *m_points;
	Int m_numPoints;
	Int m_sizePoints;
	mutable IRegion2D m_bounds;
	mutable Real m_radius;
	mutable Bool m_boundsNeedsUpdate;
};

Bool PolygonTrigger::containsPointF(Coord3D &point) const
{
	if (m_boundsNeedsUpdate)
		updateBounds();

	if (point.x < m_bounds.lo.x)
		return false;
	if (point.y < m_bounds.lo.y)
		return false;
	if (point.x > m_bounds.hi.x)
		return false;
	if (point.y > m_bounds.hi.y)
		return false;

	Bool inside = false;
	Int i;
	for (i = 0; i < m_numPoints; ++i) {
		ICoord3D pt1 = m_points[i];
		const ICoord3D *src2 = (i != 0) ? &m_points[i - 1] : &m_points[m_numPoints - 1];
		ICoord3D pt2;
		pt2.x = src2->x;
		pt2.y = src2->y;
		pt2.z = src2->z;
		if (pt1.y == pt2.y)
			continue;

		if (pt1.x < point.x && pt2.x < point.x)
			continue;

		if (pt1.y > pt2.y)
			std::swap(pt1, pt2);
		if (pt2.y < point.y)
			continue;
		if (pt1.y >= point.y)
			continue;

		Int dx = pt2.x - pt1.x;
		Int dy = pt2.y - pt1.y;
		if (dx * (point.y - pt1.y) >= (point.x - pt1.x) * dy)
			inside = !inside;
	}
	return inside;
}

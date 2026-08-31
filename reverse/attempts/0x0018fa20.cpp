// ?d_0018fa20@@YAXXZ
// partial score=0.88 date=2026-08-30
// cl: /DNDEBUG /MD /EHsc /O2 /G6

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
	Bool pointInTrigger(Coord3D &point) const;

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

Bool PolygonTrigger::pointInTrigger(Coord3D &point) const
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
		ICoord3D pt2;
		if (i == m_numPoints - 1)
			pt2 = m_points[0];
		else
			pt2 = m_points[i + 1];

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

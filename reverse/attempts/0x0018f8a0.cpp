// ?pointInTrigger@PolygonTrigger@@QBE_NAAUICoord3D@@@Z
// partial score=0.99 date=2026-09-15
// Scratch copy of reverse/attempts/0x0018f8a0.cpp; do not use as production source.
// ?pointInTrigger@PolygonTrigger@@QBE_NAAUICoord3D@@@Z
// cl: /O2 /G6 /DNDEBUG /MD /EHsc-
// stlport

#include <algorithm>

typedef bool Bool;
typedef int Int;

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
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

// The point array is the PolygonTrigger ICoord3D array witnessed by matched
// callers and updateBounds; the generic TempIndexStruct swap pin is not used
// as coordinate-type evidence.
class PolygonTrigger
{
protected:
	void updateBounds() const;

	unsigned char m_unmodelled00[0x10];
	ICoord3D *m_points;
	Int m_numPoints;
	Int m_sizePoints;
	mutable IRegion2D m_bounds;
	mutable float m_radius;
	mutable Bool m_boundsNeedsUpdate;

public:
	Bool pointInTrigger(ICoord3D &point) const;
};

Bool PolygonTrigger::pointInTrigger(ICoord3D &point) const
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
	for (i = 0; i < m_numPoints; ++i)
	{
		ICoord3D pt1 = m_points[i];
		const ICoord3D *src2 =
			(i != 0) ? &m_points[i - 1] : &m_points[m_numPoints - 1];
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
		const Int pt2x = pt2.x;
		if (pt2.y < point.y)
			continue;
		if (pt1.y >= point.y)
			continue;

		Int dx = pt2x - pt1.x;
		Int dy = pt2.y - pt1.y;
		if (dx * (point.y - pt1.y) >= (point.x - pt1.x) * dy)
			inside = !inside;
	}
	return inside;
}

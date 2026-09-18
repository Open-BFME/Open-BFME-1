// cl: /O2 /G6 /DNDEBUG /MD /EHsc-
// stlport

#include <algorithm>
#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

// BFME float-coordinate overload: the original method name is not recovered.
// Only the three scalar coordinates are used by this TU's ABI view.
struct Coord3D
{
	float x, y, z;
};

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

struct TempIndexStruct
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

class PolygonTrigger
{
protected:
	void updateBounds() const;

	unsigned char m_unmodelled00[0x10];
	TempIndexStruct *m_points;
	Int m_numPoints;
	Int m_sizePoints;
	mutable IRegion2D m_bounds;
	mutable float m_radius;
	mutable Bool m_boundsNeedsUpdate;

public:
	Bool pointInTrigger(ICoord3D &point) const;
	Bool bfmeContainsPointAt0018FA20(Coord3D &point) const;
};

// ?pointInTrigger@PolygonTrigger@@QBE_NAAUICoord3D@@@Z
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
		TempIndexStruct pt1 = m_points[i];
		const TempIndexStruct *previousVertex =
			(i != 0) ? &m_points[i - 1] : &m_points[m_numPoints - 1];
		TempIndexStruct pt2 = *previousVertex;

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
		const Int upperEndpointX = pt2.x;

		if ((upperEndpointX - pt1.x) * (point.y - pt1.y) >=
			(point.x - pt1.x) * (pt2.y - pt1.y))
			inside = !inside;
	}
	return inside;
}

// Full367-byte body at0018FA20, distinct from the integer predicate above.
// The same owner layout and updateBounds call, plus the matched006DFxxx
// callers throughILT0000A7DB, establish this float-coordinate query.
// Keeping the same TempIndexStruct and post-swap x read fixes the old reload
// ordering near miss without changing the arithmetic or adding barriers.
Bool PolygonTrigger::bfmeContainsPointAt0018FA20(Coord3D &point) const
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
		TempIndexStruct pt1 = m_points[i];
		const TempIndexStruct *previousVertex =
			(i != 0) ? &m_points[i - 1] : &m_points[m_numPoints - 1];
		TempIndexStruct pt2 = *previousVertex;

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
		const Int upperEndpointX = pt2.x;

		if ((upperEndpointX - pt1.x) * (point.y - pt1.y) >=
			(point.x - pt1.x) * (pt2.y - pt1.y))
			inside = !inside;
	}
	return inside;
}

// ?updateBounds@PolygonTrigger@@IBEXXZ
void PolygonTrigger::updateBounds() const
{
	const Int BIG_INT = 0x7ffff0;
	m_bounds.lo.x = m_bounds.lo.y = BIG_INT;
	m_bounds.hi.x = m_bounds.hi.y = -BIG_INT;
	Int i;
	for (i = 0; i < m_numPoints; ++i)
	{
		if (m_points[i].x < m_bounds.lo.x)
			m_bounds.lo.x = m_points[i].x;
		if (m_points[i].y < m_bounds.lo.y)
			m_bounds.lo.y = m_points[i].y;
		if (m_points[i].x > m_bounds.hi.x)
			m_bounds.hi.x = m_points[i].x;
		if (m_points[i].y > m_bounds.hi.y)
			m_bounds.hi.y = m_points[i].y;
	}
	m_boundsNeedsUpdate = 0;
	Real halfWidth = (m_bounds.hi.x - m_bounds.lo.x) / 2.0f;
	Real halfHeight = (m_bounds.hi.y + m_bounds.lo.y) / 2.0f;
	m_radius = sqrt(halfHeight * halfHeight + halfWidth * halfWidth);
}

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
		const TempIndexStruct *src2 =
			(i != 0) ? &m_points[i - 1] : &m_points[m_numPoints - 1];
		TempIndexStruct pt2 = *src2;

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
		const Int pt2x = pt2.x;

		if ((pt2x - pt1.x) * (point.y - pt1.y) >=
			(point.x - pt1.x) * (pt2.y - pt1.y))
			inside = !inside;
	}
	return inside;
}

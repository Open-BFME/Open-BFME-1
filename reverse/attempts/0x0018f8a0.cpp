// ?pointInTrigger@PolygonTrigger@@QBE_NAAUICoord3D@@@Z
// partial score=0.9 date=2026-09-11
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

// Retail's swap relocation identifies this local record as TempIndexStruct.
struct TempIndexStruct
{
	Int x;
	Int y;
	Int z;
};

// This declaration exists only to bind the already-converted real callee.
class Rva0018F8A0PolygonTrigger;
class PolygonTrigger
{
	friend class Rva0018F8A0PolygonTrigger;

protected:
	virtual void marker() = 0;
	void updateBounds() const;
};

class Rva0018F8A0PolygonTrigger
{
public:
	virtual void marker() = 0;

protected:
	void updateBounds() const
	{
		reinterpret_cast<const PolygonTrigger *>(this)->updateBounds();
	}

	unsigned char m_unmodelled00[0x0c];
	TempIndexStruct *m_points;
	Int m_numPoints;
	unsigned char m_unmodelled18[4];
	mutable IRegion2D m_bounds;
	mutable float m_radius;
	mutable Bool m_boundsNeedsUpdate;

public:
	Bool pointInTrigger(ICoord3D &point) const;
};

// ?pointInTrigger@PolygonTrigger@@QBE_NAAUICoord3D@@@Z
Bool Rva0018F8A0PolygonTrigger::pointInTrigger(ICoord3D &point) const
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
		TempIndexStruct pt2;
		if (i == 0)
			pt2 = m_points[m_numPoints - 1];
		else
			pt2 = m_points[i - 1];

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

// ?isCellEntryPoint@Bridge@@QAE_NPBURegion2D@@PAM@Z
// partial score=0.429 date=2026-09-17
// Bridge::isCellEntryPoint, retail 0x001A2950.

#include <math.h>

typedef float Real;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D(void) {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}

	Real length(void) const { return (Real)sqrt(x * x + y * y + z * z); }

	void normalize(void)
	{
		Real len = length();
		if (len != 0)
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}
};

struct BridgeInfo
{
	Coord3D from;
	Coord3D to;
	unsigned char m_pad[0x04];
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
};

extern Bool LineInRegion(const Coord2D *p1, const Coord2D *p2,
	const Region2D *clipRegion);
#pragma comment(linker, "/alternatename:?LineInRegion@@YA_NPBUCoord2D@@0PBURegion2D@@@Z=?j_0001ffe1@@YAXXZ")

#define PATHFIND_CELL_SIZE (*(const Real *)0x01075C74)
#define HALF_PATHFIND_CELL_SIZE (*(const Real *)0x01075344)

class Bridge
{
public:
	Bool isCellEntryPoint(const Region2D *cell, Real *entryX);

private:
	unsigned char m_pad[0x0C];
	BridgeInfo m_bridgeInfo;
};

Bool Bridge::isCellEntryPoint(const Region2D *cell, Real *entryX)
{
	Coord3D endVector;
	endVector.x = m_bridgeInfo.fromRight.x - m_bridgeInfo.fromLeft.x;
	endVector.y = m_bridgeInfo.fromRight.y - m_bridgeInfo.fromLeft.y;
	endVector.z = m_bridgeInfo.fromRight.z - m_bridgeInfo.fromLeft.z;
	endVector.normalize();
	endVector.x *= PATHFIND_CELL_SIZE;
	endVector.y *= PATHFIND_CELL_SIZE;

	Coord3D bridgeVector;
	bridgeVector.x = m_bridgeInfo.to.x - m_bridgeInfo.from.x;
	bridgeVector.y = m_bridgeInfo.to.y - m_bridgeInfo.from.y;
	bridgeVector.z = m_bridgeInfo.to.z - m_bridgeInfo.from.z;
	bridgeVector.normalize();
	bridgeVector.x *= HALF_PATHFIND_CELL_SIZE;
	bridgeVector.y *= HALF_PATHFIND_CELL_SIZE;

	Coord3D fromLeft = m_bridgeInfo.fromLeft;
	fromLeft.x -= bridgeVector.x;
	fromLeft.y -= bridgeVector.y;
	fromLeft.x += endVector.x;
	fromLeft.y += endVector.y;

	Coord3D fromRight = m_bridgeInfo.fromRight;
	fromRight.x -= bridgeVector.x;
	fromRight.y -= bridgeVector.y;
	fromRight.x -= endVector.x;
	fromRight.y -= endVector.y;

	Coord3D toLeft = m_bridgeInfo.toLeft;
	toLeft.x += bridgeVector.x;
	toLeft.y += bridgeVector.y;
	toLeft.x += endVector.x;
	toLeft.y += endVector.y;

	Coord3D toRight = m_bridgeInfo.toRight;
	toRight.x += bridgeVector.x;
	toRight.y += bridgeVector.y;
	toRight.x -= endVector.x;
	toRight.y -= endVector.y;

	Coord2D line1, line2;
	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = fromRight.x;
	line2.y = fromRight.y;
	if (LineInRegion(&line1, &line2, cell))
	{
		*entryX = fromLeft.x;
		return true;
	}

	line1.x = toLeft.x;
	line1.y = toLeft.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell))
	{
		*entryX = toLeft.x;
		return true;
	}

	return false;
}

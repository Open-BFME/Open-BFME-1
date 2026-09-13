// cl: /DNDEBUG /MD /EHsc
// Bridge::isCellOnSide, retail 0x001A26D0.

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
	Coord3D(const Coord3D &that) : x(that.x), y(that.y) {}

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
	unsigned char m_pad[0x24];
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
};

extern Bool LineInRegion(const Coord2D *p1, const Coord2D *p2,
	const Region2D *clipRegion);
#pragma comment(linker, "/alternatename:?LineInRegion@@YA_NPBUCoord2D@@0PBURegion2D@@@Z=?j_0001ffe1@@YAXXZ")

#define BRIDGE_SIDE_SCALE (*(const Real *)0x0109C344)

class Bridge
{
public:
	Bool isCellOnSide(const Region2D *cell);

private:
	unsigned char m_pad[0x04];
	BridgeInfo m_bridgeInfo;
};

Bool Bridge::isCellOnSide(const Region2D *cell)
{
	Coord3D endVector;
	endVector.x = m_bridgeInfo.fromRight.x - m_bridgeInfo.fromLeft.x;
	endVector.y = m_bridgeInfo.fromRight.y - m_bridgeInfo.fromLeft.y;
	endVector.z = m_bridgeInfo.fromRight.z - m_bridgeInfo.fromLeft.z;
	endVector.normalize();
	endVector.x *= BRIDGE_SIDE_SCALE;
	endVector.y *= BRIDGE_SIDE_SCALE;

	Coord3D fromLeft = m_bridgeInfo.fromLeft;
	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;

	Coord3D fromRight = m_bridgeInfo.fromRight;
	fromRight.x += endVector.x;
	fromRight.y += endVector.y;

	Coord3D toLeft = m_bridgeInfo.toLeft;
	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;

	Coord3D toRight = m_bridgeInfo.toRight;
	toRight.x += endVector.x;
	toRight.y += endVector.y;

	Coord2D line1, line2;
	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = toLeft.x;
	line2.y = toLeft.y;
	if (LineInRegion(&line1, &line2, cell))
		return true;

	line1.x = fromRight.x;
	line1.y = fromRight.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell))
		return true;

	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;
	fromRight.x += endVector.x;
	fromRight.y += endVector.y;
	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;
	toRight.x += endVector.x;
	toRight.y += endVector.y;

	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = toLeft.x;
	line2.y = toLeft.y;
	if (LineInRegion(&line1, &line2, cell))
		return true;

	line1.x = fromRight.x;
	line1.y = fromRight.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell))
		return true;

	return false;
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Bridge::isCellEntryPoint, retail 0x001A2950 (510 bytes, ret 8).
// Zero Hour's TerrainLogic.cpp body; BFME adds an out parameter that receives
// the z of the entry line's first corner (fromLeft.z or toLeft.z).

#include "basetype.h"

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

#define PATHFIND_CELL_SIZE 10 // retail 10.0f at 0x01075C74; half is 5.0f at 0x01075344

class Bridge
{
public:
	Bool isCellEntryPoint(const Region2D *cell, Real *entryZ);

private:
	unsigned char m_pad[0x0C];
	BridgeInfo m_bridgeInfo;
};

Bool Bridge::isCellEntryPoint(const Region2D *cell, Real *entryZ)
{
	Coord3D endVector;
	endVector.x = m_bridgeInfo.fromRight.x - m_bridgeInfo.fromLeft.x;
	endVector.y = m_bridgeInfo.fromRight.y - m_bridgeInfo.fromLeft.y;
	endVector.z = m_bridgeInfo.fromRight.z - m_bridgeInfo.fromLeft.z;
	{
		Real len = (Real)sqrt(endVector.x * endVector.x +
			endVector.y * endVector.y + endVector.z * endVector.z);
		if (len != 0)
		{
			endVector.x /= len;
			endVector.y /= len;
			endVector.z /= len;
		}
	}
	endVector.x *= PATHFIND_CELL_SIZE;
	endVector.y *= PATHFIND_CELL_SIZE;

	Coord3D bridgeVector;
	bridgeVector.x = m_bridgeInfo.to.x - m_bridgeInfo.from.x;
	bridgeVector.y = m_bridgeInfo.to.y - m_bridgeInfo.from.y;
	bridgeVector.z = m_bridgeInfo.to.z - m_bridgeInfo.from.z;
	{
		Real len = (Real)sqrt(bridgeVector.x * bridgeVector.x +
			bridgeVector.y * bridgeVector.y + bridgeVector.z * bridgeVector.z);
		if (len != 0)
		{
			bridgeVector.x /= len;
			bridgeVector.y /= len;
			bridgeVector.z /= len;
		}
	}
	bridgeVector.x *= PATHFIND_CELL_SIZE/2;
	bridgeVector.y *= PATHFIND_CELL_SIZE/2;

	Coord3D fromLeft;
	fromLeft.x = m_bridgeInfo.fromLeft.x;
	fromLeft.y = m_bridgeInfo.fromLeft.y;
	fromLeft.z = m_bridgeInfo.fromLeft.z;
	fromLeft.x -= bridgeVector.x;
	fromLeft.y -= bridgeVector.y;
	fromLeft.x += endVector.x;
	fromLeft.y += endVector.y;

	Coord3D fromRight;
	fromRight.x = m_bridgeInfo.fromRight.x;
	fromRight.y = m_bridgeInfo.fromRight.y;
	fromRight.z = m_bridgeInfo.fromRight.z;
	fromRight.x -= bridgeVector.x;
	fromRight.y -= bridgeVector.y;
	fromRight.x -= endVector.x;
	fromRight.y -= endVector.y;

	Coord3D toLeft;
	toLeft.x = m_bridgeInfo.toLeft.x;
	toLeft.y = m_bridgeInfo.toLeft.y;
	toLeft.z = m_bridgeInfo.toLeft.z;
	toLeft.x += bridgeVector.x;
	toLeft.y += bridgeVector.y;
	toLeft.x += endVector.x;
	toLeft.y += endVector.y;

	Coord3D toRight;
	toRight.x = m_bridgeInfo.toRight.x;
	toRight.y = m_bridgeInfo.toRight.y;
	toRight.z = m_bridgeInfo.toRight.z;
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
		*entryZ = fromLeft.z;
		return true;
	}

	line1.x = toLeft.x;
	line1.y = toLeft.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell))
	{
		*entryZ = toLeft.z;
		return true;
	}

	return false;
}

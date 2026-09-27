// ?rva003F82C0@Pathfinder@@QAEXHHPAVPathfindCell@@PAVBridge@@_N0M@Z
// partial score=0.84 date=2026-09-27
// ?rva003F82C0@Pathfinder@@QAEXHHPAVPathfindCell@@PAVBridge@@_N0M@Z
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x, y;
	Real z;
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	~Coord3D() {}
};

struct ICoord2D
{
	Int x, y;
};

struct Coord2D
{
	Real x, y;
};

struct Region2D
{
	Coord2D lo, hi;
};

struct Coord3DStorage
{
	Real x, y, z;
};

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

class Object;

class GameLogic
{
public:
	Object *findObjectByID(Int objectID);
};

class Bridge
{
public:
	Bool isPointOnBridge(const Coord3D *point);
	Bool isCellOnEnd(const Region2D *cell);
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);
};

class PathfindCellInfo
{
public:
	unsigned char m_pad[0x20];
	Int m_obstacleID;
};

class PathfindCell
{
public:
	Int getType(void) const { return m_packed & 7; }
	Int getLayer(void) const { return (m_packed >> 6) & 0x3f; }

	PathfindCellInfo *m_info;
	unsigned char m_pad04[8];
	unsigned int m_packed;
};

class Rva003F7380State
{
public:
	void resetIfMatching(const void *argument);
};

class Gen_003F68B0
{
public:
	void bfmeSetMode(unsigned int mode);
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 1
};

class Rva003F82C0LayerHeight
{
public:
	Real call(PathfindLayerEnum layer, const Coord3D *point, Coord3D *normal);
};

extern void j_00029f3c();

__forceinline Real rva003F82C0GetLayerHeight(void *pathfinder,
	PathfindLayerEnum layer, const Coord3D *point, Coord3D *normal)
{
	union
	{
		void (*asFunction)();
		Real (Rva003F82C0LayerHeight::*asMember)(PathfindLayerEnum,
			const Coord3D *, Coord3D *);
	} fnCast;
	fnCast.asFunction = j_00029f3c;
	return (reinterpret_cast<Rva003F82C0LayerHeight *>(pathfinder)->*fnCast.asMember)(
		layer, point, normal);
}

class Pathfinder
{
public:
	void rva003F82C0(Int cellX, Int cellY, PathfindCell *cell,
		Bridge *theBridge, Bool keep, PathfindCell *bridgeCell, Real height);

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	ICoord2D m_extentLo;
	ICoord2D m_extentHi;
};

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F (*(const Real *)0x01075C74)
#define BRIDGE_CLEARANCE (*(const Real *)0x010888F0)
#define THE_GAME_LOGIC (*(GameLogic **)0x012F0898)

void Pathfinder::rva003F82C0(Int cellX, Int cellY, PathfindCell *cell,
	Bridge *theBridge, Bool keep, PathfindCell *bridgeCell, Real height)
{
	Coord3D topLeftCorner, point, bottomRightCorner;

	topLeftCorner.y = (Real)(cellY * PATHFIND_CELL_SIZE);
	bottomRightCorner.y = topLeftCorner.y + PATHFIND_CELL_SIZE_F;
	topLeftCorner.x = (Real)(cellX * PATHFIND_CELL_SIZE);
	bottomRightCorner.x = topLeftCorner.x + PATHFIND_CELL_SIZE_F;
	topLeftCorner.z = 0.0f;
	bottomRightCorner.z = 0.0f;
	register Int bridgeCount = 0;
	if (theBridge->isPointOnBridge(&topLeftCorner))
		bridgeCount = 1;
	point = topLeftCorner;
	point.y = bottomRightCorner.y;
	if (theBridge->isPointOnBridge(&point))
		bridgeCount++;
	if (theBridge->isPointOnBridge(&bottomRightCorner))
		bridgeCount++;
	point = topLeftCorner;
	point.x = bottomRightCorner.x;
	if (theBridge->isPointOnBridge(&point))
		bridgeCount++;

	if (keep)
	{
		if (bridgeCount != 0 && cell->getType() == 4)
		{
			PathfindCellInfo *info = cell->m_info;
			Int obstacleID = info != 0 ? info->m_obstacleID : 0;
			Object *obstacle = THE_GAME_LOGIC->findObjectByID(obstacleID);
			if (obstacle != 0)
				((Rva003F7380State *)cell)->resetIfMatching(obstacle);
		}

		if (bridgeCount > 0)
			cell->m_packed |= 0x100000;

		if (bridgeCount == 4)
		{
			cell->m_packed = (cell->m_packed & 0xff3c043f) | 0x400;
			((Gen_003F68B0 *)cell)->bfmeSetMode(0);
			cell->m_packed &= 0xfffbffff;
			return;
		}
		if (bridgeCount == 0)
			return;
	}
	else
	{
		cell->m_packed &= 0xffefffff;
		Int surroundingCount = 0;
		Int surroundingLayer = 1;
		for (Int x = cellX - 1; x < cellX + 2; ++x)
		{
			if (x < m_extentLo.x || x > m_extentHi.x)
				continue;
			for (Int y = cellY - 1; y < cellY + 2; ++y)
			{
				if (y < m_extentLo.y || y > m_extentHi.y)
					continue;
				if (x == cellX && y == cellY)
					continue;
				PathfindCell *adjacent = &m_map[x][y];
				Int layer = adjacent->getLayer();
				if (layer > 0x10)
				{
					++surroundingCount;
					surroundingLayer = layer;
				}
			}
		}

		Int cellLayer = cell->getLayer();
		if (cellLayer == 0x10)
		{
			if (bridgeCount == 4 && surroundingCount >= 3)
			{
				unsigned int layerBits = ((unsigned int)surroundingLayer << 6) & 0xfc0;
				cell->m_packed = (cell->m_packed & 0xfffff03f) | layerBits;
				cell->m_packed &= 0xfffc0fff;
				return;
			}
			if (surroundingCount >= 3)
			{
				cell->m_packed = (cell->m_packed & 0xfffff07f) | 0x40;
				((Gen_003F68B0 *)cell)->bfmeSetMode(0);
			}
			else
			{
				((Gen_003F68B0 *)cell)->bfmeSetMode(5);
			}
		}
		else if (cellLayer != 1)
		{
			((Gen_003F68B0 *)cell)->bfmeSetMode(5);
		}
		cell->m_packed &= 0xfffc0fff;
		return;
	}

	union
	{
		Region2D cellBounds;
		Coord3DStorage center;
	} bridgeGeometry;
	{
		bridgeGeometry.cellBounds.lo.x = topLeftCorner.x;
		bridgeGeometry.cellBounds.lo.y = topLeftCorner.y;
		bridgeGeometry.cellBounds.hi.x = bottomRightCorner.x;
		bridgeGeometry.cellBounds.hi.y = bottomRightCorner.y;
		if (!theBridge->isCellOnEnd(&bridgeGeometry.cellBounds))
		{
			cell->m_packed = (cell->m_packed & 0xfffc043f) | 0x400;
			((Gen_003F68B0 *)cell)->bfmeSetMode(5);
			return;
		}
	}

	bridgeGeometry.center.x = topLeftCorner.x;
	bridgeGeometry.center.y = topLeftCorner.y;
	bridgeGeometry.center.z = topLeftCorner.z;
	bridgeGeometry.center.x += PATHFIND_CELL_SIZE_F * 0.5f;
	bridgeGeometry.center.y += PATHFIND_CELL_SIZE_F * 0.5f;
	Real groundHeight = rva003F82C0GetLayerHeight(this,
		(PathfindLayerEnum)cell->getLayer(),
		(const Coord3D *)&bridgeGeometry.center, 0);
	Real bridgeHeight = theBridge->getBridgeHeight(
		(const Coord3D *)&bridgeGeometry.center, 0);
	if (bridgeCell != 0)
	{
		if ((Real)fabs((double)(height - bridgeHeight)) < BRIDGE_CLEARANCE)
		{
			cell->m_packed = (cell->m_packed & 0xfffff43f) | 0x400;
			cell->m_packed = (cell->m_packed & ~0x3f000) |
				(bridgeCell->m_packed << 6 & 0x3f000);
			bridgeCell->m_packed = (bridgeCell->m_packed & ~0x3f000) |
				(cell->m_packed << 6 & 0x3f000);
			((Gen_003F68B0 *)bridgeCell)->bfmeSetMode(0);
			((Gen_003F68B0 *)cell)->bfmeSetMode(0);
			cell->m_packed &= 0xff3fffff;
			return;
		}
	}
	else if ((Real)fabs((double)(groundHeight - bridgeHeight)) < BRIDGE_CLEARANCE)
	{
		((Gen_003F68B0 *)cell)->bfmeSetMode(0);
		cell->m_packed = (cell->m_packed & 0xff3d0fff) | 0x10000;
		return;
	}

	cell->m_packed = (cell->m_packed & 0xfffc043f) | 0x400;
	((Gen_003F68B0 *)cell)->bfmeSetMode(0);
}

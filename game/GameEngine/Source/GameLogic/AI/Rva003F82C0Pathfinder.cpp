// ?rva003F82C0@Pathfinder@@QAEXHHPAVPathfindCell@@PAVBridge@@_N0M@Z
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x003F82C0, 1044 bytes (ret 0x1c at +0x411).
//
// Identity: the only caller is the matched Pathfinder::rva003F8820
// (Rva003F8820Pathfinder.cpp), which calls this body through its ILT thunk
// ?j_0001a523@@YAXXZ with ECX = the Pathfinder and seven stack arguments
// (cellX, cellY, cell, bridge, keep, bridgeCell, height). ECX is used here as
// the same Pathfinder (m_map@+0x10, m_extent@+0x14, and it is the receiver of
// the matched Pathfinder::getLayerHeight). No string or Zero Hour twin names
// the method, so the name keeps the address token. It is BFME's per-cell bridge
// classifier: the four isPointOnBridge corner probes follow ZH
// PathfindLayer::classifyLayerMapCell, the rest is BFME-only.
//
// The packed cell dword at +0x0c uses the matched neighbour's accessors
// (type = bits 0..2, layer = bits 6..11). Mode changes go through the matched
// setter ?bfmeSetMode@Gen_003F68B0@@QAEXI@Z and the obstacle reset through the
// matched ?resetIfMatching@Rva003F7380State@@..., both called on the cell as
// retail does (their owner classes are those ledger rows' names). The two
// float constants are retail's 10.0f (0x01075C74) and 15.0f (0x010888F0).
//
// Shape notes: the four-corner count lives in ESI with a stack home because
// the ZH "bridgeCount++" form is kept; the bridgeCount == 4 arm is an if/else
// around the rest of the keep path (a plain early return reverses retail's
// tail merge with the final "mark as layer 16" arm); the not-on-end arm comes
// after the height tests; the layer-insert arm falls through to the shared
// final clear, which is why retail stores the cell dword twice there.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord2D { Real x, y; };
struct Region2D { Coord2D lo, hi; };
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

// Same declaration as the matched caller's TU (Rva003F8820Pathfinder.cpp).
struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	~Coord3D() {}
};

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

class Object;

class GameLogic
{
public:
	Object *findObjectByID(Int objectID);
};
extern GameLogic *TheGameLogic;

class Bridge
{
public:
	Bool isPointOnBridge(const Coord3D *point);
	Bool isCellOnEnd(const Region2D *cell);
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);
};

// Owner class of the matched setter ?bfmeSetMode@Gen_003F68B0@@QAEXI@Z
// (retail 0x003F68B0); retail calls it on a PathfindCell.
class Gen_003F68B0
{
public:
	void bfmeSetMode(UnsignedInt mode);
};

// Owner of the matched ?resetIfMatching@Rva003F7380State@@QAEXPBURva003F7380Argument@@@Z
// (retail 0x003F7380); retail calls it on the cell with the obstacle Object.
struct Rva003F7380Argument;
class Rva003F7380State
{
public:
	void resetIfMatching(const Rva003F7380Argument *argument);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	unsigned char m_pad00[0x20];
	Int m_obstacleID;	// +0x20, as PathfindObstacleCallbackDebb0.cpp; ZH getObstacleID() shape
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// Retail 16-byte cell: packed dword@+0x0c, type:3@0, layer:6@6.
class PathfindCell
{
public:
	Int getLayer(void) const { return (Int)((m_packed >> 6) & 0x3f); }
	Int getType(void) const { return (Int)(m_packed & 7); }

	PathfindCellInfo *m_info;
	Int m_at04;
	Int m_at08;
	UnsignedInt m_packed;
};

enum PathfindLayerEnum { LAYER_INVALID = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void rva003F82C0(Int cellX, Int cellY, PathfindCell *cell, Bridge *theBridge,
		Bool keep, PathfindCell *bridgeCell, Real height);
	Real getLayerHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);

	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
};

void Pathfinder::rva003F82C0(Int cellX, Int cellY, PathfindCell *cell, Bridge *theBridge,
	Bool keep, PathfindCell *bridgeCell, Real height)
{
	Coord3D topLeftCorner, bottomRightCorner;

	topLeftCorner.y = (Real)(cellY * 10);
	bottomRightCorner.y = topLeftCorner.y + 10.0f;
	topLeftCorner.x = (Real)(cellX * 10);
	bottomRightCorner.x = topLeftCorner.x + 10.0f;
	topLeftCorner.z = 0.0f;
	bottomRightCorner.z = 0.0f;

	Int bridgeCount = 0;
	Coord3D pt;
	if (theBridge->isPointOnBridge(&topLeftCorner))
		bridgeCount++;
	pt = topLeftCorner;
	pt.y = bottomRightCorner.y;
	if (theBridge->isPointOnBridge(&pt))
		bridgeCount++;
	if (theBridge->isPointOnBridge(&bottomRightCorner))
		bridgeCount++;
	pt = topLeftCorner;
	pt.x = bottomRightCorner.x;
	if (theBridge->isPointOnBridge(&pt))
		bridgeCount++;

	if (keep)
	{
		if (bridgeCount != 0 && cell->getType() == 4)
		{
			PathfindCellInfo *info = cell->m_info;
			Object *obstacle = TheGameLogic->findObjectByID(info ? info->m_obstacleID : 0);
			if (obstacle)
				((Rva003F7380State *)cell)->resetIfMatching(
					(const Rva003F7380Argument *)obstacle);
		}
		if (bridgeCount > 0)
			cell->m_packed |= 0x100000;
		if (bridgeCount == 4)
		{
			cell->m_packed = (cell->m_packed & 0xff3c043f) | 0x400;
			((Gen_003F68B0 *)cell)->bfmeSetMode(0);
			cell->m_packed &= 0xfffbffff;
		}
		else
		{
			if (bridgeCount == 0)
				return;

			Region2D cellBounds;
			cellBounds.lo.x = topLeftCorner.x;
			cellBounds.lo.y = topLeftCorner.y;
			cellBounds.hi.x = bottomRightCorner.x;
			cellBounds.hi.y = bottomRightCorner.y;
			if (theBridge->isCellOnEnd(&cellBounds))
			{
				Real groundHeight = getLayerHeight((PathfindLayerEnum)cell->getLayer(), &topLeftCorner, 0);
				Real bridgeHeight = theBridge->getBridgeHeight(&topLeftCorner, 0);
				if (bridgeCell && (Real)fabs(bridgeHeight - height) < 15.0f)
				{
					cell->m_packed = (cell->m_packed & 0xfffff43f) | 0x400;
					cell->m_packed = (cell->m_packed & ~0x3f000) | ((bridgeCell->m_packed << 6) & 0x3f000);
					bridgeCell->m_packed = (bridgeCell->m_packed & ~0x3f000) | ((cell->m_packed << 6) & 0x3f000);
					((Gen_003F68B0 *)bridgeCell)->bfmeSetMode(0);
					((Gen_003F68B0 *)cell)->bfmeSetMode(0);
					cell->m_packed &= 0xff3fffff;
					return;
				}
				if ((Real)fabs(groundHeight - bridgeHeight) < 15.0f)
				{
					((Gen_003F68B0 *)cell)->bfmeSetMode(0);
					cell->m_packed = (cell->m_packed & 0xff3d0fff) | 0x10000;
					return;
				}
				cell->m_packed = (cell->m_packed & 0xff3c043f) | 0x400;
				((Gen_003F68B0 *)cell)->bfmeSetMode(0);
				cell->m_packed &= 0xfffbffff;
				return;
			}
			cell->m_packed = (cell->m_packed & 0xfffc043f) | 0x400;
			((Gen_003F68B0 *)cell)->bfmeSetMode(5);
			return;
		}
	}
	else
	{
		if (bridgeCount != 0)
		{
			cell->m_packed = cell->m_packed & 0xffefffff;
			Int surroundingCount = 0;
			Int surroundingLayer = 1;
			for (Int x = cellX - 1; x < cellX + 2; ++x)
			{
				if (x < m_extent.lo.x || x > m_extent.hi.x)
					continue;
				for (Int y = cellY - 1; y < cellY + 2; ++y)
				{
					if (y < m_extent.lo.y || y > m_extent.hi.y)
						continue;
					if (x == cellX && cellY == y)
						continue;
					Int layer = m_map[x][y].getLayer();
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
				if (bridgeCount != 4 && surroundingCount >= 3)
				{
					cell->m_packed = (cell->m_packed & ~0xfc0) | ((surroundingLayer << 6) & 0xfc0);
				}
				else
				{
					cell->m_packed = (cell->m_packed & 0xfffff07f) | 0x40;
					((Gen_003F68B0 *)cell)->bfmeSetMode(0);
				}
			}
			else if (cellLayer != 1)
			{
				((Gen_003F68B0 *)cell)->bfmeSetMode(5);
			}
			cell->m_packed &= 0xfffc0fff;
			return;
		}
		if (cell->getType() == 2)
			((Gen_003F68B0 *)cell)->bfmeSetMode(0);
		return;
	}
}

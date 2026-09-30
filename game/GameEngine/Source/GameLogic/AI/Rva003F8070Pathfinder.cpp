// ?rva003F8070@Pathfinder@@QAE_NHHPAVPathfindCell@@PAVPolygonTrigger@@H_N@Z
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x003F8070, 464 bytes: per-cell polygon-area layer classifier; the only caller (0x003F9310 via ILT 0x0001E781)
// passes ECX = the Pathfinder (m_map@+0x10) and six stack args. No string or ZH twin names it, so the name keeps the address.
// Corner probes follow ZH PathfindLayer::classifyLayerMapCell; m_layerHeights@+0x243B8 as PathfinderGetLayerHeight.cpp.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

struct ICoord3D
{
	Int x, y, z;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(Int objectID);
};
extern GameLogic *TheGameLogic;

class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
};

class Gen_003F68B0
{
public:
	void bfmeSetMode(UnsignedInt mode);
};

struct Rva003F7380Argument;
class Rva003F7380State
{
public:
	void resetIfMatching(const Rva003F7380Argument *argument);
};

class PathfindCellInfo
{
public:
	unsigned char m_pad00[0x20];
	Int m_obstacleID;
};

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

class Pathfinder
{
public:
	Bool rva003F8070(Int cellX, Int cellY, PathfindCell *cell, PolygonTrigger *trigger,
		Int layer, Bool keep);

	unsigned char m_pad00[0x243B8];
	Real m_layerHeights[64];
};

Bool Pathfinder::rva003F8070(Int cellX, Int cellY, PathfindCell *cell, PolygonTrigger *trigger,
	Int layer, Bool keep)
{
	ICoord3D topLeftCorner, bottomRightCorner;

	topLeftCorner.y = cellY * 10;
	bottomRightCorner.y = topLeftCorner.y + 10;
	topLeftCorner.x = cellX * 10;
	bottomRightCorner.x = topLeftCorner.x + 10;

	Int count = 0;
	ICoord3D pt;
	if (trigger->pointInTrigger(topLeftCorner))
		count++;
	pt = topLeftCorner;
	pt.y = bottomRightCorner.y;
	if (trigger->pointInTrigger(pt))
		count++;
	if (trigger->pointInTrigger(bottomRightCorner))
		count++;
	pt = topLeftCorner;
	pt.x = bottomRightCorner.x;
	if (trigger->pointInTrigger(pt))
		count++;

	if (count == 0)
		return false;

	if (keep)
	{
		Int cellLayer = cell->getLayer();
		if (cellLayer < 0x11 || cellLayer > 0x40 || m_layerHeights[cellLayer] < m_layerHeights[layer])
			cell->m_packed = (cell->m_packed & ~0xfc0) | ((layer << 6) & 0xfc0);
		cell->m_packed &= 0xfffc0fff;
		if (cell->getType() == 4)
		{
			PathfindCellInfo *info = cell->m_info;
			Object *obstacle = TheGameLogic->findObjectByID(info ? info->m_obstacleID : 0);
			if (obstacle)
				((Rva003F7380State *)cell)->resetIfMatching(
					(const Rva003F7380Argument *)obstacle);
		}
		((Gen_003F68B0 *)cell)->bfmeSetMode(0);
		cell->m_packed = (cell->m_packed & 0xfffbffff) | 0x100000;
		return true;
	}

	if (count == 4)
	{
		cell->m_packed = (cell->m_packed & 0xfffff07f) | 0x40;
		if (cell->getType() != 4)
			((Gen_003F68B0 *)cell)->bfmeSetMode(0);
		cell->m_packed &= 0xfffc0fff;
	}
	else if (cell->getType() == 5)
	{
		cell->m_packed = (cell->m_packed & 0xfffff07f) | 0x40;
		((Gen_003F68B0 *)cell)->bfmeSetMode(0);
		cell->m_packed &= 0xfffc0fff;
	}
	cell->m_packed &= 0xffefffff;
	return true;
}

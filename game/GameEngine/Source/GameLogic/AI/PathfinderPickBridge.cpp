// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003D8C40 (1502 bytes): Pathfinder::bfmePickBridge.
//
// Identity: TerrainLogic::pickBridge (TerrainLogicBridges.cpp) and
// doSetRallyPoint (both matched) call it through an ILT thunk as a
// Bool __thiscall taking (const Vector3 &, const Vector3 &, Vector3 *), ret 0xC.
// Extent: the scaffold row stopped at the first `ret 0xc` (+0x5D3, 1494 B), but
// the final `jp` at +0x5C9 targets the return-false tail
// `xor eax,eax / add esp,0x6c / ret 0xc` at +0x5D6..+0x5DD, so the body is
// 1502 bytes; the 8 tail bytes were unclaimed.
//
// Shape: the first loop is Zero Hour's TerrainLogic::pickBridge walk over a
// Bridge list (the Bridge list head moved onto the Pathfinder at +0x858); the
// two height-slice loops intersect the from->to segment with each bridge
// height (+0x243F8 count, inline Real array at +0x243FC; cells on layer
// i + 0x11) and each active layer's plane (+0x3C, +0x40), using Zero Hour's
// inline Pathfinder::getCell(layer, pos) / getCell(layer, x, y).
// PathfindLayer::getCell is visible (non-inlined, as in retail's AIPathfind.cpp
// where it is an ordinary out-of-line member at 0x003FBAB0); with it opaque,
// VC7.1 swaps the this/bridge callee-saved registers.

#include "vector3.h"

typedef float Real;
typedef bool Bool;
typedef int Int;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
struct Coord3D { Real x, y, z; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

// upstream layout: inputs/reference/shims/pathfind/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getType(void) const { return m_packed & 0x7; }
	Int getLayer(void) const { return (m_packed >> 6) & 0x3f; }
private:
	void *m_info;
	Int m_unused1;
	Int m_unused2;
	unsigned int m_packed;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	Bridge *getNext(void) { return m_next; }
private:
	void *m_vtbl;
	Bridge *m_next;
};

// upstream layout: inputs/reference/shims/pathfind/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	// Retail 0x003FBAB0, matched in pathfind_getcell.cpp; kept out of line.
	inline __declspec(noinline) PathfindCell *getCell(Int cellX, Int cellY)
	{
		if (m_layerCells == 0)
			return 0;
		cellX -= m_xOrigin;
		cellY -= m_yOrigin;
		if (cellX < 0 || cellX >= m_width)
			return 0;
		if (cellY < 0 || cellY >= m_height)
			return 0;
		PathfindCell *cell = &m_layerCells[cellX][cellY];
		if (cell->getType() == 5)
			return 0;
		return cell;
	}
	Bool isActive(void) const { return m_active != 0; }
	Int getLayerHeight(void) const { return m_layerHeight; }
private:
	void *m_blockOfMapCells;        // +0x00
	PathfindCell **m_layerCells;    // +0x04
	Int m_width;                    // +0x08
	Int m_height;                   // +0x0c
	Int m_xOrigin;                  // +0x10
	Int m_yOrigin;                  // +0x14
	unsigned char m_tail[0x3c - 0x18];
	void *m_active;                 // +0x3c
	Int m_layerHeight;              // +0x40
};

// upstream layout: inputs/reference/shims/pathfind/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			PathfindCell *cell = 0;
			if (layer > LAYER_GROUND && layer <= LAYER_LAST)
			{
				cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}

	PathfindCell *getCell(PathfindLayerEnum layer, const Coord3D *pos)
	{
		ICoord2D cell;
		Bool overflow = worldToCell(pos, &cell);
		if (overflow)
			return 0;
		return getCell(layer, cell.x, cell.y);
	}

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;                 // +0x10
	IRegion2D m_extent;                   // +0x14
	unsigned char m_mid[0x858 - 0x24];
	Bridge *m_bridgeList;                 // +0x858
	PathfindLayer m_layers[16];           // +0x85c
	unsigned char m_gap[0x243f8 - 0xc9c];
	Int m_bridgeHeightCount;              // +0x243f8
	Real m_bridgeHeights[1];              // +0x243fc
};

Bool Pathfinder::bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos)
{
	Real bestDist = 3.402823466e+38f;
	for (Bridge *bridge = m_bridgeList; bridge; bridge = bridge->getNext())
	{
		Vector3 curPos;
		if (bridge->pickBridge(from, to, &curPos))
		{
			Real dist = Vector3::Quick_Distance(curPos, from);
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = curPos;
			}
		}
	}

	Int i;
	for (i = 0; i < m_bridgeHeightCount; i++)
	{
		Vector3 delta = to - from;
		Real t = (m_bridgeHeights[i] - from.Z) / delta.Z;
		Vector3 hitPos = from + delta * t;
		Coord3D pt;
		pt.x = hitPos.X;
		pt.y = hitPos.Y;
		pt.z = hitPos.Z;
		PathfindCell *cell = getCell(LAYER_GROUND, &pt);
		if (cell && cell->getLayer() == i + 0x11 && cell->getType() == 0)
		{
			Real dist = Vector3::Quick_Distance(hitPos, from);
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hitPos;
			}
		}
	}

	for (i = 2; i <= LAYER_LAST; i++)
	{
		if (!m_layers[i].isActive())
			continue;
		Vector3 delta = to - from;
		Real t = ((Real)m_layers[i].getLayerHeight() - from.Z) / delta.Z;
		Vector3 hitPos = from + delta * t;
		Coord3D pt;
		pt.x = hitPos.X;
		pt.y = hitPos.Y;
		pt.z = hitPos.Z;
		PathfindCell *cell = getCell((PathfindLayerEnum)i, &pt);
		if (cell && cell->getLayer() == i && cell->getType() == 0)
		{
			Real dist = Vector3::Quick_Distance(hitPos, from);
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hitPos;
			}
		}
	}
	return bestDist < 3.402823466e+38f;
}

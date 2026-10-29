// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
// PathfindLayer::classifyCells, retail 0x003FC790 (1405 bytes).

#include <math.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;
typedef float Real;
typedef bool Bool;

#define g_bfmeDefaultBU 1.0f
#define g_bfmeDirectionWeight1285 10.0f
#define g_bfmeScaleBK 0.1f

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_WALL = 15
};

struct ICoord2D
{
	Int x;
	Int y;
};

#include "Lib/Coord2D.h"

#include "Lib/Coord3D.h"

// ?Rva003FC790Set@@YAXPAUCoord3D@@PBU1@@Z absent-from-retail
static __forceinline void Rva003FC790Set(Coord3D *destination, const Coord3D *source)
{
	destination->x = source->x;
	destination->y = source->y;
	destination->z = source->z;
}

// ?length@@YAMABUCoord3D@@@Z absent-from-retail
static __forceinline Real length(const Coord3D &v)
{
	return (Real)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// ?normalize@@YAXAAUCoord3D@@@Z absent-from-retail
static __forceinline void normalize(Coord3D &v)
{
	Real len = length(v);
	if (len != 0.0f) {
		Real scale = 1.0f / len;
		v.x *= scale;
		v.y *= scale;
		v.z *= scale;
	}
}

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct BridgeInfo
{
	BridgeInfo(void);

	Coord3D from;
	Coord3D to;
	Real bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
	unsigned char m_tail[0x6c - 0x4c];
};

class Bridge
{
public:
	Bool isPointOnBridge(const Coord3D *point);
	Bool isCellOnSide(const Region2D *cell);
	Bool isCellOnEnd(const Region2D *cell);
	Bool isCellEntryPoint(const Region2D *cell, Real *entryZ);
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);

	void getBridgeInfo(BridgeInfo *info)
	{
		*info = m_bridgeInfo;
	}

private:
	unsigned char m_prefix[0x0c];
	BridgeInfo m_bridgeInfo;
};


class Gen_003F68B0
{
public:
	void bfmeSetMode(unsigned int mode);
};

class PathfindCellInfo;

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_OBSTACLE = 4,
		CELL_IMPASSABLE = 5,
		CELL_BRIDGE_IMPASSABLE = 6
	};

	void reset(void);

	void setLayer(PathfindLayerEnum layer)
	{
		m_layer = (unsigned int)layer;
	}

	PathfindLayerEnum getLayer(void) const
	{
		return (PathfindLayerEnum)m_layer;
	}

	void setConnectLayer(PathfindLayerEnum layer)
	{
		m_connectsToLayer = (unsigned int)layer;
	}

	PathfindLayerEnum getConnectLayer(void) const
	{
		return (PathfindLayerEnum)m_connectsToLayer;
	}

	CellType getType(void) const
	{
		return (CellType)m_type;
	}

private:
	PathfindCellInfo *m_info;
	int m_zoneAndGoals;
	unsigned short m_cellTypeAndUnitFlags;
	unsigned short m_layerFlags;
	unsigned int m_type:3;
	unsigned int m_unitFlags:3;
	unsigned int m_layer:6;
	unsigned int m_connectsToLayer:6;
	unsigned int m_unused:14;
};

// PathfindCell::setType is retail 0x003F68B0, matched as Gen_003F68B0::bfmeSetMode.
// A file-static forwarder: a member setType here would emit a non-retail
// COMDAT of that name (or bind only through the pin).
static inline void setType(PathfindCell *cell, PathfindCell::CellType type)
{
	((Gen_003F68B0 *)cell)->bfmeSetMode((unsigned int)type);
}

// Pathfinder::getCell(layer, x, y) is retail 0x003D4E80, matched in
// PathfindCheckDestination.cpp; retail inlines it here. A file-static
// forwarder: a member here emitted a non-retail COMDAT of that name.
class Pathfinder
{
public:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	Int m_lowX;
	Int m_lowY;
	Int m_highX;
	Int m_highY;
};

static inline PathfindCell *pathfinderGetCell(Pathfinder *pathfinder, PathfindLayerEnum layer, Int x, Int y)
{
	(void)layer;
	if (x < pathfinder->m_lowX || x > pathfinder->m_highX || y < pathfinder->m_lowY || y > pathfinder->m_highY) {
		return 0;
	}
	return &pathfinder->m_map[x][y];
}

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return m_pathfinder;
	}

private:
	unsigned char m_prefix[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void slot0(void) {}
	virtual void slot1(void) {}
	virtual void slot2(void) {}
	virtual void slot3(void) {}
	virtual void slot4(void) {}
	virtual void slot5(void) {}
	virtual void slot6(void) {}
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal = 0, Bool clip = true) const;
};

extern TerrainLogic *TheTerrainLogic;

#define g_bfmeK1266C 5.0f
#define BRIDGE_DIR_SCALE 7.0f
extern "C" __declspec(dllimport) double __cdecl floor(double);

// ?fast_float_floor@@YAMM@Z absent-from-retail
__forceinline float fast_float_floor(float f)
{
	return (float)floor((double)f);
}

// ?fast_float2long_round@@YAJM@Z absent-from-retail
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(value) (fast_float2long_round(fast_float_floor(value)))

class PathfindLayer
{
public:
	void classifyCells(void);

private:
	__forceinline void classifyLayerMapCell(Int i, Int j, PathfindCell *cell,
		Bridge *theBridge);

	PathfindCell *m_blockOfMapCells;
	PathfindCell **m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	ICoord2D m_startCell;
	ICoord2D m_endCell;
	PathfindLayerEnum m_layer;
	Int m_zone;
	unsigned char m_pad30[4];
	Bool m_destroyed;
	unsigned char m_pad35[3];
	Bridge *m_bridge;
};

void PathfindLayer::classifyCells(void)
{
	m_startCell.x = -1;
	m_startCell.y = -1;
	m_endCell.x = -1;
	m_endCell.y = -1;
	Int i, j;
	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			PathfindCell *cell = &m_layerCells[i][j];
			cell->setConnectLayer(LAYER_INVALID);
			cell->setLayer(m_layer);
			{
			Int cellX = i + m_xOrigin;
			Int cellY = j + m_yOrigin;
			Coord3D topLeftCorner, bottomRightCorner;

			topLeftCorner.y = (Real)cellY * g_bfmeDirectionWeight1285;
			bottomRightCorner.y = topLeftCorner.y + g_bfmeDirectionWeight1285;

			topLeftCorner.x = (Real)cellX * g_bfmeDirectionWeight1285;
			bottomRightCorner.x = topLeftCorner.x + g_bfmeDirectionWeight1285;

			Int bridgeCount = 0;
			Coord3D pt;
			if (m_bridge->isPointOnBridge(&topLeftCorner)) {
				bridgeCount++;
			}
			pt = topLeftCorner;
			pt.y = bottomRightCorner.y;
			if (m_bridge->isPointOnBridge(&pt)) {
				bridgeCount++;
			}
			if (m_bridge->isPointOnBridge(&bottomRightCorner)) {
				bridgeCount++;
			}
			pt = topLeftCorner;
			pt.x = bottomRightCorner.x;
			if (m_bridge->isPointOnBridge(&pt)) {
				bridgeCount++;
			}

			cell->reset();
			cell->setLayer(m_layer);
			setType(cell, PathfindCell::CELL_IMPASSABLE);
			if (bridgeCount == 4) {
				setType(cell, PathfindCell::CELL_CLEAR);
			} else {
				if (bridgeCount != 0) {
					setType(cell, PathfindCell::CELL_BRIDGE_IMPASSABLE);
				}

				Region2D cellBounds;
				cellBounds.lo.x = topLeftCorner.x;
				cellBounds.lo.y = topLeftCorner.y;
				cellBounds.hi.x = bottomRightCorner.x;
				cellBounds.hi.y = bottomRightCorner.y;

				if (m_bridge->isCellOnSide(&cellBounds)) {
					setType(cell, PathfindCell::CELL_BRIDGE_IMPASSABLE);
				} else {
					if (m_bridge->isCellOnEnd(&cellBounds)) {
						setType(cell, PathfindCell::CELL_CLEAR);
					}
					Real entryZ;
					if (m_bridge->isCellEntryPoint(&cellBounds, &entryZ)) {
						setType(cell, PathfindCell::CELL_CLEAR);
						cell->setConnectLayer(LAYER_GROUND);
						PathfindCell *groundCell = pathfinderGetCell(TheAI->pathfinder(),
							LAYER_GROUND, cellX, cellY);
						groundCell->setConnectLayer(cell->getLayer());
					}
				}
			}

			Coord3D center;
			Rva003FC790Set(&center, &topLeftCorner);
			center.x += g_bfmeK1266C;
			center.y += g_bfmeK1266C;
			// Retail reads the packed cell type only after both center stores.
			_ReadWriteBarrier();
			if (cell->getType() != PathfindCell::CELL_IMPASSABLE) {
				if (cell->getConnectLayer() != LAYER_GROUND) {
					Real groundHeight = TheTerrainLogic->getLayerHeight(
						center.x, center.y, LAYER_GROUND);
					Real bridgeHeight = m_bridge->getBridgeHeight(&center, 0);
					if (groundHeight + g_bfmeDirectionWeight1285 > bridgeHeight) {
						PathfindCell *groundCell = pathfinderGetCell(TheAI->pathfinder(),
							LAYER_GROUND, cellX, cellY);
						if (groundCell->getType() != PathfindCell::CELL_OBSTACLE) {
							setType(groundCell, PathfindCell::CELL_BRIDGE_IMPASSABLE);
						}
					}
				}
			}
			}
		}

		BridgeInfo info;
		m_bridge->getBridgeInfo(&info);
		Coord3D bridgeDir;
		Rva003FC790Set(&bridgeDir, &info.to);
		bridgeDir.x -= info.from.x;
		bridgeDir.y -= info.from.y;
		bridgeDir.z -= info.from.z;
		normalize(bridgeDir);
		bridgeDir.x *= BRIDGE_DIR_SCALE;
		bridgeDir.y *= BRIDGE_DIR_SCALE;

		m_startCell.x = REAL_TO_INT_FLOOR(
			(info.from.x - bridgeDir.x) * g_bfmeScaleBK);
		m_startCell.y = REAL_TO_INT_FLOOR(
			(info.from.y - bridgeDir.y) * g_bfmeScaleBK);
		m_endCell.x = REAL_TO_INT_FLOOR(
			(info.to.x + bridgeDir.x) * g_bfmeScaleBK);
		m_endCell.y = REAL_TO_INT_FLOOR(
			(info.to.y + bridgeDir.y) * g_bfmeScaleBK);
	}

	if (m_destroyed) {
		for (i = 0; i < m_width; i++) {
			for (j = 0; j < m_height; j++) {
				PathfindCell *cell = &m_layerCells[i][j];
				PathfindLayerEnum connectLayer = cell->getConnectLayer();
				if (connectLayer == LAYER_GROUND || (int)connectLayer >= 0x10) {
					PathfindCell *groundCell = pathfinderGetCell(TheAI->pathfinder(),
						LAYER_GROUND, i + m_xOrigin, j + m_yOrigin);
					if (groundCell) {
						groundCell->setConnectLayer(LAYER_INVALID);
					}
				}
				setType(cell, PathfindCell::CELL_BRIDGE_IMPASSABLE);
			}
		}
	}
}

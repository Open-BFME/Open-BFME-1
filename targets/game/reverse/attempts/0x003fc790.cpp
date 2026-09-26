// ?classifyCells@PathfindLayer@@QAEXXZ
// partial score=0.2 date=2026-09-22
// Candidate for the BFME packed-cell bridge classifier.
// The retail body uses the Zero Hour algorithm with BFME field and enum changes.

// cl: /DNDEBUG /MD /EHsc

#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

#define BfmeZeroRange (*(const Real *)0x01075350)
#define g_bfmeDefaultBU (*(const Real *)0x01075334)
#define g_bfmeDirectionWeight1285 (*(const Real *)0x01075c74)
#define g_bfmeScaleBK (*(const Real *)0x01075c70)

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

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}

	void normalize(void)
	{
		Real len = length();
		if (len != BfmeZeroRange) {
			Real scale = g_bfmeDefaultBU / len;
			x *= scale;
			y *= scale;
			z *= scale;
		}
	}
};

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
	Bool isCellEntryPoint(const Region2D *cell);
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);

	void getBridgeInfo(BridgeInfo *info)
	{
		*info = m_bridgeInfo;
	}

private:
	unsigned char m_prefix[0x0c];
	BridgeInfo m_bridgeInfo;
};

#pragma comment(linker, "/alternatename:?isCellEntryPoint@Bridge@@QAE_NPBURegion2D@@@Z=?j_0001cf49@@YAXXZ")

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
	void setType(CellType type);

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

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		(void)layer;
		if (x < m_lowX || x > m_highX || y < m_lowY || y > m_highY) {
			return 0;
		}
		return &m_map[x][y];
	}

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	Int m_lowX;
	Int m_lowY;
	Int m_highX;
	Int m_highY;
};

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

#define TheAI (*(AI **)0x012ef214)

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

#define TheTerrainLogic (*(TerrainLogic **)0x012ef4cc)

#define g_bfmeK1266C (*(const Real *)0x01075344)
#define BRIDGE_DIR_SCALE (*(const Real *)0x0109c34c)
#define REAL_TO_INT_FLOOR(value) ((Int)floor((double)(value)))

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

__forceinline void PathfindLayer::classifyLayerMapCell(Int i, Int j,
	PathfindCell *cell, Bridge *theBridge)
{
	Coord3D topLeftCorner, bottomRightCorner;

	topLeftCorner.y = (Real)j * g_bfmeDirectionWeight1285;
	bottomRightCorner.y = topLeftCorner.y + g_bfmeDirectionWeight1285;

	topLeftCorner.x = (Real)i * g_bfmeDirectionWeight1285;
	bottomRightCorner.x = topLeftCorner.x + g_bfmeDirectionWeight1285;

	Int bridgeCount = 0;
	Coord3D pt;
	if (theBridge->isPointOnBridge(&topLeftCorner)) {
		bridgeCount++;
	}
	pt = topLeftCorner;
	pt.y = bottomRightCorner.y;
	if (theBridge->isPointOnBridge(&pt)) {
		bridgeCount++;
	}
	if (theBridge->isPointOnBridge(&bottomRightCorner)) {
		bridgeCount++;
	}
	pt = topLeftCorner;
	pt.x = bottomRightCorner.x;
	if (theBridge->isPointOnBridge(&pt)) {
		bridgeCount++;
	}

	cell->reset();
	cell->setLayer(m_layer);
	cell->setType(PathfindCell::CELL_IMPASSABLE);
	if (bridgeCount == 4) {
		cell->setType(PathfindCell::CELL_CLEAR);
	} else {
		if (bridgeCount != 0) {
			cell->setType(PathfindCell::CELL_BRIDGE_IMPASSABLE);
		}

		Region2D cellBounds;
		cellBounds.lo.x = topLeftCorner.x;
		cellBounds.lo.y = topLeftCorner.y;
		cellBounds.hi.x = bottomRightCorner.x;
		cellBounds.hi.y = bottomRightCorner.y;

		if (m_bridge->isCellOnSide(&cellBounds)) {
			cell->setType(PathfindCell::CELL_BRIDGE_IMPASSABLE);
		} else {
			if (m_bridge->isCellOnEnd(&cellBounds)) {
				cell->setType(PathfindCell::CELL_CLEAR);
			}
			if (m_bridge->isCellEntryPoint(&cellBounds)) {
				cell->setType(PathfindCell::CELL_CLEAR);
				cell->setConnectLayer(LAYER_GROUND);
				PathfindCell *groundCell = TheAI->pathfinder()->getCell(
					LAYER_GROUND, i, j);
				groundCell->setConnectLayer(cell->getLayer());
			}
		}
	}

	Coord3D center = topLeftCorner;
	center.x += g_bfmeK1266C;
	center.y += g_bfmeK1266C;
	if (cell->getType() != PathfindCell::CELL_IMPASSABLE) {
		if (cell->getConnectLayer() != LAYER_GROUND) {
			Real groundHeight = TheTerrainLogic->getLayerHeight(
				center.x, center.y, LAYER_GROUND);
			Real bridgeHeight = theBridge->getBridgeHeight(&center, 0);
			if (groundHeight + g_bfmeDirectionWeight1285 > bridgeHeight) {
				PathfindCell *groundCell = TheAI->pathfinder()->getCell(
					LAYER_GROUND, i, j);
				if (groundCell->getType() != PathfindCell::CELL_OBSTACLE) {
					groundCell->setType(PathfindCell::CELL_BRIDGE_IMPASSABLE);
				}
			}
		}
	}
}

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
			classifyLayerMapCell(i + m_xOrigin, j + m_yOrigin, cell, m_bridge);
		}

		BridgeInfo info;
		m_bridge->getBridgeInfo(&info);
		Coord3D bridgeDir = info.to;
		bridgeDir.x -= info.from.x;
		bridgeDir.y -= info.from.y;
		bridgeDir.z -= info.from.z;
		bridgeDir.normalize();
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
					PathfindCell *groundCell = TheAI->pathfinder()->getCell(
						LAYER_GROUND, i + m_xOrigin, j + m_yOrigin);
					if (groundCell) {
						groundCell->setConnectLayer(LAYER_INVALID);
					}
				}
				cell->setType(PathfindCell::CELL_BRIDGE_IMPASSABLE);
			}
		}
	}
}

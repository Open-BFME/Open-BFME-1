// ?prependCells@Pathfinder@@QAEXPAVPath@@PBUCoord3D@@PAVPathfindCell@@_N@Z
// partial score=0.97 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003DD930: ?prependCells@Pathfinder@@QAEXPAVPath@@PBUCoord3D@@PAVPathfindCell@@_N@Z (BFME rewrite from the retail control flow).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

#define PATHFIND_CELL_SIZE_F 10.0f

class Object;

struct Coord3D
{
	Real x, y, z;
};

class PathNode
{
public:
	const Coord3D *getPosition(void) const { return &m_pos; }
	void setLayer(PathfindLayerEnum layer) { m_layer = layer; }
	void setCanOptimize(Bool canOpt) { m_canOptimize = canOpt; }

	PathNode *m_next;
	PathNode *m_prev;
	PathNode *m_nextOpti;
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

class Path
{
public:
	void prependNode(const Coord3D *pos, PathfindLayerEnum layer);
	PathNode *getFirstNode(void) { return m_path; }
	void setBlockedByAlly(Bool blocked) { m_blockedByAlly = blocked; }

	Int m_pad0;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_pad0c;
	Bool m_blockedByAlly;
};

// Linked waypoint record the BFME cell info points at (+0x0C) and the cell
// itself carries (+0x04); layout from the reads in this body only.
struct Rva003DD930Waypoint
{
	Int m_pad00;
	Int m_cost;
	Int m_pad08;
	Coord3D m_pos;
	char m_pad18[0x44 - 0x18];
	Rva003DD930Waypoint *m_next;
	Int m_pad48;
	Int m_last;
	char m_pad50[0xa8 - 0x50];
	UnsignedInt m_objectID;
};

class PathfindCell;

struct PathfindCellInfo
{
	Int m_x;
	Int m_y;
	PathfindCellInfo *m_pathParent;
	Rva003DD930Waypoint *m_waypoint;
	char m_pad10[0x24 - 0x10];
	UnsignedInt m_blockedByAlly : 1;
	PathfindCell *m_cell;
};

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR = 0, CELL_WATER = 1, CELL_CLIFF = 2 };

	PathfindCell *getParentCell(void) const
	{
		if (m_info && m_info->m_pathParent)
			return m_info->m_pathParent->m_cell;
		return 0;
	}
	void clearParentCell(void) { m_info->m_pathParent = 0; }
	UnsignedShort getXIndex(void) const { return (UnsignedShort)m_info->m_x; }
	UnsignedShort getYIndex(void) const { return (UnsignedShort)m_info->m_y; }
	CellType getType(void) const { return (CellType)m_type; }
	PathfindLayerEnum getLayer(void) const { return (PathfindLayerEnum)m_layer; }
	Bool isBlockedByAlly(void) const { return m_info->m_blockedByAlly != 0; }
	Rva003DD930Waypoint *getWaypoint(void) const { return m_info ? m_info->m_waypoint : 0; }

	PathfindCellInfo *m_info;
	Rva003DD930Waypoint *m_waypoint;
	Int m_pad08;
	UnsignedInt m_type : 3;
	UnsignedInt m_pad3 : 3;
	UnsignedInt m_layer : 6;
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true);

	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva003DD930ObjectNode
{
	Rva003DD930ObjectNode *m_next;
	UnsignedInt m_id;
	Object *m_object;
};

class GameLogic
{
public:
	Object *findObjectByID(UnsignedInt id)
	{
		UnsignedInt n = m_buckets.end - m_buckets.begin;
		Rva003DD930ObjectNode *node = m_buckets.begin[id % n];
		while (node && node->m_id != id)
			node = node->m_next;
		return node ? node->m_object : 0;
	}

	char m_pad[0xb4];
	struct { Rva003DD930ObjectNode **begin; Rva003DD930ObjectNode **end; } m_buckets;
};
extern GameLogic *TheGameLogic;

class BfmeGridAL
{
public:
	void bfmeSetAL(Int x, Int y, unsigned char passable);
};

class Pathfinder
{
public:
	void prependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell, Coord3D &pos, PathfindLayerEnum layer);

	char m_pad[0xc9c];
	BfmeGridAL m_zoneManager;
};

inline void inlineAdjustCoordToCell(Int cellX, Int cellY, Bool centerInCell, Coord3D &position, PathfindLayerEnum layer)
{
	if (centerInCell) {
		position.x = ((Real)cellX + 0.5f) * PATHFIND_CELL_SIZE_F;
		position.y = ((Real)cellY + 0.5f) * PATHFIND_CELL_SIZE_F;
	} else {
		position.x = ((Real)cellX + 0.05) * PATHFIND_CELL_SIZE_F;
		position.y = ((Real)cellY + 0.05) * PATHFIND_CELL_SIZE_F;
	}
	position.z = TheTerrainLogic->getLayerHeight(position.x, position.y, layer);
}

#define DEAD_WAYPOINT ((Rva003DD930Waypoint *)0xdeadc0de)

void Pathfinder::prependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center)
{
	Coord3D pos;
	PathfindCell *cell, *prevCell = 0;
	Bool goalCellNull = (goalCell->getParentCell() == 0);
	for (cell = goalCell; cell->getParentCell(); cell = cell->getParentCell())
	{
		m_zoneManager.bfmeSetAL(cell->getXIndex(), cell->getYIndex(), true);
		inlineAdjustCoordToCell(cell->getXIndex(), cell->getYIndex(), center, pos, cell->getLayer());
		if (prevCell && cell->getXIndex() == prevCell->getXIndex() && cell->getYIndex() == prevCell->getYIndex()) {
			PathfindLayerEnum layer = cell->getLayer();
			if (layer == LAYER_GROUND) {
				layer = prevCell->getLayer();
			}
			path->getFirstNode()->setLayer(layer);
			continue;
		}

		Bool canOptimize = true;
		if (cell->getType() == PathfindCell::CELL_CLIFF) {
			if (prevCell && prevCell->getType() != PathfindCell::CELL_CLIFF) {
				if (path->getFirstNode()) {
					path->getFirstNode()->setCanOptimize(false);
				}
			}
		} else {
			if (prevCell && prevCell->getType() == PathfindCell::CELL_CLIFF) {
				canOptimize = false;
			}
		}

		Rva003DD930Waypoint *waypoint = cell->getWaypoint();
		if (waypoint) {
			Int cost = waypoint->m_cost;
			pos = waypoint->m_pos;
			if (cost != 0x7fffffff) {
				if (cell->m_waypoint) {
					if (path->getFirstNode()) {
						path->getFirstNode()->m_costSoFar = cell->m_waypoint->m_cost;
						path->getFirstNode()->setCanOptimize(false);
					}
					path->prependNode(&cell->m_waypoint->m_pos, cell->getLayer());
				}
				for (Rva003DD930Waypoint *link = cell->getWaypoint()->m_next; link; link = link->m_next) {
					if (link == DEAD_WAYPOINT) {
						Rva003DD930Waypoint *owner = cell->getWaypoint();
						GameLogic *logic = TheGameLogic;
						do {
							if (link == DEAD_WAYPOINT)
								break;
							if (owner->m_objectID)
								logic->findObjectByID(owner->m_objectID);
							link = link->m_next;
						} while (link);
						break;
					}
					if (path->getFirstNode()) {
						path->getFirstNode()->m_costSoFar = link->m_cost;
						path->getFirstNode()->setCanOptimize(false);
					}
					path->prependNode(&link->m_pos, cell->getLayer());
					if (link->m_last)
						break;
				}
				if (path->getFirstNode()) {
					path->getFirstNode()->m_costSoFar = cost;
					path->getFirstNode()->setCanOptimize(false);
				}
			}
		}

		path->prependNode(&pos, TheTerrainLogic->getLayerForDestination(0, &pos));
		path->getFirstNode()->setCanOptimize(canOptimize);
		if (cell->isBlockedByAlly()) {
			path->setBlockedByAlly(true);
		}
		if (prevCell) {
			prevCell->clearParentCell();
		}
		prevCell = cell;
	}
	if (!cell->m_info)
		return;
	m_zoneManager.bfmeSetAL(cell->getXIndex(), cell->getYIndex(), true);
	if (goalCellNull) {
		adjustCoordToCell(cell->getXIndex(), cell->getYIndex(), center, pos, cell->getLayer());
		path->prependNode(&pos, cell->getLayer());
	}
	if (fromPos->x != path->getFirstNode()->getPosition()->x || fromPos->y != path->getFirstNode()->getPosition()->y) {
		path->prependNode(fromPos, cell->getLayer());
	}
}

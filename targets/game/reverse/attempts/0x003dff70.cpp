// ?d_003dff70@@YAXXZ
// partial score=0.4282 date=2026-10-04
// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing
//
// Retail 0x003DFF70 (816 bytes through ret 0x1c): a BFME variant of the Zero
// Hour Pathfinder::checkDestination (AIPathfind.cpp:4924) that also reports a
// crowding cost. Address-derived name: the only caller is the matched
// Pathfinder::rva003f1690 (through ILT 0x000073B5), which reads the seven
// stack words and the al result; no source names the method.
//
// The scan is ZH's: numCellsAbove from the radius/centre pair, the ignored
// obstacle and own id cached from the AI module, the nested i/j sweep with the
// inlined layer-aware getCell. BFME adds a footprint override up front (large
// templates collapse to one centred cell off the ground layer, or where the
// terrain slot at +0xBC accepts the cell centre) and accumulates *cost from
// the goal and position units instead of rejecting allies' cells. Layouts
// follow PathfindCheckDestination.cpp (0x003DD7A0).

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
struct Coord3D { Real x, y, z; };

enum PathfindLayerEnum { LAYER_GROUND = 1 };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_beforeKindof[0xc8 - 0x08];
	unsigned int m_kindof[4];	// +0xC8 KindOf bit words
};

class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
#define OBJECT_TU_MEMBERS \
 const ThingTemplate *getTemplate() const { const Overridable *t=m_template; if(t && t->m_nextOverride) t=t->m_nextOverride->getFinalOverride(); return (const ThingTemplate *)t; } \
 ObjectID getID() const { return (ObjectID)m_id; } \
 AIUpdateInterface *getAIUpdateInterface() const { return m_ai; } \
 Bool bfmeIsComputerControlled() const; \
 Relationship getRelationship(const Object *that) const;
#include "object.h"

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void _tl_00() = 0;
	virtual void _tl_01() = 0;
	virtual void _tl_02() = 0;
	virtual void _tl_03() = 0;
	virtual void _tl_04() = 0;
	virtual void _tl_05() = 0;
	virtual void _tl_06() = 0;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) = 0;
	virtual void _tl_08() = 0;
	virtual void _tl_09() = 0;
	virtual void _tl_10() = 0;
	virtual void _tl_11() = 0;
	virtual void _tl_12() = 0;
	virtual void _tl_13() = 0;
	virtual void _tl_14() = 0;
	virtual void _tl_15() = 0;
	virtual void _tl_16() = 0;
	virtual void _tl_17() = 0;
	virtual void _tl_18() = 0;
	virtual void _tl_19() = 0;
	virtual void _tl_20() = 0;
	virtual void _tl_21() = 0;
	virtual void _tl_22() = 0;
	virtual void _tl_23() = 0;
	virtual void _tl_24() = 0;
	virtual void _tl_25() = 0;
	virtual void _tl_26() = 0;
	virtual void _tl_27() = 0;
	virtual void _tl_28() = 0;
	virtual void _tl_29() = 0;
	virtual void _tl_30() = 0;
	virtual void _tl_31() = 0;
	virtual void _tl_32() = 0;
	virtual void _tl_33() = 0;
	virtual void _tl_34() = 0;
	virtual void _tl_35() = 0;
	virtual void _tl_36() = 0;
	virtual void _tl_37() = 0;
	virtual void _tl_38() = 0;
	virtual void _tl_39() = 0;
	virtual void _tl_40() = 0;
	virtual void _tl_41() = 0;
	virtual void _tl_42() = 0;
	virtual void _tl_43() = 0;
	virtual void _tl_44() = 0;
	virtual void _tl_45() = 0;
	virtual void _tl_46() = 0;
	virtual Bool slotBC(const Coord3D *pos) = 0;	// +0xBC
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];
	ObjectID m_goalUnitID;		// +0x14
	ObjectID m_posUnitID;		// +0x18
	ObjectID m_goalAircraftID;	// +0x1C
	ObjectID m_obstacleID;		// +0x20
};

class PathfindCell
{
public:
	Int getRawType() const { return m_packed & 0x7; }
	Int getFlags() const { return m_packed & 0x38; }
	unsigned char getGoalAircraftByte() const { return (unsigned char)(m_packed >> 21); }

	Bool isObstaclePresent(ObjectID objID) const
	{
		if (objID == INVALID_ID)
			return false;
		if (!m_info)
			return false;
		if (m_info->m_obstacleID == objID)
			return true;
		return false;
	}

	ObjectID getGoalUnit() const { return m_info ? m_info->m_goalUnitID : INVALID_ID; }
	ObjectID getPosUnit() const { return m_info ? m_info->m_posUnitID : INVALID_ID; }

	PathfindCellInfo *m_info;
	Int m_unused1;
	Int m_unused2;
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int cellX, Int cellY);

private:
	void *m_blockOfMapCells;			// +0x00
	PathfindCell **m_layerCells;		// +0x04
	Int m_width;						// +0x08
	Int m_height;						// +0x0c
	Int m_xOrigin;						// +0x10
	Int m_yOrigin;						// +0x14
	unsigned char m_tail[0x44 - 0x18];
};

// Matched body (pathfind_getcell.cpp, retail 0x003FBAB0), visible here as in
// retail's AIPathfind.cpp.
__declspec(noinline) PathfindCell *PathfindLayer::getCell(Int cellX, Int cellY)
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
	if (cell->getRawType() == 5)
		return 0;
	return cell;
}

class Pathfinder
{
public:
	Bool checkFootprint003DFF70(const Object *obj, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int iRadius, Bool centerInCell, Int *cost);

	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY)
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell(cellX, cellY);
				if (cell)
					return cell;
			}
			return &m_map[cellX][cellY];
		}
		return 0;
	}

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

Bool Pathfinder::checkFootprint003DFF70(const Object *obj, Int cellX, Int cellY,
	PathfindLayerEnum layer, Int iRadius, Bool centerInCell, Int *cost)
{
	Int radiusCopy = iRadius;

	if (obj->getTemplate()->m_kindof[3] & 0x1000)
	{
		if (layer != LAYER_GROUND)
		{
			radiusCopy = 1;
			centerInCell = true;
		}
		else
		{
			Coord3D pos;
			pos.y = (cellY + 0.5f) * 10.0f;
			pos.x = (cellX + 0.5f) * 10.0f;
			pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND);
			if (TheTerrainLogic->slotBC(&pos))
			{
				radiusCopy = 1;
				centerInCell = true;
			}
		}
	}
	if ((obj->getTemplate()->m_kindof[2] & 0x2000000) &&
		(obj->getTemplate()->m_kindof[0] & 0x100) && layer != LAYER_GROUND)
	{
		radiusCopy = 1;
		centerInCell = false;
	}

	Int numCellsAbove = radiusCopy;
	if (centerInCell) numCellsAbove++;
	*cost = 0;
	Int i, j;
	ObjectID ignoreId = INVALID_ID;
	ObjectID objID = INVALID_ID;
	if (obj->getAIUpdateInterface())
	{
		ignoreId = obj->getAIUpdateInterface()->getIgnoredObstacleID();
		objID = obj->getID();
	}
	for (i = cellX - radiusCopy; i < cellX + numCellsAbove; i++)
	{
		for (j = cellY - radiusCopy; j < cellY + numCellsAbove; j++)
		{
			PathfindCell *cell = getCell(layer, i, j);
			if (cell == 0)
				return false;
			if (cell->getRawType() == 5)
				return false;
			if ((cell->getGoalAircraftByte() & 1) && obj->bfmeIsComputerControlled())
				return false;
			if (cell->getRawType() == 2)
				return false;
			if (cell->getRawType() == 4)
			{
				if (cell->isObstaclePresent(ignoreId))
					continue;
				return false;
			}
			if (cell->getRawType() == 5 || cell->getRawType() == 6)
				return false;
			if ((cell->getGoalAircraftByte() & 1) && obj->bfmeIsComputerControlled())
				return false;
			if (cell->getFlags() == 0)
				continue;

			ObjectID goalUnitID = cell->getGoalUnit();
			if (goalUnitID == objID)
				continue;
			if (ignoreId != INVALID_ID && ignoreId == goalUnitID)
				continue;
			if (goalUnitID != INVALID_ID)
			{
				Object *unit = TheGameLogic->findObjectByID(goalUnitID);
				if (unit)
				{
					if (unit->m_containedBy == obj)
						continue;
					if (obj->getRelationship(unit) == ALLIES)
						(*cost)++;
					else if (cell->getFlags() == 0x18)
						return false;
				}
			}

			ObjectID posUnitID = cell->getPosUnit();
			if (posUnitID == objID)
				continue;
			if (posUnitID == INVALID_ID)
				continue;
			Object *unit = TheGameLogic->findObjectByID(posUnitID);
			if (!unit)
				continue;
			if (unit->m_containedBy == obj)
				continue;
			*cost += obj->getRelationship(unit) == ALLIES ? 3 : 1;
		}
	}
	return true;
}

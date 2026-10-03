// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/GameLogic/Object
// stlport
// BFME Pathfinder::clearCellForDiameter, RVA 0x003DC810, 729 bytes.
// ZH twin: GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp:6724.
// BFME adds an unsigned crusher level and a sixth stopOnFail byte argument.
// The native GameLogic lookup must be visible but not inlined: its read-only
// effects recover retail's failure-block placement and short branches.
// Object uses the canonical BFME header. The reduced pathfind shim does not
// declare this BFME six-argument method or the cell-info/flag operations here;
// these TU-local views retain its witnessed map, extent and layer offsets.
// Evidence: targets/game/reverse/identity_evidence/003dc810-clear-cell.md.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef int ObjectID;

const ObjectID INVALID_ID = 0;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

#define OBJECT_TU_MEMBERS UnsignedByte getCrushableLevel() const;
#include "object.h"

#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

class Rva003DC810CellInfo
{
public:
	unsigned char m_prefix[0x18];
	ObjectID m_objectID18;
	unsigned char m_unknown1C[8];
	UnsignedInt m_bits003DC810;
};

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR = 0, CELL_OBSTACLE = 4 };
	enum CellFlags { NO_UNITS = 0, UNIT_PRESENT_FIXED = 3 };

	Int getType( void ) const { return m_type; }
	Int getFlags( void ) const { return m_flags; }
	ObjectID getObjectID003DC810( void ) const { ObjectID id = m_info ? m_info->m_objectID18 : INVALID_ID; return id; }
	Bool isObstacleFence( void ) const { return m_info && (((unsigned char)(m_info->m_bits003DC810 >> 1)) & 1); }

	Rva003DC810CellInfo *m_info;
	Int m_unused1;
	Int m_unused2;
	UnsignedInt m_type:3;
	UnsignedInt m_flags:3;
	UnsignedInt m_rest:26;
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	unsigned char m_body[0x44];
};

class Pathfinder
{
public:
	Int clearCellForDiameter( UnsignedInt crusher, Int cellX, Int cellY, PathfindLayerEnum layer,
		Int pathDiameter, Bool stopOnFail );
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
{
	if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
		cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
	{
		if (layer > LAYER_GROUND && layer <= LAYER_LAST)
		{
			PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
			if (cell)
				return cell;
		}
		return &m_map[cellX][cellY];
	}
	return 0;
}

Int Pathfinder::clearCellForDiameter( UnsignedInt crusher, Int cellX, Int cellY,
	PathfindLayerEnum layer, Int pathDiameter, Bool stopOnFail )
{
	Int radius = pathDiameter/2;
	Int numCellsAbove = radius;
	if (radius==0) numCellsAbove++;
	Int i, j;
	if (radius > 1)
	{
		for (i = cellX - radius; i < cellX + radius; i++)
		{
			Int jMax;
			Bool xMinOrMax = (i == cellX - radius) || (i == cellX + radius - 1);
			if (xMinOrMax)
			{
				jMax = cellY + radius - 1;
				j = cellY - radius + 1;
			}
			else
			{
				jMax = cellY + radius;
				j = cellY - radius;
			}
			for (; j < jMax; j++)
			{
				Bool clear = true;
				PathfindCell *cell = getCell(layer, i, j);
				if (cell)
				{
					if (cell->getFlags() == PathfindCell::UNIT_PRESENT_FIXED)
					{
						Object *obj = TheGameLogic->findObjectByID(cell->getObjectID003DC810());
						if (obj && (UnsignedInt)(signed char)obj->getCrushableLevel() > crusher)
							clear = false;
					}
				}
				else
				{
					clear = false;
				}
				if (!clear)
				{
					if (stopOnFail)
						return 0;
					return clearCellForDiameter(crusher, cellX, cellY, layer, pathDiameter - 2, false);
				}
				if (cell->getType() != PathfindCell::CELL_CLEAR)
				{
					if (cell->getType() != PathfindCell::CELL_OBSTACLE || !crusher ||
						!cell->isObstacleFence())
					{
						if (stopOnFail)
							return 0;
						return clearCellForDiameter(crusher, cellX, cellY, layer, pathDiameter - 2, false);
					}
				}
			}
		}
	}
	else
	{
		for (i = cellX - radius; i < cellX + numCellsAbove; i++)
		{
			for (j = cellY - radius; j < cellY + numCellsAbove; j++)
			{
				PathfindCell *cell = getCell(layer, i, j);
				if (!cell)
					return 0;
				if (cell->getFlags() == PathfindCell::UNIT_PRESENT_FIXED)
				{
					Object *obj = TheGameLogic->findObjectByID(cell->getObjectID003DC810());
					if (obj && (UnsignedInt)(signed char)obj->getCrushableLevel() > crusher)
						return 0;
				}
				if (cell->getType() != PathfindCell::CELL_CLEAR)
				{
					if (cell->getType() != PathfindCell::CELL_OBSTACLE || !crusher ||
						!cell->isObstacleFence())
						return 0;
				}
			}
		}
	}
	if (radius == 0)
		return 1;
	return 2*radius;
}

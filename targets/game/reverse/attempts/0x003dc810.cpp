// ?clearCellForDiameter@Pathfinder@@QAEHIHHW4PathfindLayerEnum@@H_N@Z
// partial score=0.96 date=2026-09-28
// ?clearCellForDiameter@Pathfinder@@QAEHIHHW4PathfindLayerEnum@@H_N@Z
// partial score=0.96(shape) date=2026-09-28
// cl: /DNDEBUG /MD
//
// Retail 0x003DC810, 729 bytes (ret 0x18). Identity: ILT 0x00048D29 pinned as
// ?clearCellForDiameter@Pathfinder@@QAEHHHHHHH@Z with 14 ILT callers.
// BFME's six-argument form of ZH AIPathfind.cpp clearCellForDiameter: an unsigned
// crusher level compared against the signed crushable level, and a trailing Bool
// that returns 0 on failure instead of retrying at pathDiameter-2 (tail recursion,
// compiled as a jump back to the entry).  radius>1 runs a corner-cutting loop
// (ZH xMinOrMax Bool; j assigned directly in each branch), radius<=1 a plain loop
// that returns 0 on any failure.  Cell type/flags are the 3-bit fields of the
// dword at +0x0C (bitfield access gives retail's dword load + `cmp dl,0x18`).
// probe: 745 vs 729 bytes, shape 0.960, 521 differing bytes.  Everything up to
// +0x117 is instruction-identical; the whole residue is ONE block placement: retail
// lays the not-clear block (stopOnFail test + tail recursion) inline right after
// the crushable-level compare (`jbe` over it), VC7.1 here moves it after the loop,
// which turns every short jump into a near jump.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

class Object
{
public:
	UnsignedByte getCrushableLevel( void ) const;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
	ObjectID m_bfme1C;
	ObjectID m_bfme20;
	UnsignedInt m_bfme24;
};

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR = 0, CELL_OBSTACLE = 4 };
	enum CellFlags { NO_UNITS = 0, UNIT_PRESENT_FIXED = 3 };

	Int getType( void ) const { return m_type; }
	Int getFlags( void ) const { return m_flags; }
	ObjectID getPosUnit( void ) const { ObjectID id = m_info ? m_info->m_posUnitID : INVALID_ID; return id; }
	Bool isObstacleFence( void ) const { return m_info && (((unsigned char)(m_info->m_bfme24 >> 1)) & 1); }

	PathfindCellInfo *m_info;
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
						Object *obj = TheGameLogic->findObjectByID(cell->getPosUnit());
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
					Object *obj = TheGameLogic->findObjectByID(cell->getPosUnit());
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

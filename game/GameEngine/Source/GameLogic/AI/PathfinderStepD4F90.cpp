// cl: /DNDEBUG /MD
//
// Retail 0x003D4F90: the per-cell movement predicate used by the BFME
// Pathfinder walk.  The ILT at 0x0002B9E0 names this body from the
// Pathfinder examine callback.
//
// Every retail call this body makes leaves through an ILT thunk, so each
// callee is referenced directly by its thunk address (`j_XXXXXXXX`) and
// reached through a TU-local function-pointer union; no linker symbol
// aliasing directive is used.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

// Retail ILT thunks every call below leaves through; named by address only.
extern void j_000022bb();
extern void j_00005e48();
extern void j_00010ea1();
extern void j_0001264d();
extern void j_000169c3();
extern void j_000171e8();
extern void j_0001c675();
extern void j_00020671();
extern void j_00021da0();
extern void j_00024ef1();
extern void j_00032b5f();
extern void j_0003398d();
extern void j_0003a828();
extern void j_0003d1a9();
extern void j_0003d3ed();
extern void j_0003e9f5();
extern void j_00040313();
extern void j_000461ff();
extern void j_0004b3b7();

struct BfmeMovementPositionInfo
{
	Int m_surfaces;
	unsigned char m_field04;
	unsigned char m_allowAircraftGoal;
	unsigned char m_pad06[2];
	Int m_maxLayer;
};
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell;

struct PathfindCellInfo
{
	ICoord2D m_pos;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	UnsignedShort m_totalCost;
	UnsignedShort m_costSoFar;
	UnsignedInt m_pathParent;
	UnsignedInt m_goalUnitID;
	UnsignedInt m_posUnitID;
	union { UnsignedInt m_goalAircraftID; Int m_obstacleID; };
	UnsignedInt m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_freeNext;
	PathfindCellInfo **m_freePrevLink;
};
extern void *g_rva012F1094;

class PathfindCell
{
public:
	__forceinline void allocateInfo(const ICoord2D *pos)
	{
		if (m_info == 0)
		{
			if (g_rva012F1094 == 0)
				j_0003d1a9();
			typedef PathfindCellInfo *(__cdecl *AcquireFn)(PathfindCellInfo **freeList,
				PathfindCell *cell, const ICoord2D *pos);
			m_info = ((AcquireFn)(void *)j_00021da0)(reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), this, pos);
		}
		else
		{
			m_info->m_prevOpen = 0;
		}
	}
	Bool hasInfo() const { return m_info != 0; }
	Bool getOpen() const { return m_info ? ((m_info->m_flags >> 3) & 1) : false; }
	Bool getClosed() const { return m_info ? ((m_info->m_flags >> 4) & 1) : false; }
	UnsignedShort getXIndex() const { return (UnsignedShort)m_info->m_pos.x; }
	UnsignedShort getYIndex() const { return (UnsignedShort)m_info->m_pos.y; }
	PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)((m_bits >> 6) & 0x3f); }

	PathfindCellInfo *m_info;
	Int m_zone;
	Int m_unused08;
	union { UnsignedInt m_bits; unsigned int m_word; };
};

extern Int g_Va012B49FC[];
class Overridable
{
public:
	void *m_vptr;
	const Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0x444 - 8];
	Int m_bfme444;
	unsigned char m_pad448[0x4cc - 0x448];
	Bool m_bfme4CC;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *d = m_template;
		if (d == 0)
			return d;
		typedef const Overridable *(Overridable::*FinalOverride)(void);
		union { void (*fn)(); FinalOverride call; } u = { j_000022bb };
		Overridable *next = const_cast<Overridable *>(d->m_nextOverride);
		return (const ThingTemplate *)(next ? (next->*u.call)() : d);
	}

	void *m_vptr;
	const ThingTemplate *m_template;
};

class TerrainLogic
{
public:
	// Retail body is reached only through its ILT thunk; no member is needed.
};
extern TerrainLogic *TheTerrainLogic;

class LocomotorSet
{
public:
	Int getValidSurfaces() const { return m_validLocomotorSurfaces; }

	unsigned char m_pad[0x10];
	Int m_validLocomotorSurfaces;
};

class BfmeStepInfo
{
public:
	Int m_surfaces;
	Bool m_field04;
	Bool m_allowAircraftGoal;
	char m_pad06[2];
	Int m_maxLayer;
};

class Pathfinder
{
public:
	Bool bfmeStepD4F90(void *movementInfo, PathfindCell *pathfindCell);

protected:
	Int checkPathCost(Object *obj, const LocomotorSet &locomotorSet,
		const Coord3D *from, const Coord3D *rawTo);

private:
	// Retail reads byte +8 here, but BFME layout witnesses disagree on its member identity.
	unsigned char m_opaque00[0x838];
	PathfindCellInfo *m_closedList;		// +0x838
	Bool m_isTunneling;					// +0x83C
	unsigned char m_pad83d[0x844 - 0x83d];
	Int m_ignoreObstacleID;				// +0x844
};

bool Pathfinder::bfmeStepD4F90( void *movementInfo, PathfindCell *pathfindCell )
{
	const PathfindCell *toCell = pathfindCell;
	register BfmeMovementPositionInfo *info = (BfmeMovementPositionInfo *)movementInfo;
	if (toCell == 0)
		return false;

	unsigned int word = toCell->m_word;
	if (((unsigned char)(word >> 21) & 1) != 0 &&
		info->m_allowAircraftGoal != 0)
		return false;

	Int type = word & 7;
	switch (type)
	{
	case 3:
		goto typeThree;

	case 4:
		break;

	default:
		goto common;
	}

	{
		Int obstacleID = toCell->m_info != 0 ?
			toCell->m_info->m_obstacleID : 0;
		if (obstacleID != m_ignoreObstacleID)
			goto common;
		goto passable;
	}

common:
	if ((g_Va012B49FC[type] & info->m_surfaces) == 0)
		return false;

	if (info->m_field04 != 0 && ((unsigned char)(word >> 20) & 1) != 0)
		return false;

	if (info->m_maxLayer < 0)
		goto passable;

	if ((Int)((word >> 22) & 3) > info->m_maxLayer)
		return false;

passable:
	return true;

typeThree:
	if ((word & 0xfc0) != 0x40)
		return false;

	goto common;
}
Int Pathfinder::checkPathCost(Object *obj, const LocomotorSet &locomotorSet,
	const Coord3D *from, const Coord3D *rawTo)
{
	if (((const unsigned char *)this)[8] == 0)
		return 0;
	enum { MAX_COST = 0x7fff0000 };

	Int cellCount = 0;

	Coord3D adjustTo = *rawTo;
	Coord3D *to = &adjustTo;

	PathfindLayerEnum goalLayer;
	{
		typedef PathfindLayerEnum (TerrainLogic::*LayerForDestination)(Object *, const Coord3D *);
		union { void (*fn)(); LayerForDestination call; } u = { j_0001c675 };
		goalLayer = (TheTerrainLogic->*u.call)(obj, to);
	}
	Int goalX, goalY;
	{
		ICoord2D cell;
		typedef Bool (Pathfinder::*WorldToCell)(const Coord3D *, ICoord2D *);
		union { void (*fn)(); WorldToCell call; } u = { j_000171e8 };
		(this->*u.call)(to, &cell);
		goalX = cell.x;
		goalY = cell.y;
	}
	PathfindCell *goalCell;
	{
		typedef PathfindCell *(Pathfinder::*GetCellXY)(PathfindLayerEnum, Int, Int);
		union { void (*fn)(); GetCellXY call; } u = { j_00020671 };
		goalCell = (this->*u.call)(goalLayer, goalX, goalY);
	}
	if (goalCell == 0)
		return MAX_COST;

	{
		Bool center;
		Int radius;
		typedef void (Pathfinder::*RadiusAndCenter)(const Object *, Int &, Bool &);
		union { void (*fn)(); RadiusAndCenter call; } u = { j_000461ff };
		(this->*u.call)(obj, radius, center);
	}

	PathfindCell *parentCell;
	{
		ICoord2D startCellNdx;
		{
			typedef Bool (Pathfinder::*WorldToCell)(const Coord3D *, ICoord2D *);
			union { void (*fn)(); WorldToCell call; } u = { j_000171e8 };
			(this->*u.call)(from, &startCellNdx);
		}
		PathfindLayerEnum fromLayer;
		{
			typedef PathfindLayerEnum (TerrainLogic::*LayerForDestination)(Object *, const Coord3D *);
			union { void (*fn)(); LayerForDestination call; } u = { j_0001c675 };
			fromLayer = (TheTerrainLogic->*u.call)(obj, from);
		}
		{
			typedef PathfindCell *(Pathfinder::*GetCellPos)(PathfindLayerEnum, const Coord3D *);
			union { void (*fn)(); GetCellPos call; } u = { j_0003398d };
			parentCell = (this->*u.call)(fromLayer, from);
		}
		if (parentCell == 0)
			return MAX_COST;
		ICoord2D pos2d;
		{
			typedef Bool (Pathfinder::*WorldToCell)(const Coord3D *, ICoord2D *);
			union { void (*fn)(); WorldToCell call; } u = { j_000171e8 };
			(this->*u.call)(to, &pos2d);
		}
		goalCell->allocateInfo(&pos2d);
		if (parentCell != goalCell)
			parentCell->allocateInfo(&startCellNdx);
	}

	Int templateLayer = obj->getTemplate()->m_bfme444;
	Bool templateFlag = obj->getTemplate()->m_bfme4CC;
	BfmeStepInfo stepInfo;
	Bool isCrusher;
	{
		typedef Bool (Object::*IsComputerControlled)(void) const;
		union { void (*fn)(); IsComputerControlled call; } u = { j_00010ea1 };
		isCrusher = (obj->*u.call)();
	}
	stepInfo.m_surfaces = locomotorSet.getValidSurfaces();
	stepInfo.m_allowAircraftGoal = isCrusher;
	stepInfo.m_field04 = !templateFlag;
	stepInfo.m_maxLayer = templateLayer - 1;

	if (!bfmeStepD4F90(&stepInfo, parentCell))
	{
		typedef void (PathfindCell::*ReleaseInfo)(void);
		union { void (*fn)(); ReleaseInfo call; } u = { j_0004b3b7 };
		(parentCell->*u.call)();
		(goalCell->*u.call)();
		return MAX_COST;
	}

	{
		typedef Bool (PathfindCell::*StartPathfind)(PathfindCell *);
		union { void (*fn)(); StartPathfind call; } u = { j_0003e9f5 };
		(parentCell->*u.call)(goalCell);
	}
	{
		typedef UnsignedInt (Pathfinder::*CostToGoal)(PathfindCell *, PathfindCell *);
		union { void (*fn)(); CostToGoal call; } u = { j_0003a828 };
		parentCell->m_info->m_totalCost = (UnsignedShort)(this->*u.call)(parentCell, goalCell);
	}
	{
		typedef void (Pathfinder::*OpenCost)(PathfindCell *);
		union { void (*fn)(); OpenCost call; } u = { j_00024ef1 };
		(this->*u.call)(parentCell);
	}

	{
		typedef PathfindCell *(Pathfinder::*NextOpenCell)(void);
		union { void (*fn)(); NextOpenCell call; } u = { j_0003d3ed };
		while ((parentCell = (this->*u.call)()) != 0)
		{
			{
				typedef void (PathfindCell::*CloseInfo)(PathfindCellInfo **);
				union { void (*fn)(); CloseInfo call; } u = { j_00005e48 };
				(parentCell->*u.call)(&m_closedList);
			}

			if (parentCell == goalCell)
			{
				Int cost = parentCell->m_info->m_totalCost;
				m_isTunneling = false;
				{
					typedef void (Pathfinder::*ClearTunneling)(void);
					union { void (*fn)(); ClearTunneling call; } u = { j_00032b5f };
					(this->*u.call)();
				}
				return cost;
			}

			if (cellCount > 500)
				continue;

			{
				typedef void (Pathfinder::*ExpandCell)(PathfindCell *, Object *);
				union { void (*fn)(); ExpandCell call; } u = { j_0001264d };
				(this->*u.call)(parentCell, obj);
			}

			static Int deltaX[] = { 1, 0, -1, 0, 1, -1, -1, 1 };
			static Int deltaY[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
			const Int numNeighbors = 8;
			const Int firstDiagonal = 4;
			ICoord2D newCellCoord;
			PathfindCell *newCell;
			const Int adjacent[5] = { 0, 1, 2, 3, 0 };
			Bool neighborFlags[8] = { false, false, false, false, false, false, false };

			for (Int i = 0; i < numNeighbors; i++)
			{
				neighborFlags[i] = false;
				Int nx = parentCell->getXIndex() + deltaX[i];
				Int ny = parentCell->getYIndex() + deltaY[i];
				newCellCoord.x = nx;
				newCellCoord.y = ny;

				{
					typedef PathfindCell *(Pathfinder::*GetCellXY)(PathfindLayerEnum, Int, Int);
					union { void (*fn)(); GetCellXY call; } u = { j_00020671 };
					newCell = (this->*u.call)(parentCell->getLayer(), nx, ny);
				}
				if (newCell == 0)
					continue;

				if (newCell->getOpen() || newCell->getClosed())
					continue;
				if (i >= firstDiagonal)
				{
					if (!neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
						continue;
				}

				if (!bfmeStepD4F90(&stepInfo, newCell))
					continue;

				neighborFlags[i] = true;

				newCell->allocateInfo(&newCellCoord);
				cellCount++;

				UnsignedInt newCostSoFar;
				{
					typedef UnsignedInt (PathfindCell::*CostSoFar)(PathfindCell *);
					union { void (*fn)(); CostSoFar call; } u = { j_000169c3 };
					newCostSoFar = (newCell->*u.call)(parentCell);
				}
				newCell->m_info->m_flags &= ~1u;
				{
					typedef void (PathfindCell::*SetParentCell)(PathfindCell *);
					union { void (*fn)(); SetParentCell call; } u = { j_00040313 };
					(newCell->*u.call)(parentCell);
				}
				PathfindCell *costGoal = *(PathfindCell *volatile *)&goalCell;
				newCell->m_info->m_costSoFar = (UnsignedShort)newCostSoFar;
				UnsignedInt costRemaining;
				{
					typedef UnsignedInt (Pathfinder::*CostToGoal)(PathfindCell *, PathfindCell *);
					union { void (*fn)(); CostToGoal call; } u = { j_0003a828 };
					costRemaining = (this->*u.call)(newCell, costGoal);
				}
				newCell->m_info->m_totalCost = newCell->m_info->m_costSoFar + costRemaining;
				{
					typedef void (Pathfinder::*OpenCost)(PathfindCell *);
					union { void (*fn)(); OpenCost call; } u = { j_00024ef1 };
					(this->*u.call)(newCell);
				}
			}
		}
	}

	m_isTunneling = false;
	if (goalCell->hasInfo() && !goalCell->getClosed() && !goalCell->getOpen())
	{
		typedef void (PathfindCell::*ReleaseInfo)(void);
		union { void (*fn)(); ReleaseInfo call; } u = { j_0004b3b7 };
		(goalCell->*u.call)();
	}
	{
		typedef void (Pathfinder::*ClearTunneling)(void);
		union { void (*fn)(); ClearTunneling call; } u = { j_00032b5f };
		(this->*u.call)();
	}
	return MAX_COST;
}

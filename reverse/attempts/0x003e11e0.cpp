// ?checkPathCost@Pathfinder@@IAEHPAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z
// partial score=0.995 date=2026-09-23
// cl: /DNDEBUG /MD /ICode/GameEngine/Source/GameLogic/AI
// The landed movement predicate is included unchanged so VC7.1 sees that it
// only reads the cell; calls still route to its retail ILT 0x0002B9E0.
#pragma auto_inline(off)
namespace StepContract003D4F90 {
#include "PathfinderStepD4F90.cpp"
}
#pragma auto_inline(on)
// Pathfinder::checkPathCost -- retail RVA 0x003E11E0, 1064 bytes (sub esp,0x44;
// ret 0x10 at +0x425, int3 pad to 0x003E1608).
// Identity: the matched Pathfinder::adjustDestination (0x003F6090) calls this
// body through ILT 0x00038F19 right after tightenPath with
// (obj, locomotorSet, groupDest, dest) and compares the Int result against
// 1.4 * distance, exactly Zero Hour's
//   tightenPath(obj, locomotorSet, dest, groupDest);
//   Int cost = checkPathCost(obj, locomotorSet, groupDest, dest);
// The body is ZH AIPathfind.cpp's checkPathCost A* loop with BFME deltas:
// no obj null guard, getLayerForDestination(obj, pos), allocateInfo cannot
// fail, a BfmeStepInfo movement record replaces validMovementPosition, open or
// closed neighbours are skipped outright, and the open/closed lists are the
// indexed BFME lists (0x003D6400 insert, 0x003D6490 pop, 0x003F6C30 close).
// The neighbour deltas are split into x (VA 0x012B4A20) and y (0x012B4A48)
// tables. Unproven helper identities keep address-derived names.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

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

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

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
	Bool bfmeIsComputerControlled() const;
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *d = m_template;
		if (d == 0)
			return d;
		return (const ThingTemplate *)(d->m_nextOverride ? d->m_nextOverride->getFinalOverride() : d);
	}

	void *m_vptr;
	const ThingTemplate *m_template;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

class PathfindCell;

class PathfindCellInfo
{
public:
	static void allocateCellInfos();

	ICoord2D m_pos;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	UnsignedShort m_totalCost;
	UnsignedShort m_costSoFar;
	UnsignedInt m_pathParent;
	UnsignedInt m_goalUnitID;
	UnsignedInt m_posUnitID;
	UnsignedInt m_goalAircraftID;
	UnsignedInt m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_freeNext;
	PathfindCellInfo **m_freePrevLink;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

class PathfindCell
{
public:
	Bool startPathfind(PathfindCell *goalCell);
	UnsignedInt costSoFar(PathfindCell *parent);
	void setParentCell(PathfindCell *parent);
	void rva003F6F10();
	void rva003F6C30(PathfindCellInfo **head);

	__forceinline void allocateInfo(const ICoord2D *pos)
	{
		if (m_info == 0)
		{
			if (g_bfmePathfindFreeList == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, pos);
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
	UnsignedInt m_bits;
};

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

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	PathfindCell *getCell(PathfindLayerEnum layer, const Coord3D *pos);
	Bool bfmeStepD4F90(void *info, PathfindCell *cell)
	{
		return ((StepContract003D4F90::Pathfinder *)this)->bfmeStepD4F90(
			info, (StepContract003D4F90::PathfindCell *)cell);
	}
	UnsignedInt rva003DB900(PathfindCell *cell, PathfindCell *goalCell);
	void rva003D6400(PathfindCell *cell);
	PathfindCell *rva003D6490();
	void rva003DAE40(PathfindCell *cell, Object *obj);
	void rva003D5FC0();

protected:
	void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);
	Int checkPathCost(Object *obj, const LocomotorSet &locomotorSet,
		const Coord3D *from, const Coord3D *rawTo);

private:
	unsigned char m_pad00[8];
	Bool m_isMapReady;					// +0x008
	unsigned char m_pad09[0x838 - 9];
	PathfindCellInfo *m_closedList;		// +0x838
	Bool m_isTunneling;					// +0x83C
};

Int Pathfinder::checkPathCost(Object *obj, const LocomotorSet &locomotorSet,
	const Coord3D *from, const Coord3D *rawTo)
{
	if (m_isMapReady == false)
		return 0;
	enum { MAX_COST = 0x7fff0000 };

	Int cellCount = 0;

	Coord3D adjustTo = *rawTo;
	Coord3D *to = &adjustTo;

	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
	Int goalX, goalY;
	{
		ICoord2D cell;
		worldToCell(to, &cell);
		goalX = cell.x;
		goalY = cell.y;
	}
	PathfindCell *goalCell = getCell(goalLayer, goalX, goalY);
	if (goalCell == 0)
		return MAX_COST;

	{
		Bool center;
		Int radius;
		getRadiusAndCenter(obj, radius, center);
	}

	PathfindCell *parentCell;
	{
		ICoord2D startCellNdx;
		worldToCell(from, &startCellNdx);
		PathfindLayerEnum fromLayer = TheTerrainLogic->getLayerForDestination(obj, from);
		parentCell = getCell(fromLayer, from);
		if (parentCell == 0)
			return MAX_COST;
		ICoord2D pos2d;
		worldToCell(to, &pos2d);
		goalCell->allocateInfo(&pos2d);
		if (parentCell != goalCell)
			parentCell->allocateInfo(&startCellNdx);
	}

	Int templateLayer = obj->getTemplate()->m_bfme444;
	Bool templateFlag = obj->getTemplate()->m_bfme4CC;
	BfmeStepInfo stepInfo;
	Bool isCrusher = obj->bfmeIsComputerControlled();
	stepInfo.m_surfaces = locomotorSet.getValidSurfaces();
	stepInfo.m_allowAircraftGoal = isCrusher;
	stepInfo.m_field04 = !templateFlag;
	stepInfo.m_maxLayer = templateLayer - 1;

	if (!bfmeStepD4F90(&stepInfo, parentCell))
	{
		parentCell->rva003F6F10();
		goalCell->rva003F6F10();
		return MAX_COST;
	}

	parentCell->startPathfind(goalCell);
	parentCell->m_info->m_totalCost = (UnsignedShort)rva003DB900(parentCell, goalCell);
	rva003D6400(parentCell);

	while ((parentCell = rva003D6490()) != 0)
	{
		parentCell->rva003F6C30(&m_closedList);

		if (parentCell == goalCell)
		{
			Int cost = parentCell->m_info->m_totalCost;
			m_isTunneling = false;
			rva003D5FC0();
			return cost;
		}

		if (cellCount > 500)
			continue;

		rva003DAE40(parentCell, obj);

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

			newCell = getCell(parentCell->getLayer(), nx, ny);
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

			UnsignedInt newCostSoFar = newCell->costSoFar(parentCell);
			newCell->m_info->m_flags &= ~1u;
			newCell->setParentCell(parentCell);
			newCell->m_info->m_costSoFar = (UnsignedShort)newCostSoFar;
			UnsignedInt costRemaining = rva003DB900(newCell, goalCell);
			newCell->m_info->m_totalCost = newCell->m_info->m_costSoFar + costRemaining;
			rva003D6400(newCell);
		}
	}

	m_isTunneling = false;
	if (goalCell->hasInfo() && !goalCell->getClosed() && !goalCell->getOpen())
		goalCell->rva003F6F10();
	rva003D5FC0();
	return MAX_COST;
}

#pragma comment(linker, "/alternatename:?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBUCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?worldToCell@Pathfinder@@QAE_NPBUCoord3D@@PAUICoord2D@@@Z=?j_000171e8@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCell@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@HH@Z=?j_00020671@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCell@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@PBUCoord3D@@@Z=?j_0003398d@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z=?j_000461ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?allocateCellInfos@PathfindCellInfo@@SAXXZ=?j_0003d1a9@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAcquirePathfindCellInfo@@YAPAVPathfindCellInfo@@PAPAV1@PAVPathfindCell@@PBUICoord2D@@@Z=?j_00021da0@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeIsComputerControlled@Object@@QBE_NXZ=?j_00010ea1@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeStepD4F90@Pathfinder@StepContract003D4F90@@QAE_NPAXPAVPathfindCell@2@@Z=?j_0002b9e0@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003F6F10@PathfindCell@@QAEXXZ=?j_0004b3b7@@YAXXZ")
#pragma comment(linker, "/alternatename:?startPathfind@PathfindCell@@QAE_NPAV1@@Z=?j_0003e9f5@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003DB900@Pathfinder@@QAEIPAVPathfindCell@@0@Z=?j_0003a828@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003D6400@Pathfinder@@QAEXPAVPathfindCell@@@Z=?j_00024ef1@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003D6490@Pathfinder@@QAEPAVPathfindCell@@XZ=?j_0003d3ed@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003F6C30@PathfindCell@@QAEXPAPAVPathfindCellInfo@@@Z=?j_00005e48@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003DAE40@Pathfinder@@QAEXPAVPathfindCell@@PAVObject@@@Z=?j_0001264d@@YAXXZ")
#pragma comment(linker, "/alternatename:?costSoFar@PathfindCell@@QAEIPAV1@@Z=?j_000169c3@@YAXXZ")
#pragma comment(linker, "/alternatename:?setParentCell@PathfindCell@@QAEXPAV1@@Z=?j_00040313@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003D5FC0@Pathfinder@@QAEXXZ=?j_00032b5f@@YAXXZ")

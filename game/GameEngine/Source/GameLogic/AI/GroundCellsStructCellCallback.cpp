// cl: /DNDEBUG /MD
//
// Retail 0x003DE940: 284 bytes, ret 0x10, reached through ILT 0x0004903F.
// BFME member form of Zero Hour's Pathfinder::groundCellsCallback
// (AIPathfind.cpp): the receiver is the ground line-walk record (pathfinder
// +0x00, goal cell +0x08, path diameter +0x0C) that findGroundPath builds,
// and the body is step for step the copy the matched line walk
// groundCellsAlongLine003E2620 (PathfinderFindGroundPath.cpp) inlines: open/
// closed abort, clearCellForDiameter against the record's diameter, cell
// info acquire, setBlockedByAlly(false), cost to goal, cost so far +2/+5,
// parent, total and the open-list bucket insert (0x003D6400 out of line
// here).  The record's original name is unproven, so the class keeps the
// address-derived name.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct ICoord2D { Int x, y; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class PathfindCell;

struct PathfindCellInfo
{
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
};
extern void *g_rva012F1094;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(PathfindCellInfo **freeListHead,
	PathfindCell *pathfindCell, const ICoord2D *cellPosition);

class PathfindCell
{
public:
	void setParentCellHierarchical(PathfindCell *parent);
	PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)((m_bits >> 6) & 0x3f); }

	PathfindCellInfo *m_info;
	Int m_unused04;
	UnsignedShort m_zone;
	UnsignedShort m_pad0a;
	UnsignedInt m_bits;
};

class BfmeThingBRE;
class Gen_003D6400 { public: void bfmeCopyIndexed(BfmeThingBRE *cell); };

class Pathfinder
{
public:
	Int clearCellForDiameter(UnsignedInt crusher, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int pathDiameter, Bool stopOnFail);
	UnsignedInt rva003DB900(PathfindCell *cell, PathfindCell *goalCell);
};

struct Rva003DE940GroundCellsStruct
{
	Pathfinder *pathfinder;
	Bool centerInCell;
	PathfindCell *goalCell;
	Int pathDiameter;

	Int cellCallback(PathfindCell *from, PathfindCell *to, Int to_x, Int to_y);
};

// ?cellCallback@Rva003DE940GroundCellsStruct@@QAEHPAVPathfindCell@@0HH@Z
Int Rva003DE940GroundCellsStruct::cellCallback(PathfindCell *from,
	PathfindCell *to, Int to_x, Int to_y)
{
	if (!from)
		return 0;

	if ((Bool)(to->m_info ? ((to->m_info->m_flags >> 3) & 1) : false) ||
		(Bool)(to->m_info ? ((to->m_info->m_flags >> 4) & 1) : false))
		return 1;

	if (pathfinder->clearCellForDiameter(0, to_x, to_y, to->getLayer(),
			pathDiameter, true) != pathDiameter)
		return 1;

	ICoord2D newCellCoord;
	newCellCoord.x = to_x;
	newCellCoord.y = to_y;
	if (to->m_info == 0)
	{
		if (g_rva012F1094 == 0)
			PathfindCellInfo::allocateCellInfos();
		to->m_info = bfmeAcquirePathfindCellInfo(reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), to, &newCellCoord);
	}
	else
	{
		to->m_info->m_prevOpen = 0;
	}
	to->m_info->m_flags &= ~1u;

	Int costRemaining = pathfinder->rva003DB900(to, goalCell);
	to->m_info->m_costSoFar = from->m_info->m_costSoFar + (((to->m_bits >> 24) & 1) ? 2 : 5);
	to->setParentCellHierarchical(from);
	to->m_info->m_totalCost = to->m_info->m_costSoFar + costRemaining;
	((Gen_003D6400 *)pathfinder)->bfmeCopyIndexed((BfmeThingBRE *)to);
	return 0;
}

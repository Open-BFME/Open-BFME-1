// ?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0H_N@Z
// partial score=0.4 date=2026-09-03
// cl: /DNDEBUG /MD
//
// BFME 0x003F2160: Pathfinder::findGroundPath.
//
// This is deliberately TU-local.  The retail function predates the current
// public Pathfinder declaration: its first and third machine arguments are an
// Object* and a Coord3D*, while the surviving decorated name says Coord3D*,
// Coord3D*, Int, Bool.  Keeping the decorated signature and recovering the
// live argument roles here preserves both the caller ABI and the retail body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short UnsignedShort;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

class Object
{
public:
	Bool bfmeIsComputerControlled(void) const;
};

class Path
{
public:
	~Path(void);
};
class PathfindCell;

class PathfindCellInfo
{
public:
	static void allocateCellInfos(void);

	ICoord2D m_pos;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	UnsignedShort m_totalCost;
	UnsignedShort m_costSoFar;
	Int m_pathParent;
	Int m_goalUnitID;
	Int m_posUnitID;
	Int m_goalAircraftID;
	UnsignedInt m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_freeNext;
	PathfindCellInfo **m_freePrevLink;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

extern PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

class PathfindCell
{
public:
	Bool startPathfind(PathfindCell *goalCell);
	void setParentCell(PathfindCell *parentCell);
	void listHelper(void *pathfinderList);
	UnsignedInt costSoFar(PathfindCell *parentCell);

	PathfindCellInfo *m_info;
	Int m_unused1;
	Int m_zone;
	UnsignedInt m_packed;

	Int getLayer(void) const { return (m_packed >> 6) & 0x3f; }
	UnsignedShort getXIndex(void) const
	{
		return (UnsignedShort)m_info->m_pos.x;
	}
	UnsignedShort getYIndex(void) const
	{
		return (UnsignedShort)m_info->m_pos.y;
	}
};

class BfmeGridAL
{
public:
	void bfmeClearAL(void) volatile;
	void bfmeFillAL(void) volatile;
	unsigned char bfmeNearAL(Int across, Int along) const volatile;
	unsigned char bfmeFarAL(Int across, Int along) const volatile;
	UnsignedShort getEffectiveZone(
		const PathfindMovementProfile &profile, UnsignedShort zone) const volatile;

private:
	unsigned char m_opaque[0x23634];
};

class BfmeClearAL
{
public:
	void clear(void) volatile;
};

class BfmeFillAL
{
public:
	void fill(void) volatile;
};

class BfmeNearAL
{
public:
	unsigned char nearCell(Int across, Int along) const volatile;
};

class BfmeFarAL
{
public:
	unsigned char farCell(Int across, Int along) const volatile;
};

class PathfindZoneManager
{
public:
	UnsignedShort getEffectiveZone(
		const PathfindMovementProfile &profile, UnsignedShort zone) const;

private:
	unsigned char m_opaque[0x23634];
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(
		Object *object, const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class Rva003F7380State
{
public:
	void finishReset(void);
};

class Gen_dtor_001500d0
{
public:
	virtual ~Gen_dtor_001500d0(void);
};

void __cdecl operator delete(void *path);

struct BfmeSeedNode
{
	unsigned char payload[0x80];
};

struct BfmeSeedTag
{
};

extern BfmeSeedNode *__cdecl j_0000dbe8(
	BfmeSeedNode *first, BfmeSeedNode *second, BfmeSeedNode *third,
	const BfmeSeedTag *formal, Int *zero);
extern void j_0000145b(void);
extern void j_000010fa5(void);
typedef void (__fastcall *BfmeZoneThunk)(void *zone);
extern unsigned char __cdecl bfmeNearCell(Int across, Int along);
extern unsigned char __cdecl bfmeFarCell(Int across, Int along);
extern UnsignedShort __cdecl bfmeEffectiveZone(
	const PathfindMovementProfile &profile, UnsignedShort zone);

class SubsystemInterface
{
public:
	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);
	virtual void draw(void);
};

class Snapshot
{
public:
	virtual void crc(void);
};

struct BfmeSeedNode;

extern void j_0001fa14(void);
extern void j_0003a828(void);
extern void j_00024ef1(void);
extern void j_0003d3ed(void);
extern void j_0005e48(void);
extern void j_0001264d(void);
extern void j_00035a2b(void);
extern void j_000169c3(void);
extern void j_00020da1(void);
extern void j_00032b5f(void);
extern void j_0001fbbd(void);
extern void j_00036b33(void);

class Pathfinder : SubsystemInterface, public Snapshot
{
public:
	Path *findGroundPath(const Coord3D *objectSlot,
		const Coord3D *from, Int rawToSlot, Bool diameterSlot);
	Path *internal_findHierarchicalPath(Int first, Int second, Object *object,
		const Coord3D *from, const Coord3D *to, Int last, Int flags);
	Int cellMetric(PathfindCell *cell, PathfindCell *goalCell);
	void cellPair(PathfindCell *cell);
	PathfindCell *firstLive(void);
	void layerHelper(PathfindCell *cell, Int zero);
	Int lineHelper(const ICoord2D *start, const ICoord2D *end,
		Int layer, void *info);
	Path *buildPath(const Coord3D *from, PathfindCell *goalCell,
		Bool center, Int diameter);
	void cleanup(void);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	PathfindCell *getClippedCell(PathfindLayerEnum layer, const Coord3D *position);
	void clip(Coord3D *from, Coord3D *to);
	Bool worldToCell(const Coord3D *world, ICoord2D *cell);
	Int clearCellForDiameter(Int crusher, Int cellX, Int cellY,
		Int layer, Int diameter, Int attackerOnWall);

private:
	Bool m_isMapReady;
	unsigned char m_pad09[7];
	PathfindCell **m_map;
	Int m_extent[4];
	unsigned char m_mid[0x85c - 0x24];
	unsigned char m_layers[16 * 0x44];
	volatile BfmeGridAL m_zoneManager;
	unsigned char m_afterZone[0x2470c - 0xc9c - 0x23634];
	BfmeSeedNode *m_2470c;
	BfmeSeedNode *m_24710;
};

typedef Int (__fastcall *ObjectIntFn)(Object *, void *);
typedef Bool (__fastcall *ObjectBoolFn)(Object *, void *);

// VC7.1 reserves __thiscall in a free-function-pointer typedef.  Fastcall
// keeps the object in ECX and consumes a dummy volatile EDX argument; all
// remaining arguments stay on the stack in the retail order.
struct GroundCellsInfo
{
	Pathfinder *thePathfinder;
	Bool centerInCell;
	PathfindCell *goalCell;
	Int pathDiameter;
};

union GroundPathScratch
{
	GroundCellsInfo lineInfo;
	Int adjacent[5];
};

struct GroundPathCoords
{
	ICoord2D cell;
	ICoord2D newCell;
};

union GroundPathPrepScratch
{
	GroundPathCoords coords;
	ICoord2D startCell;
	PathfindMovementProfile profile;
};

struct GroundPathPrepCore
{
	union
	{
		struct
		{
			Coord3D clipFrom;
			union
			{
				Coord3D adjustTo;
				ICoord2D newCell;
			} destination;
		} prep;
	} coords;
	union
	{
		ICoord2D cell;
		ICoord2D startCell;
	} low;
};

union GroundPathPrepFrame
{
	GroundPathPrepCore prep;
	PathfindMovementProfile profile;
};

struct GroundPathSearchFrame
{
	Bool neighborFlags[8];
	union
	{
		struct
		{
			ICoord2D lineStart;
			ICoord2D lineEnd;
		} line;
		ICoord2D newCellCoord;
	} coords;
	union
	{
		GroundCellsInfo lineInfo;
		Int adjacent[5];
	} callback;
};

union GroundPathState
{
	GroundPathPrepCore prep;
	PathfindMovementProfile profile;
	GroundPathSearchFrame search;
	unsigned char retailFrameShape[0x48];
};

#define self this
#define source from

Path *Pathfinder::findGroundPath(const Coord3D *objectSlot,
	const Coord3D *from, Int rawToSlot, Bool diameterSlot)
{
	Bool centerInCell = false;
	Int pathDiameter;
	PathfindCell *goalCell;
	PathfindCell *parentCell;
	GroundPathState prep;
	self->m_zoneManager.bfmeClearAL();
	Bool isHuman = true;

	// The first call is the BFME replacement for the old hierarchical-path
	// setup.  It intentionally takes the address of the surviving first formal;
	// retail's callee uses that stack slot as its object argument.
	BfmeSeedNode *seed = j_0000dbe8(
		self->m_24710,
		self->m_24710,
		self->m_2470c,
		(const BfmeSeedTag *)&objectSlot, 0);
	self->m_24710 = seed;
	const Coord3D *targetPosition =
		(const Coord3D *)(unsigned int)rawToSlot;
	const Coord3D *startPosition = from;
	Path *hierarchicalPath = self->internal_findHierarchicalPath(
		isHuman, 1, (Object *)objectSlot, startPosition,
		targetPosition, 0, 0);
	if (hierarchicalPath != 0)
	{
		delete hierarchicalPath;
	}
	else
	{
		j_000010fa5();
	}

	if (targetPosition->x == *(const float *)0x01075350 &&
		targetPosition->y == *(const float *)0x01075350)
		return 0;
	if (!self->m_isMapReady)
		return 0;

	pathDiameter = *(Int *)&diameterSlot;
	{
		prep.prep.coords.prep.destination.adjustTo = *targetPosition;
		prep.prep.coords.prep.clipFrom = *startPosition;
		clip(&prep.prep.coords.prep.clipFrom,
			&prep.prep.coords.prep.destination.adjustTo);
		*((Bool *)((char *)self + 0x83c)) = false;

		PathfindLayerEnum destinationLayer =
			TheTerrainLogic->getLayerForDestination((Object *)objectSlot,
				&prep.prep.coords.prep.destination.adjustTo);
		worldToCell(&prep.prep.coords.prep.destination.adjustTo,
			&prep.prep.low.cell);

	if (pathDiameter != self->clearCellForDiameter(0,
		prep.prep.low.cell.x, prep.prep.low.cell.y,
		destinationLayer, pathDiameter, 1))
	{
		Int offset = 1;
		const Int maxOffset = 8;
		while (offset < maxOffset)
		{
			prep.prep.coords.prep.destination.newCell =
				prep.prep.low.cell;
			prep.prep.low.cell.x += offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.y += offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.x -= offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.x -= offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.y -= offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.y -= offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.x += offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			prep.prep.low.cell.x += offset;
			if (self->clearCellForDiameter(0, prep.prep.low.cell.x,
				prep.prep.low.cell.y, destinationLayer,
				pathDiameter, 1) == pathDiameter) break;
			++offset;
			prep.prep.low.cell =
				prep.prep.coords.prep.destination.newCell;
		}
		if (offset >= maxOffset)
			return 0;
	}

	goalCell = self->getCell(destinationLayer,
		prep.prep.low.cell.x, prep.prep.low.cell.y);
	if (goalCell == 0)
		return 0;
	if (goalCell->m_info == 0)
	{
		if (g_bfmePathfindFreeList == 0)
			PathfindCellInfo::allocateCellInfos();
		goalCell->m_info = bfmeAcquirePathfindCellInfo(
			&g_bfmePathfindFreeList, goalCell, &prep.prep.low.cell);
	}
	else
	{
		goalCell->m_info->m_prevOpen = 0;
	}

	PathfindLayerEnum startLayer =
			TheTerrainLogic->getLayerForDestination((Object *)objectSlot,
				startPosition);
		parentCell = self->getClippedCell(startLayer,
			&prep.prep.coords.prep.clipFrom);
		if (parentCell == 0)
			return 0;

		if (parentCell != goalCell)
		{
			worldToCell(&prep.prep.coords.prep.clipFrom,
				&prep.prep.low.startCell);
			if (parentCell->m_info == 0)
			{
				if (g_bfmePathfindFreeList == 0)
					PathfindCellInfo::allocateCellInfos();
				parentCell->m_info = bfmeAcquirePathfindCellInfo(
					&g_bfmePathfindFreeList, parentCell,
					&prep.prep.low.startCell);
			}
			else
			{
				parentCell->m_info->m_prevOpen = 0;
			}
		}
	}

	Bool computerControlled =
		((Object *)objectSlot)->bfmeIsComputerControlled();
	Int level = ((ObjectIntFn)&j_0001fbbd)((Object *)objectSlot, 0) - 1;
	Bool playerOwned = ((ObjectBoolFn)&j_00036b33)(
		(Object *)objectSlot, 0);
	prep.profile.acceptableSurfaces = 1;
	prep.profile.crusher = !playerOwned;
	prep.profile.terrainOnly = computerControlled;
	prep.profile.layer = level;

	UnsignedShort parentZone = self->m_zoneManager.getEffectiveZone(
		prep.profile, (UnsignedShort)parentCell->m_zone);
	UnsignedShort goalZone = self->m_zoneManager.getEffectiveZone(
		prep.profile, (UnsignedShort)goalCell->m_zone);
	if (parentZone != goalZone)
	{
		((Rva003F7380State *)goalCell)->finishReset();
		((Rva003F7380State *)parentCell)->finishReset();
		return 0;
	}

	parentCell->startPathfind(goalCell);
	(parentCell->m_info->m_totalCost =
		self->cellMetric(parentCell, goalCell),
		self->cellPair(parentCell));
	PathfindCell *current = self->firstLive();
	if (current == 0)
	{
		((Rva003F7380State *)goalCell)->finishReset();
		self->cleanup();
		return 0;
	}

	while (current != 0)
	{
		if (current == goalCell)
		{
			Path *path = self->buildPath(startPosition, goalCell,
				centerInCell, pathDiameter);
			((Rva003F7380State *)current)->finishReset();
			self->cleanup();
			return path;
		}

		current->listHelper((void *)((char *)self + 0x838));
		self->layerHelper(current, 0);

		#define search prep.search
		search.coords.line.lineStart.x = current->getXIndex();
		search.coords.line.lineStart.y = current->getYIndex();
		search.coords.line.lineEnd.x = goalCell->getXIndex();
		search.coords.line.lineEnd.y = goalCell->getYIndex();
		search.callback.lineInfo.thePathfinder = self;
		search.callback.lineInfo.centerInCell = centerInCell;
		search.callback.lineInfo.goalCell = goalCell;
		search.callback.lineInfo.pathDiameter = pathDiameter;
		self->lineHelper(&search.coords.line.lineStart,
			&search.coords.line.lineEnd, current->getLayer(),
			&search.callback.lineInfo);

		search.callback.adjacent[0] = 0;
		search.callback.adjacent[1] = 1;
		search.callback.adjacent[2] = 2;
		search.callback.adjacent[3] = 3;
		search.callback.adjacent[4] = 0;
		search.neighborFlags[0] = false;
		search.neighborFlags[1] = false;
		search.neighborFlags[2] = false;
		search.neighborFlags[3] = false;
		search.neighborFlags[4] = false;
		search.neighborFlags[5] = false;
		search.neighborFlags[6] = false;
		search.neighborFlags[7] = false;

		Int i = 0;
		while (i < 8)
		{
			search.neighborFlags[i] = false;
			search.coords.newCellCoord.x =
				current->getXIndex() +
				*((const Int *)(0x012b4b38 + i * 4));
			search.coords.newCellCoord.y =
				current->getYIndex() +
				*((const Int *)(0x012b4b10 + i * 4));
			PathfindCell *newCell = self->getCell((PathfindLayerEnum)current->getLayer(),
				search.coords.newCellCoord.x,
				search.coords.newCellCoord.y);
			if (newCell == 0)
			{
				++i;
				continue;
			}

			if (newCell->getLayer() == LAYER_GROUND &&
				!self->m_zoneManager.bfmeNearAL(
					search.coords.newCellCoord.x,
					search.coords.newCellCoord.y))
			{
				Bool passable = false;
				if (self->m_zoneManager.bfmeFarAL(
					search.coords.newCellCoord.x + 3,
					search.coords.newCellCoord.y + 3)) passable = true;
				if (self->m_zoneManager.bfmeFarAL(
					search.coords.newCellCoord.x - 3,
					search.coords.newCellCoord.y + 3)) passable = true;
				if (self->m_zoneManager.bfmeFarAL(
					search.coords.newCellCoord.x + 3,
					search.coords.newCellCoord.y - 3)) passable = true;
				if (self->m_zoneManager.bfmeFarAL(
					search.coords.newCellCoord.x - 3,
					search.coords.newCellCoord.y - 3)) passable = true;
				if (!passable)
				{
					++i;
					continue;
				}
			}

			Bool onList = false;
			if (newCell->m_info != 0)
			{
				if ((newCell->m_info->m_flags & 8) != 0 ||
					(newCell->m_info->m_flags & 16) != 0)
					onList = true;
			}

			Int clearDiameter = 0;
			UnsignedInt newCostSoFar;
			if (newCell != goalCell)
			{
				if (i >= 4 &&
					!search.neighborFlags[search.callback.adjacent[i - 4]] &&
					!search.neighborFlags[search.callback.adjacent[i - 3]])
				{
					++i;
					continue;
				}

				clearDiameter = self->clearCellForDiameter(0,
					search.coords.newCellCoord.x,
					search.coords.newCellCoord.y,
					newCell->getLayer(), pathDiameter, 0);
				if ((newCell->m_packed & 7) != 0 ||
					((newCell->m_packed >> 18) & 1) != 0)
				{
					++i;
					continue;
				}
				search.neighborFlags[i] = true;

				if (newCell->m_info == 0)
				{
					if (g_bfmePathfindFreeList == 0)
						PathfindCellInfo::allocateCellInfos();
				newCell->m_info = bfmeAcquirePathfindCellInfo(
					&g_bfmePathfindFreeList, newCell,
					&search.coords.newCellCoord);
				}
				else
				{
					newCell->m_info->m_prevOpen = 0;
				}

				newCostSoFar = newCell->costSoFar(current);
				if (clearDiameter < pathDiameter)
				{
					Int delta = pathDiameter - clearDiameter;
					newCostSoFar += 0.6f * (delta * 10);
				}
				newCell->m_info->m_flags &= ~1u;
			}

			Int costRemaining = self->cellMetric(newCell, goalCell);
			if (onList && newCell->m_info->m_costSoFar <=
				(UnsignedShort)newCostSoFar)
			{
				++i;
				continue;
			}

			newCell->m_info->m_costSoFar = (UnsignedShort)newCostSoFar;
			newCell->setParentCell(current);
			newCell->m_info->m_totalCost =
				newCell->m_info->m_costSoFar + (UnsignedShort)costRemaining;
			self->cellPair(newCell);
			++i;
		}

		current = self->firstLive();
	}

	((Rva003F7380State *)goalCell)->finishReset();
	self->cleanup();
	return 0;
}

#undef search
#undef source
#undef self

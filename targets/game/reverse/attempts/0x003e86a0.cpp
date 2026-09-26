// ?getMoveAwayFromPath@Pathfinder@@QAEPAVPath@@PAVObject@@0PAV2@01@Z
// partial score=0.25 date=2026-09-20
// cl: /DNDEBUG /MD
//
// Retail 0x003E86A0: Pathfinder::getMoveAwayFromPath.
//
// This TU deliberately keeps the BFME Pathfinder and cell layouts local.  The
// shared Zero Hour header puts m_isMapReady at a different offset and cannot
// describe the indexed BFME open-list slots.  All out-of-line calls below are
// made through the retail ILT names reported by tools/callees.py.
//
// PROGRESS 2026-09-20: FRAME BLOCKER FIXED. The prior 0.2 bank used a 0xBC
// frame vs retail 0xB4 (8 bytes = 2 dwords too many). Root cause: the local
// TCheckMovementInfo (BfmeMovementInfo) was sized 36 bytes with four trailing
// fields (m_allyFixedCount + 3 bools) that BFME does not have. Retail's struct
// spans exactly 0x1c = 28 bytes (cell[8], layer, radius, centerInCell byte,
// considerTransient byte, +2 pad, acceptableSurfaces, ignoreObstacle), stored
// at esp+0x8c..0xa8 in the retail dump. Trimming it to 28 bytes makes
// `sub esp,0xb4` byte-match and moves the first divergence from +8 to +24.
//
// REMAINING BLOCKER (register/slot cascade, ~1175 bytes still differ):
// retail keeps obj in EBX and &obj->position (obj+0x38) in EDI; our build
// consistently assigns obj->EDI and &pos->EBX (a clean ebx<->edi swap that
// cascades through nearly every instruction). Retail also RELOADS obj from
// [ebp+8] inside the while-loop (at +0x508 and +0x5ac) because the
// pathToAvoid2 node loop reuses EBX as its node pointer, breaking obj's live
// range; our loop keeps obj live in EDI throughout, so EDI is never freed for
// the loop's currentInfo temporary. Consequently our local-slot packing also
// diverges (getRadiusAndCenter outputs land at esp+0x27/0x64 vs retail
// 0x13/0x24). Tried and REJECTED (no register flip): separating &pos into a
// named objPos local, giving obj a named local copy, and CSE'd-inline vs
// named-pointer variants. This is a global-allocator/loop-pressure match, not
// a single source-shape lever; next worker must induce obj's in-loop reload
// (free EDI in the loop) to reproduce retail's ebx=obj / edi=currentInfo.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

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
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class Player;
class Pathfinder;

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool bfmeIsComputerControlled() const;
	Int bfmeScale() const;
};

struct PathfindCellInfo;

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
	Int m_zone;
	Int m_unused08;
	UnsignedInt m_bits;
};

struct PathfindCellInfo
{
	ICoord2D m_pos;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	UnsignedShort m_totalCost;
	UnsignedShort m_costSoFar;
	UnsignedInt m_pathParent;
	UnsignedInt m_goalUnit;
	UnsignedInt m_posUnit;
	UnsignedInt m_goalAircraft;
	UnsignedInt m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_freeNext;
	PathfindCellInfo **m_freePrevLink;
};

class PathNode
{
public:
	char m_pad[8];
	PathNode *m_nextOptimized;
	Coord3D m_position;
};

class Path
{
public:
	char m_prefix[4];
	PathNode *m_first;
};

class Overridable
{
};

class BfmeZoneManager
{
public:
	void setAllPassable();
};

class BfmeMovementInfo
{
public:
	ICoord2D m_cell;
	Int m_layer;
	Int m_radius;
	Bool m_centerInCell;
	Bool m_considerTransient;
	Int m_acceptableSurfaces;
	Int m_ignoreObstacle;
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

class BfmeAIUpdate
{
public:
	Int ignoredObstacle();
};

class LocomotorSet
{
};

class Pathfinder
{
public:
	Path *getMoveAwayFromPath(Object *obj, Object *otherObj,
		Path *pathToAvoid, Object *otherObj2, Path *pathToAvoid2);
};

extern void j_000022bb();
extern void j_000059c0();
extern void j_00005e48();
extern void j_0000dbe8();
extern void j_00010ea1();
extern void j_00010fa5();
extern void j_0001264d();
extern void j_000127a6();
extern void j_000171e8();
extern void j_0001a36b();
extern void j_0001ffe1();
extern void j_00020671();
extern void j_00020824();
extern void j_00021da0();
extern void j_00024ef1();
extern void j_0002b9e0();
extern void j_00032b5f();
extern void j_00036642();
extern void j_0003a391();
extern void j_0003d1a9();
extern void j_0003e9f5();
extern void j_000411d2();
extern void j_00044a3f();
extern void j_000461ff();
extern void j_00049f3f();
extern void j_0004a980();
extern void j_0004b3b7();

extern float g_bfmeK1266C;
extern float g_bfmeOffsetDF;
extern PathfindCellInfo *g_bfmePathfindFreeList;

static __forceinline Int readInt(const void *p, UnsignedInt offset)
{
	return *(const Int *)((const unsigned char *)p + offset);
}

static __forceinline UnsignedInt readUnsigned(const void *p,
	UnsignedInt offset)
{
	return *(const UnsignedInt *)((const unsigned char *)p + offset);
}

static __forceinline void *readPointer(const void *p, UnsignedInt offset)
{
	return *(void **)((const unsigned char *)p + offset);
}

static __forceinline Bool readBool(const void *p, UnsignedInt offset)
{
	return *(const unsigned char *)((const unsigned char *)p + offset) != 0;
}

static __forceinline PathfindCellInfo **openSlots(Pathfinder *self)
{
	return (PathfindCellInfo **)((unsigned char *)self + 0x34);
}

static __forceinline Int &firstOpenSlot(Pathfinder *self)
{
	return *(Int *)((unsigned char *)self + 0x834);
}

static __forceinline PathfindCellInfo **openHead(Pathfinder *self)
{
	return (PathfindCellInfo **)((unsigned char *)self + 0x838);
}

static __forceinline unsigned char &tunneling(Pathfinder *self)
{
	return *(unsigned char *)((unsigned char *)self + 0x83c);
}

static __forceinline Int getCellLayer(const PathfindCell *cell)
{
	return (Int)((cell->m_bits >> 6) & 0x3f);
}

static __forceinline Player *controllingPlayer(Object *object)
{
	union
	{
		void (*raw)(void);
		Player *(Object::*member)() const;
	} call;
	call.raw = j_00020824;
	return (object->*call.member)();
}

static __forceinline void getRadiusAndCenter(Pathfinder *self, const Object *object,
	Int *radius, Bool *center)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)(const Object *, Int *, Bool *);
	} call;
	call.raw = j_000461ff;
	(self->*call.member)(object, radius, center);
}

static __forceinline Coord3D *clearPathCellVector(Coord3D *first, Coord3D *last,
	Coord3D *result, void *tag, Int zero)
{
	union
	{
		void (*raw)(void);
		Coord3D *(*function)(Coord3D *, Coord3D *, Coord3D *, void *, Int);
	} call;
	call.raw = j_0000dbe8;
	return call.function(first, last, result, tag, zero);
}

static __forceinline void setAllPassable(BfmeZoneManager *manager)
{
	union
	{
		void (*raw)(void);
		void (BfmeZoneManager::*member)();
	} call;
	call.raw = j_00010fa5;
	(manager->*call.member)();
}

static __forceinline Bool worldToCell(Pathfinder *self, const Coord3D *position,
	ICoord2D *cell)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(const Coord3D *, ICoord2D *);
	} call;
	call.raw = j_000171e8;
	return (self->*call.member)(position, cell);
}

static __forceinline Int objectLayer(const Object *object)
{
	union
	{
		void (*raw)(void);
		Int (Object::*member)() const;
	} call;
	call.raw = j_0003a391;
	return (object->*call.member)();
}

static __forceinline PathfindCell *getCell(Pathfinder *self, Int layer, Int x, Int y)
{
	union
	{
		void (*raw)(void);
		PathfindCell *(Pathfinder::*member)(Int, Int, Int);
	} call;
	call.raw = j_00020671;
	return (self->*call.member)(layer, x, y);
}

static __forceinline const void *finalTemplate(const void *thingTemplate)
{
	if (thingTemplate != 0)
	{
		const Overridable *overrideObject = *(const Overridable **)(
			(const unsigned char *)thingTemplate + 4);
		if (overrideObject != 0)
		{
			union
			{
				void (*raw)(void);
				const Overridable *(Overridable::*member)() const;
			} call;
			call.raw = j_000022bb;
			return (overrideObject->*call.member)();
		}
	}
	return thingTemplate;
}

static __forceinline Bool isComputerControlled(const Object *object)
{
	union
	{
		void (*raw)(void);
		Bool (Object::*member)() const;
	} call;
	call.raw = j_00010ea1;
	return (object->*call.member)();
}

static __forceinline Bool checkMovement(Pathfinder *self, Object *object,
	BfmeMovementInfo *info)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(Object *, BfmeMovementInfo *);
	} call;
	call.raw = j_0004a980;
	return (self->*call.member)(object, info);
}

static __forceinline void initMovementInfo(BfmeMovementInfo *info)
{
	union
	{
		void (*raw)(void);
		void (BfmeMovementInfo::*member)();
	} call;
	call.raw = j_00036642;
	(info->*call.member)();
}

static __forceinline Int ignoredObstacle(BfmeAIUpdate *ai)
{
	union
	{
		void (*raw)(void);
		Int (BfmeAIUpdate::*member)();
	} call;
	call.raw = j_0001a36b;
	return (ai->*call.member)();
}

static __forceinline Bool stepCell(Pathfinder *self, BfmeMovementInfo *info,
	PathfindCell *cell)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(void *, PathfindCell *);
	} call;
	call.raw = j_0002b9e0;
	return (self->*call.member)((void *)info, cell);
}

static __forceinline PathfindCellInfo *acquireInfo(PathfindCellInfo **freeList,
	PathfindCell *cell, const ICoord2D *position)
{
	union
	{
		void (*raw)(void);
		PathfindCellInfo *(*function)(PathfindCellInfo **, PathfindCell *,
			const ICoord2D *);
	} call;
	call.raw = j_00021da0;
	return call.function(freeList, cell, position);
}

static __forceinline void allocateInfos()
{
	union
	{
		void (*raw)(void);
		void (*function)();
	} call;
	call.raw = j_0003d1a9;
	call.function();
}

static __forceinline Bool startPathfind(PathfindCell *cell)
{
	union
	{
		void (*raw)(void);
		Bool (PathfindCell::*member)(PathfindCell *);
	} call;
	call.raw = j_0003e9f5;
	return (cell->*call.member)(0);
}

static __forceinline void copyIndexed(Pathfinder *self, PathfindCell *cell)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)(PathfindCell *);
	} call;
	call.raw = j_00024ef1;
	(self->*call.member)(cell);
}

static __forceinline void resetLists(Pathfinder *self)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)();
	} call;
	call.raw = j_00032b5f;
	(self->*call.member)();
}

static __forceinline void adjustCoordToCell(Pathfinder *self, Int x, Int y,
	Bool center, Coord3D *position, Int layer)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)(Int, Int, Bool, Coord3D *, Int);
	} call;
	call.raw = j_000411d2;
	(self->*call.member)(x, y, center, position, layer);
}

static __forceinline void detachCell(PathfindCell *cell)
{
	union
	{
		void (*raw)(void);
		void (PathfindCell::*member)();
	} call;
	call.raw = j_00044a3f;
	(cell->*call.member)();
}

static __forceinline Bool lineInRegion(const Coord2D *start, const Coord2D *end,
	const Region2D *bounds)
{
	union
	{
		void (*raw)(void);
		Bool (*function)(const Coord2D *, const Coord2D *, const Region2D *);
	} call;
	call.raw = j_0001ffe1;
	return call.function(start, end, bounds);
}

static __forceinline Bool innerMovement(Pathfinder *self, Object *object, Int x, Int y,
	Int layer, Int radius, Bool center, void **slot)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(void *, void *, void *, void *, void *,
			void *, void **, Int);
	} call;
	call.raw = j_00049f3f;
	return (self->*call.member)((void *)object, (void *)x, (void *)y,
		(void *)layer, (void *)radius, (void *)(Int)center, slot, 0);
}

static __forceinline Path *buildActualPath(Pathfinder *self, Object *object,
	Int surfaces, const Coord3D *position, PathfindCell *cell, Bool center)
{
	union
	{
		void (*raw)(void);
		Path *(Pathfinder::*member)(const Object *, Int, const Coord3D *,
			PathfindCell *, Bool, Bool);
	} call;
	call.raw = j_000059c0;
	return (self->*call.member)(object, surfaces, position, cell, center,
		false);
}

static __forceinline void releaseInfo(PathfindCell *cell)
{
	union
	{
		void (*raw)(void);
		void (PathfindCell::*member)();
	} call;
	call.raw = j_0004b3b7;
	(cell->*call.member)();
}

static __forceinline void moveInfo(PathfindCell *cell, PathfindCellInfo **head)
{
	union
	{
		void (*raw)(void);
		void (PathfindCell::*member)(PathfindCellInfo **);
	} call;
	call.raw = j_00005e48;
	(cell->*call.member)(head);
}

static __forceinline void expandLayers(Pathfinder *self, PathfindCell *cell,
	Object *object)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)(PathfindCell *, Object *);
	} call;
	call.raw = j_0001264d;
	(self->*call.member)(cell, object);
}

static __forceinline Int examineNeighbors(Pathfinder *self, PathfindCell *cell,
	const LocomotorSet *locomotorSet, Bool human, Bool center, Int radius,
	const ICoord2D *startCell, const Object *object)
{
	union
	{
		void (*raw)(void);
		Int (Pathfinder::*member)(PathfindCell *, PathfindCell *,
			const LocomotorSet &, Bool, Bool, Int, const ICoord2D &,
			const Object *, Int);
	} call;
	call.raw = j_000127a6;
	return (self->*call.member)(cell, 0, *locomotorSet, human, center,
		radius, *startCell, object, 0);
}

Path *Pathfinder::getMoveAwayFromPath(Object *obj, Object *otherObj,
	Path *pathToAvoid, Object *otherObj2, Path *pathToAvoid2)
{
	if (!readBool(this, 8))
		return 0;

	Bool isHuman = true;
	if (controllingPlayer(obj) != 0 &&
		readInt(controllingPlayer(obj), 0x2c) == 1)
		isHuman = false;

	Bool otherCenter;
	Int otherRadius;
	getRadiusAndCenter(this, otherObj, &otherRadius, &otherCenter);

	Coord3D *pathCellsBegin = *(Coord3D **)((unsigned char *)this + 0x2470c);
	Coord3D *pathCellsFinish = *(Coord3D **)((unsigned char *)this + 0x24710);
	char tag;
	pathCellsFinish = clearPathCellVector(pathCellsFinish, pathCellsFinish,
		pathCellsBegin, &tag, 0);
	*(Coord3D **)((unsigned char *)this + 0x24710) = pathCellsFinish;
	setAllPassable((BfmeZoneManager *)((unsigned char *)this + 0xc9c));

	Bool centerInCell;
	Int radius;
	getRadiusAndCenter(this, obj, &radius, &centerInCell);

	Coord3D startPos = *(const Coord3D *)((const unsigned char *)obj + 0x38);
	if (!centerInCell)
	{
		startPos.x += g_bfmeK1266C;
		startPos.x += g_bfmeK1266C;
	}

	const Coord3D *objPos = (const Coord3D *)((const unsigned char *)obj + 0x38);
	ICoord2D startCellNdx;
	worldToCell(this, &startPos, &startCellNdx);
	Int layer = objectLayer(obj);
	ICoord2D parentCellNdx;
	worldToCell(this, objPos, &parentCellNdx);
	PathfindCell *parentCell = getCell(this, layer, parentCellNdx.x,
		parentCellNdx.y);
	if (parentCell == 0)
		return 0;

	BfmeAIUpdate *ai = (BfmeAIUpdate *)readPointer(obj, 0x204);
	if (ai == 0)
		return 0;

	const void *thingTemplate = readPointer(obj, 4);
	const void *effectiveTemplate = finalTemplate(thingTemplate);
	Int templateLayer = readInt(effectiveTemplate, 0x444);
	effectiveTemplate = finalTemplate(thingTemplate);
	Bool templateFlag = readBool(effectiveTemplate, 0x4cc);
	Int acceptableSurfaces = readInt(ai, 0x1b8);
	Bool crusher = isComputerControlled(obj);

	BfmeStepInfo stepInfo;
	stepInfo.m_surfaces = acceptableSurfaces;
	stepInfo.m_field04 = !templateFlag;
	stepInfo.m_allowAircraftGoal = crusher;
	stepInfo.m_maxLayer = templateLayer - 1;
	tunneling(this) = 0;
	if (!stepCell(this, (BfmeMovementInfo *)&stepInfo, parentCell))
		tunneling(this) = 1;

	BfmeMovementInfo movementInfo;
	initMovementInfo(&movementInfo);
	movementInfo.m_cell = startCellNdx;
	movementInfo.m_layer = layer;
	movementInfo.m_radius = radius;
	movementInfo.m_centerInCell = centerInCell;
	movementInfo.m_considerTransient = false;
	movementInfo.m_acceptableSurfaces = acceptableSurfaces;
	movementInfo.m_ignoreObstacle = ignoredObstacle(ai);
	if (!checkMovement(this, obj, &movementInfo))
		tunneling(this) = 1;

	if (parentCell->m_info == 0)
	{
		if (g_bfmePathfindFreeList == 0)
			allocateInfos();
		parentCell->m_info = acquireInfo(&g_bfmePathfindFreeList,
			parentCell, &startCellNdx);
	}
	else
	{
		parentCell->m_info->m_prevOpen = 0;
	}
	startPathfind(parentCell);
	copyIndexed(this, parentCell);

	Real boxHalfWidth = (Real)(radius * 10) - g_bfmeOffsetDF;
	if (centerInCell)
		boxHalfWidth += g_bfmeK1266C;
	boxHalfWidth += (Real)(otherRadius * 10);
	if (otherCenter)
		boxHalfWidth += g_bfmeK1266C;

	LocomotorSet *locomotorSet = (LocomotorSet *)((unsigned char *)ai +
		0x1a8);

	for (;;)
	{
		Int index = firstOpenSlot(this);
		if (index >= 0x200)
		{
			tunneling(this) = 0;
			resetLists(this);
			return 0;
		}

		while (openSlots(this)[index] == 0)
		{
			++index;
			firstOpenSlot(this) = index;
			if (index >= 0x200)
			{
				tunneling(this) = 0;
				resetLists(this);
				return 0;
			}
		}

		PathfindCellInfo *currentInfo = openSlots(this)[index];
		parentCell = currentInfo->m_cell;
		detachCell(parentCell);
		if (parentCell == 0)
			continue;

		Coord3D cellCenter;
		adjustCoordToCell(this, currentInfo->m_pos.x, currentInfo->m_pos.y,
			centerInCell, &cellCenter, getCellLayer(parentCell));
		Region2D bounds;
		bounds.lo.x = cellCenter.x - boxHalfWidth;
		bounds.lo.y = cellCenter.y - boxHalfWidth;
		bounds.hi.x = cellCenter.x + boxHalfWidth;
		bounds.hi.y = cellCenter.y + boxHalfWidth;

		Bool overlap = false;
		if (obj != 0 && bounds.lo.x < *(const Real *)((const unsigned char *)obj + 0x38) &&
			bounds.hi.x > *(const Real *)((const unsigned char *)obj + 0x38) &&
			bounds.lo.y < *(const Real *)((const unsigned char *)obj + 0x3c) &&
			bounds.hi.y > *(const Real *)((const unsigned char *)obj + 0x3c))
			overlap = true;

		for (PathNode *node = pathToAvoid != 0 ? pathToAvoid->m_first : 0;
			node != 0 && node->m_nextOptimized != 0;
			node = node->m_nextOptimized)
		{
			Coord2D start;
			Coord2D end;
			start.x = node->m_position.x;
			start.y = node->m_position.y;
			end.x = node->m_nextOptimized->m_position.x;
			end.y = node->m_nextOptimized->m_position.y;
			if (lineInRegion(&start, &end, &bounds))
			{
				overlap = true;
				break;
			}
		}

		if (otherObj != 0)
		{
			overlap = true;
			const Real otherX = *(const Real *)((const unsigned char *)otherObj + 0x38);
			const Real otherY = *(const Real *)((const unsigned char *)otherObj + 0x3c);
			if (bounds.lo.x < otherX && bounds.hi.x > otherX &&
				bounds.lo.y < otherY && bounds.hi.y > otherY)
				overlap = true;
		}

		if (!overlap && pathToAvoid2 != 0)
		{
			for (PathNode *node = pathToAvoid2->m_first;
				node != 0 && node->m_nextOptimized != 0;
				node = node->m_nextOptimized)
			{
				Coord2D start;
				Coord2D end;
				start.x = node->m_position.x;
				start.y = node->m_position.y;
				end.x = node->m_nextOptimized->m_position.x;
				end.y = node->m_nextOptimized->m_position.y;
				if (lineInRegion(&start, &end, &bounds))
				{
					overlap = true;
					break;
				}
			}
		}

		if (!overlap && currentInfo->m_pos.x == startCellNdx.x &&
			currentInfo->m_pos.y == startCellNdx.y)
			overlap = true;

		if (!overlap)
		{
			void *output = 0;
			if (innerMovement(this, obj, currentInfo->m_pos.x,
				currentInfo->m_pos.y, getCellLayer(parentCell), radius,
				centerInCell, &output) && output != 0)
			{
				tunneling(this) = 0;
				Path *newPath = buildActualPath(this, obj,
					acceptableSurfaces, (const Coord3D *)((const unsigned char *)obj + 0x38),
					parentCell, centerInCell);
				releaseInfo(parentCell);
				resetLists(this);
				return newPath;
			}
		}

		moveInfo(parentCell, openHead(this));
		expandLayers(this, parentCell, obj);
		examineNeighbors(this, parentCell, locomotorSet, isHuman,
			centerInCell, radius, &startCellNdx, obj);
	}
}

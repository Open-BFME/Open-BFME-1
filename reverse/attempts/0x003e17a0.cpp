// ?getAircraftPath@Pathfinder@@QAEPAVPath@@PBVObject@@PBUCoord3D@@@Z
// partial score=0.25 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003E17A0: the BFME aircraft path search.  The Zero Hour source
// calls its aircraft helper a quick two-node jog; BFME's body instead walks
// the compact live-cell queue and hands the winning cell to prependCells.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

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

class Object;
class Pathfinder;

class PathfindCell;

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

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
	Int m_field04;
	Int m_field08;
	UnsignedInt m_bits;
};

class Path
{
public:
	Path();
	char m_pad00[0x0c];
	unsigned char m_complete;
	char m_pad0d[0x17];
};

class BfmeOverridable
{
};

class BfmeAIUpdate
{
public:
	char m_pad[0x1b8];
	Int m_acceptableSurfaces;
};

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}

	BfmeOverridable *getTemplate(void) const
	{
		return *(BfmeOverridable **)((const unsigned char *)this + 4);
	}

	BfmeAIUpdate *getAI(void) const
	{
		return *(BfmeAIUpdate **)((const unsigned char *)this + 0x204);
	}

	Bool bfmeIsComputerControlled(void) const;
};

class TerrainLogic
{
};

class Gen_003D6490
{
};

class Gen_003DB900
{
};

class Pathfinder
{
public:
	Path *getAircraftPath(const Object *object, const Coord3D *to);

	char m_pad00[0x838];
	PathfindCellInfo *m_openHead;
	char m_pad83c[8];
	Int m_ignoreObstacleID;
};

extern void j_000022bb();
extern void j_00005e48();
extern void j_0000af24();
extern void j_00010ea1();
extern void j_0001264d();
extern void j_000169c3();
extern void j_000171e8();
extern void j_0001c675();
extern void j_00020671();
extern void j_00021da0();
extern void j_00024ef1();
extern void j_0002b9e0();
extern void j_00032b5f();
extern void j_000335b4();
extern void j_0003a391();
extern void j_0003a828();
extern void j_0003d1a9();
extern void j_0003d3ed();
extern void j_0003e9f5();
extern void j_00040313();
extern void j_000461ff();
extern void j_00047384();
extern void j_0004b3b7();

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define g_bfmePathfindFreeList (*(PathfindCellInfo **)0x012F1094)
#define g_bfmeDirectionX (*((const Int (*)[8])0x012B4A70))
#define g_bfmeDirectionY (*((const Int (*)[8])0x012B4A98))

static __forceinline const BfmeOverridable *finalTemplate(
	const BfmeOverridable *thingTemplate)
{
	if (thingTemplate != 0)
	{
		const BfmeOverridable *overrideObject = *(const BfmeOverridable **)(
			(const unsigned char *)thingTemplate + 4);
		if (overrideObject != 0)
		{
			union
			{
				void (*raw)(void);
				const BfmeOverridable *(BfmeOverridable::*member)() const;
			} call;
			call.raw = j_000022bb;
			return (overrideObject->*call.member)();
		}
	}
	return thingTemplate;
}

static __forceinline void getRadiusAndCenter(Pathfinder *self,
	const Object *object, Int *radius, Bool *center)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)(const Object *, Int *, Bool *);
	} call;
	call.raw = j_000461ff;
	(self->*call.member)(object, radius, center);
}

static __forceinline Bool worldToCell(Pathfinder *self, const Coord3D *world,
	ICoord2D *cell)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(const Coord3D *, ICoord2D *);
	} call;
	call.raw = j_000171e8;
	return (self->*call.member)(world, cell);
}

static __forceinline Int layerForDestination(TerrainLogic *terrain,
	Object *object, const Coord3D *position)
{
	union
	{
		void (*raw)(void);
		Int (TerrainLogic::*member)(Object *, const Coord3D *);
	} call;
	call.raw = j_0001c675;
	return (terrain->*call.member)(object, position);
}

static __forceinline PathfindCell *getCell(Pathfinder *self, Int layer,
	Int x, Int y)
{
	union
	{
		void (*raw)(void);
		PathfindCell *(Pathfinder::*member)(Int, Int, Int);
	} call;
	call.raw = j_00020671;
	return (self->*call.member)(layer, x, y);
}

static __forceinline PathfindCell *getClippedCell(Pathfinder *self, Int layer,
	const Coord3D *position)
{
	union
	{
		void (*raw)(void);
		PathfindCell *(Pathfinder::*member)(Int, const Coord3D *);
	} call;
	call.raw = j_00047384;
	return (self->*call.member)(layer, position);
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

static __forceinline Bool stepCell(Pathfinder *self, void *state,
	PathfindCell *cell)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(void *, PathfindCell *);
	} call;
	call.raw = j_0002b9e0;
	return (self->*call.member)(state, cell);
}

static __forceinline PathfindCellInfo *acquireInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *position)
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

static __forceinline void allocateInfos(void)
{
	union
	{
		void (*raw)(void);
		void (*function)(void);
	} call;
	call.raw = j_0003d1a9;
	call.function();
}

static __forceinline Bool startPathfind(PathfindCell *cell,
	PathfindCell *goal)
{
	union
	{
		void (*raw)(void);
		Bool (PathfindCell::*member)(PathfindCell *);
	} call;
	call.raw = j_0003e9f5;
	return (cell->*call.member)(goal);
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

static __forceinline PathfindCell *takeFirstLive(Pathfinder *self)
{
	union
	{
		void (*raw)(void);
		PathfindCell *(Gen_003D6490::*member)();
	} call;
	call.raw = j_0003d3ed;
	return (((Gen_003D6490 *)self)->*call.member)();
}

static __forceinline void moveInfo(PathfindCell *cell,
	PathfindCellInfo **head)
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

static __forceinline UnsignedInt costSoFar(PathfindCell *cell,
	PathfindCell *parent)
{
	union
	{
		void (*raw)(void);
		UnsignedInt (PathfindCell::*member)(PathfindCell *);
	} call;
	call.raw = j_000169c3;
	return (cell->*call.member)(parent);
}

static __forceinline Int pathPenalty(Pathfinder *self, PathfindCell *cell,
	PathfindCell *parent)
{
	union
	{
		void (*raw)(void);
		Int (Gen_003DB900::*member)(PathfindCell *, PathfindCell *);
	} call;
	call.raw = j_0003a828;
	return (((Gen_003DB900 *)self)->*call.member)(cell, parent);
}

static __forceinline void setParentCell(PathfindCell *cell,
	PathfindCell *parent)
{
	union
	{
		void (*raw)(void);
		void (PathfindCell::*member)(PathfindCell *);
	} call;
	call.raw = j_00040313;
	(cell->*call.member)(parent);
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

static __forceinline void prependCells(Pathfinder *self, Path *path,
	const Coord3D *from, PathfindCell *goal, Bool center)
{
	union
	{
		void (*raw)(void);
		void (Pathfinder::*member)(Path *, const Coord3D *, PathfindCell *, Bool);
	} call;
	call.raw = j_0000af24;
	(self->*call.member)(path, from, goal, center);
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

// ?getAircraftPath@Pathfinder@@QAEPAVPath@@PBVObject@@PBUCoord3D@@@Z
Path *Pathfinder::getAircraftPath(const Object *object, const Coord3D *to)
{
	m_ignoreObstacleID = 0;

	union
	{
		Int radius;
		const Coord3D *from;
	} radiusFrom;
	Bool center;
	getRadiusAndCenter(this, object, &radiusFrom.radius, &center);

	radiusFrom.from = object->getPosition();
	union
	{
		Coord3D start;
		ICoord2D candidatePos;
	} startCandidate;
	startCandidate.start = *radiusFrom.from;
	union
	{
		Coord3D destination;
		Bool neighborFlags[8];
	} destinationFlags;
	destinationFlags.destination = *to;
	if (!center)
	{
		startCandidate.start.x += *(const float *)0x01075344;
		startCandidate.start.y += *(const float *)0x01075344;
		destinationFlags.destination.x += *(const float *)0x01075344;
		destinationFlags.destination.y += *(const float *)0x01075344;
	}

	ICoord2D startCell;
	ICoord2D goalCellNdx;
	worldToCell(this, &startCandidate.start, &startCell);
	worldToCell(this, &destinationFlags.destination, &goalCellNdx);
	if (startCell.x == goalCellNdx.x && startCell.y == goalCellNdx.y)
		return 0;

	const BfmeOverridable *thingTemplate = object->getTemplate();
	Int maxLayer = *(const Int *)((const unsigned char *)
		finalTemplate(thingTemplate) + 0x444);
	Bool templateFlag = *(const unsigned char *)((const unsigned char *)
		finalTemplate(thingTemplate) + 0x4cc) != 0;
	BfmeAIUpdate *ai = object->getAI();
	Int surfaces = ai->m_acceptableSurfaces;
	Bool computer = isComputerControlled(object);

	struct BfmeMovementPositionInfo
	{
		Int m_surfaces;
		Bool m_field04;
		Bool m_allowAircraftGoal;
		char m_pad06[2];
		Int m_maxLayer;
	} movement;
	movement.m_surfaces = surfaces;
	movement.m_field04 = !templateFlag;
	movement.m_allowAircraftGoal = computer;
	Int destinationLayer = layerForDestination(TheTerrainLogic,
		(Object *)object, to);
	movement.m_maxLayer = maxLayer - 1;
	if (!stepCell(this, &movement, getCell(this, destinationLayer,
		goalCellNdx.x, goalCellNdx.y)))
		return 0;

	ICoord2D checkedGoal;
	if (worldToCell(this, &destinationFlags.destination, &checkedGoal))
		return 0;
	PathfindCell *goal = getCell(this, destinationLayer,
		checkedGoal.x, checkedGoal.y);
	if (goal == 0)
		return 0;

	PathfindCell *parent = getClippedCell(this,
		objectLayer(object), radiusFrom.from);
	if (parent == 0)
		return 0;

	if (goal->m_info == 0)
	{
		if (g_bfmePathfindFreeList == 0)
			allocateInfos();
		goal->m_info = acquireInfo(&g_bfmePathfindFreeList, goal,
			&goalCellNdx);
	}
	else
	{
		goal->m_info->m_prevOpen = 0;
	}

	if (parent->m_info == 0)
	{
		if (g_bfmePathfindFreeList == 0)
			allocateInfos();
		parent->m_info = acquireInfo(&g_bfmePathfindFreeList, parent,
			&startCell);
	}
	else
	{
		parent->m_info->m_prevOpen = 0;
	}

	startPathfind(parent, goal);
	copyIndexed(this, parent);
	Int examined = 0;
	PathfindCell *current = takeFirstLive(this);
	if (current == 0)
	{
		resetLists(this);
		releaseInfo(goal);
		return 0;
	}

	static const Int adjacent[5] = { 0, 1, 2, 3, 0 };
	for (;;)
	{
		if (current == goal)
			break;

		moveInfo(current, &m_openHead);
		if (examined > 0xc8)
		{
			resetLists(this);
			releaseInfo(goal);
			return 0;
		}

		expandLayers(this, current, (Object *)object);
		Int direction;
		for (direction = 0; direction < 8; ++direction)
		{
			destinationFlags.neighborFlags[direction] = false;
			PathfindCellInfo *currentInfo = current->m_info;
			startCandidate.candidatePos.x = currentInfo->m_pos.x +
				g_bfmeDirectionX[direction];
			startCandidate.candidatePos.y = currentInfo->m_pos.y +
				g_bfmeDirectionY[direction];
			PathfindCell *candidate = getCell(this,
				(Int)((current->m_bits >> 6) & 0x3f),
				startCandidate.candidatePos.x,
				startCandidate.candidatePos.y);
			if (candidate == 0)
				continue;

			PathfindCellInfo *candidateInfo = candidate->m_info;
			if (candidateInfo != 0 &&
				(((candidateInfo->m_flags >> 4) & 1) != 0 ||
				 ((candidateInfo->m_flags >> 3) & 1) != 0))
				continue;

			UnsignedInt candidateBits = candidate->m_bits;
			UnsignedInt currentBits = current->m_bits;
			Int candidateZone = (Int)((candidateBits >> 6) & 0x3f);
			Int currentZone = (Int)((currentBits >> 6) & 0x3f);
			Int currentConnect = (Int)((currentBits >> 12) & 0x3f);
			Int candidateConnect = (Int)((candidateBits >> 12) & 0x3f);
			if (candidateZone == currentZone ||
				candidateZone == currentConnect ||
				candidateConnect == currentZone ||
				(currentConnect != 0x10) ||
				(candidateConnect != currentConnect))
				continue;

			if (direction >= 4 &&
				!destinationFlags.neighborFlags[adjacent[direction - 4]] &&
				!destinationFlags.neighborFlags[adjacent[direction - 3]])
				continue;

			if (!stepCell(this, &movement, candidate))
			{
				if (candidateInfo == 0)
				{
					if (g_bfmePathfindFreeList == 0)
						allocateInfos();
					candidate->m_info = acquireInfo(&g_bfmePathfindFreeList,
						candidate, &startCandidate.candidatePos);
				}
				else
				{
					candidateInfo->m_prevOpen = 0;
				}
				moveInfo(candidate, &m_openHead);
				continue;
			}

			destinationFlags.neighborFlags[direction] = true;
			if (candidateInfo == 0)
			{
				if (g_bfmePathfindFreeList == 0)
					allocateInfos();
				candidateInfo = acquireInfo(&g_bfmePathfindFreeList,
					candidate, &startCandidate.candidatePos);
				candidate->m_info = candidateInfo;
			}
			++examined;

			UnsignedInt candidateCost = costSoFar(candidate, current);
			Int dx = currentInfo->m_pos.x - candidateInfo->m_pos.x;
			if (dx < 0)
				dx = -dx;
			Int dy = currentInfo->m_pos.y - candidateInfo->m_pos.y;
			if (dy < 0)
				dy = -dy;
			if (((candidate->m_bits >> 18) & 1) != 0 && dx + dy > 3)
				candidateCost += 10;

			candidateInfo->m_flags &= ~1u;
			Int heuristic = pathPenalty(this, candidate, current);
			if ((candidate->m_bits & 7) == 4)
				candidateCost += 0x3e8;
			candidateInfo->m_costSoFar = (UnsignedShort)candidateCost;
			setParentCell(candidate, current);
			candidateInfo->m_totalCost = (UnsignedShort)(candidateInfo->m_costSoFar + heuristic);
			copyIndexed(this, candidate);
		}

		current = takeFirstLive(this);
		if (current == 0)
		{
			resetLists(this);
			releaseInfo(goal);
			return 0;
		}
	}

	Path *path = new Path;
	if (path == 0)
		return 0;
	prependCells(this, path, radiusFrom.from, goal, center);
	path->m_complete = 1;
	releaseInfo(goal);
	resetLists(this);
	return path;
}

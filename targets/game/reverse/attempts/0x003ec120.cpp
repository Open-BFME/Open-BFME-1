// ?patchPath@Pathfinder@@EAEPAVPath@@PBVObject@@ABVLocomotorSet@@PAV2@_N@Z
// partial score=0.5692 date=2026-11-02
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// BANKED 0x003EC120 (1553 B) Pathfinder::patchPath, s538 a1: 1553 B = retail,
// shape 0.979, 669 diffs, all frame-slot offsets: frame 0x80 vs retail 0x78.
// Handoff: targets/game/reverse/attempt_support/0x003ec120-patchpath-frame-slots.md
// Declarations copied from PathfinderFindSafePathBfme.cpp (its sibling slot 4).
// Retail 0x003EC8C0 (750 B): Pathfinder::findSafePath.  Identity: slot 4 of the
// Pathfinder PathfindServicesInterface vtable, the slot Zero Hour gives
// findSafePath.  The body is the Zero Hour search on the BFME open/closed-list
// helpers that the matched checkPathCost (0x003E11E0, PathfinderStepD4F90.cpp)
// already uses; the helper names are that file's address-derived names.

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Coord3D &operator=(const Coord3D &other) { x = other.x; y = other.y; z = other.z; return *this; }
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

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class PathfindCell;
class Path;

struct PathfindCellInfo
{
	static void allocateCellInfos();

	ICoord2D m_pos;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	unsigned char m_pad10[0x24 - 0x10];
	UnsignedInt m_bits0 : 3;
	UnsignedInt m_open : 1;
	UnsignedInt m_closed : 1;
	PathfindCell *m_cell;
};
extern void *g_rva012F1094;
PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

class PathfindCell
{
public:
	Bool startPathfind(PathfindCell *goalCell);
	void rva003F6F10();
	void rva003F6C30(PathfindCellInfo **head);

	__forceinline void allocateInfo(const ICoord2D *pos)
	{
		if (m_info == 0)
		{
			if (g_rva012F1094 == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), this, pos);
		}
		else
		{
			m_info->m_prevOpen = 0;
		}
	}
	Bool getOpen() const { return m_info ? m_info->m_open != 0 : false; }
	Bool getClosed() const { return m_info ? m_info->m_closed != 0 : false; }
	UnsignedShort getXIndex() const { return (UnsignedShort)m_info->m_pos.x; }
	UnsignedShort getYIndex() const { return (UnsignedShort)m_info->m_pos.y; }
	PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)((m_bits >> 6) & 0x3f); }

	PathfindCellInfo *m_info;
	Int m_zone;
	Int m_unused08;
	UnsignedInt m_bits;
};

extern "C" __declspec(dllimport) double __cdecl floor( double );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

extern const float g_bfmeDirectionWeight1285;
extern const float g_Rva010977E0;
extern const float g_rva01075350;
extern float g_Rva01095F98;

// Template view from PathfindGetRadiusAndCenterE30.cpp.
class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	BfmeOverridable *getFinalOverride( void )
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	unsigned char m_pad08[0xc8 - 0x08];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
};

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }

	unsigned char m_pad[0x2c];
	PlayerType m_playerType;
};

class AIUpdateInterface;

class Object
{
public:
	Player *getControllingPlayer() const;
	Int getLayer() const;
	const Coord3D *getPosition() const { return &m_cachedPos; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	BfmeOverridable *getTemplate( void ) const { return m_template; }

	Int m_unknown00;
	BfmeOverridable *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_cachedPos;
	unsigned char m_pad44[0xbc - 0x44];
	Real m_boundingCircleRadius;
	unsigned char m_padC0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
};

class LocomotorSet
{
public:
	Int getValidSurfaces() const { return m_validLocomotorSurfaces; }

	unsigned char m_pad[0x10];
	Int m_validLocomotorSurfaces;
};

// Retail 0x00403140, reached through ILT 0x00010FA5 on this+0xC9C.
class BfmeGridAL
{
public:
	void bfmeFillAL();
};

// Open-list view of the Pathfinder at 0x003D6440 (Bfme5EightyThree.cpp).
class Gen_003D6440
{
public:
	__declspec(noinline) int bfmeFirstLive(void);
private:
	int m_bfmeGap[13];							// +0x000
	PathfindCellInfo *m_bfmeSlots[512];			// +0x034
	int m_bfmeCursor;							// +0x834
};

class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID();
};

class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer)
	{
		m_next = 0;
		m_prev = 0;
		m_nextOpti = 0;
		m_pos = *position;
		m_layer = layer;
		m_canOptimize = false;
		m_cost = 0x7FFFFFFF;
	}
	const Coord3D *getPosition() const { return &m_pos; }
	PathfindLayerEnum getLayer() const { return m_layer; }
	PathNode *getPrevious() const { return m_prev; }

	PathNode *m_next;
	PathNode *m_prev;
	PathNode *m_nextOpti;
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_cost;
};

class Path
{
public:
	Path();
	void optimize(const Object *obj, Int acceptableSurfaces, Bool blocked);
	PathNode *getFirstNode() const { return m_path; }
	PathNode *getLastNode() const { return m_pathTail; }
	void prependNode(const Coord3D *pos, PathfindLayerEnum layer)
	{
		PathNode *node = new PathNode(pos, layer);
		PathNode *head = m_path;
		node->m_nextOpti = head;
		node->m_next = head;
		if (head)
			head->m_prev = node;
		m_path = node;
		if (m_pathTail == 0)
			m_pathTail = node;
		m_isOptimized = false;
	}

	Int m_vtbl;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	unsigned char m_pad0d[0x24 - 0x0d];
};

struct TCheckMovementInfo
{
	TCheckMovementInfo()
		: allyFixedCount(0), enemyFixed(false), allyMoving(false),
		  obstacleID(-1), m_28(0), m_2c(false), m_2d(false), m_2e(false), m_30(0) {}

	ICoord2D cell;
	PathfindLayerEnum layer;
	Int radius;
	Bool centerInCell;
	Bool considerTransient;
	Int acceptableSurfaces;
	Int ignoredObstacleID;
	Int allyFixedCount;
	Bool enemyFixed;
	Bool allyMoving;
	Int obstacleID;
	Int m_28;
	Bool m_2c;
	Bool m_2d;
	Bool m_2e;
	Int m_30;
};

class Gen_003F69E0
{
public:
	void bfmeDetach(void);
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	void rva003D6400(PathfindCell *cell);
	PathfindCell *rva003D6490();
	void rva003DAE40(PathfindCell *cell, Object *obj);
	void rva003D5FC0();
	Bool bfmeStepE05B0_003E05B0(Object *obj, ICoord2D *info);
	void prependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);
	Int rva003E6EE0(PathfindCell *parentCell, PathfindCell *goalCell,
		const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell,
		Int radius, const ICoord2D &startCellNdx, const Object *obj,
		Int attackDistance);
	Bool rva003DF580(Object *obj, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int radius, Bool centerInCell,
		void **blocker, Int flags);
	Path *buildActualPath(const Object *obj, Int surfaces,
		const Coord3D *fromPos, PathfindCell *goalCell, Bool center,
		Bool blocked);

protected:
	__declspec(noinline) void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &pos, PathfindLayerEnum layer);

	__forceinline PathfindCell *getClippedCell(PathfindLayerEnum layer,
		const Coord3D *pos)
	{
		ICoord2D cell;
		worldToCell(pos, &cell);
		return getCell(layer, cell.x, cell.y);
	}

	__forceinline Bool checkDestination(const Object *obj, Int cellX,
		Int cellY, PathfindLayerEnum layer, Int radius, Bool centerInCell)
	{
		void *blocker;
		if (!rva003DF580(const_cast<Object *>(obj), cellX, cellY, layer,
				radius, centerInCell, &blocker, 0))
			return false;
		return blocker == 0;
	}

	__forceinline PathfindCell *getGroundCell(Int x, Int y)
	{
		if (x >= m_extentLoX && x <= m_extentHiX
			&& y >= m_extentLoY && y <= m_extentHiY)
			return &m_map[x][y];
		return 0;
	}

	__forceinline PathfindCell *getGroundCell(const Coord3D *pos)
	{
		ICoord2D cell;
		Bool overflow = worldToCell(pos, &cell);
		if (overflow)
			return 0;
		return getGroundCell(cell.x, cell.y);
	}

	__forceinline PathfindCell *takeFirstOpen()
	{
		while (m_bfme0834 < 512)
		{
			if (m_bfme0034[m_bfme0834] != 0)
			{
				PathfindCell *cell = m_bfme0034[m_bfme0834]->m_cell;
				((Gen_003F69E0 *)cell)->bfmeDetach();
				return cell;
			}
			++m_bfme0834;
		}
		return 0;
	}

private:
	virtual Path *patchPath(const Object *obj, const LocomotorSet &locomotorSet,
		Path *originalPath, Bool blocked);
	virtual Path *findSafePath(const Object *obj,
		const LocomotorSet &locomotorSet, const Coord3D *from,
		const Coord3D *repulsorPos1, const Coord3D *repulsorPos2,
		Real repulsorRadius);

	// Retail reads byte +8 here, but BFME layout witnesses disagree on its member identity.
	unsigned char m_opaque04[0x10 - 4];
	PathfindCell **m_map;				// +0x10
	Int m_extentLoX;					// +0x14
	Int m_extentLoY;					// +0x18
	Int m_extentHiX;					// +0x1C
	Int m_extentHiY;					// +0x20
	unsigned char m_pad24[0x34 - 0x24];
	PathfindCellInfo *m_bfme0034[512];	// +0x34: open-list buckets (Gen_003D6440 view)
	Int m_bfme0834;						// +0x834: first bucket cursor
	PathfindCellInfo *m_closedList;		// +0x838
	Bool m_isTunneling;					// +0x83C
	unsigned char m_pad83d[0xc9c - 0x83d];
	BfmeGridAL m_bfme0C9C;				// +0xC9C
	unsigned char m_pad0c9d[0x2470c - 0xc9d];
	_STL::vector<Coord3D> m_bfme2470C;	// +0x2470C
};

// Retail 0x003DEE30 (ILT 0x000461FF), the body PathfindGetRadiusAndCenterE30.cpp
// matches.  findSafePath needs it visible: only then does VC7.1 treat the
// reference arguments as non-escaping, cache centerInCell in EBX for the search
// loop and reuse its frame slot, as retail does.
inline __declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = object->getTemplate();
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = object->getTemplate();
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = object->m_boundingCircleRadius * 2.0f;
	if (diameter > g_bfmeDirectionWeight1285 && diameter < g_Rva010977E0) {
		diameter = 20.0f;
	}

	if ((object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level > g_rva01075350) {
		diameter = (object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_Rva01095F98 );
	centerInCell = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		centerInCell = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		centerInCell = true;
	}
}

// Retail 0x003D6440 (ILT 0x00028844): the first live open-list bucket entry of
// the Pathfinder, under its ledger name and view (Bfme5EightyThree.cpp).  It is
// defined here so the caller sees its body: only then does VC7.1 keep the
// distance on the x87 stack across the call, as retail does.
int Gen_003D6440::bfmeFirstLive(void)
{
	while (m_bfmeCursor < 512)
	{
		if (m_bfmeSlots[m_bfmeCursor] != 0)
			return (int)m_bfmeSlots[m_bfmeCursor]->m_cell;
		++m_bfmeCursor;
	}
	return 0;
}


// ?patchPath@Pathfinder@@EAEPAVPath@@PBVObject@@ABVLocomotorSet@@PAV2@_N@Z
Path *Pathfinder::patchPath(const Object *obj, const LocomotorSet &locomotorSet,
	Path *originalPath, Bool blocked)
{
	if (originalPath == 0)
		return 0;
	Bool centerInCell;
	Int radius;
	getRadiusAndCenter(obj, radius, centerInCell);
	Bool isHuman = true;
	if (obj->getControllingPlayer() &&
		obj->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
		isHuman = false;

	m_bfme2470C.clear();
	m_bfme0C9C.bfmeFillAL();

	Int cellCount = 0;
	Coord3D currentPosition;
	currentPosition = *obj->getPosition();
	ICoord2D startCellNdx;
	Coord3D goalPos;
	goalPos = *obj->getPosition();
	if (!centerInCell)
	{
		goalPos.x += 10.0f * 0.5f;
		goalPos.x += 10.0f * 0.5f;
	}
	worldToCell(&goalPos, &startCellNdx);
	ICoord2D cell;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	worldToCell(&currentPosition, &cell);
	PathfindCell *parentCell = getCell(layer, cell.x, cell.y);
	if (parentCell == 0)
		return 0;
	if (!obj->getAIUpdateInterface())
		return 0;
	m_isTunneling = false;
	parentCell->allocateInfo(&startCellNdx);
	parentCell->startPathfind(0);
	rva003D6400(parentCell);

	PathNode *startNode;
	goalPos = *originalPath->getLastNode()->getPosition();
	Real dx = goalPos.x - currentPosition.x;
	Real dy = goalPos.y - currentPosition.y;
	Real goalDeltaSqr = dx * dx + dy * dy;
	ICoord2D cellCoord;
	for (startNode = originalPath->getLastNode(); startNode != originalPath->getFirstNode();
		startNode = startNode->getPrevious())
	{
		worldToCell(startNode->getPosition(), &cellCoord);
		TCheckMovementInfo info;
		info.cell = cellCoord;
		info.layer = startNode->getLayer();
		info.centerInCell = centerInCell;
		info.radius = radius;
		info.considerTransient = blocked;
		Int cdx = cellCoord.x - startCellNdx.x;
		Int cdy = cellCoord.y - startCellNdx.y;
		if (cdx < -2 || cdx > 2)
			info.considerTransient = false;
		if (cdy < -2 || cdy > 2)
			info.considerTransient = false;
		info.acceptableSurfaces = 3;
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		info.ignoredObstacleID = ai ? ai->getIgnoredObstacleID() : 0;
		if (!bfmeStepE05B0_003E05B0(const_cast<Object *>(obj), &info.cell))
			break;
		Real nx = startNode->getPosition()->x - currentPosition.x;
		Real ny = startNode->getPosition()->y - currentPosition.y;
		Real curSqr = nx * nx + ny * ny;
		if (curSqr < goalDeltaSqr)
		{
			goalPos = *startNode->getPosition();
			goalDeltaSqr = curSqr;
		}
	}
	if (startNode == originalPath->getLastNode())
	{
		rva003D5FC0();
		return 0;
	}

	PathfindCell *candidateGoal;
	Bool overflow = worldToCell(&goalPos, &cell);
	if (overflow)
		candidateGoal = 0;
	else
		candidateGoal = getGroundCell(cell.x, cell.y);
	worldToCell(&goalPos, &cellCoord);
	candidateGoal->allocateInfo(&cellCoord);

	while ((parentCell = takeFirstOpen()) != 0)
	{
		adjustCoordToCell(parentCell->getXIndex(), parentCell->getYIndex(),
			centerInCell, currentPosition, parentCell->getLayer());
		PathNode *matchNode;
		Bool found = false;
		for (matchNode = originalPath->getLastNode(); matchNode != startNode;
			matchNode = matchNode->getPrevious())
		{
			if (currentPosition.x == matchNode->getPosition()->x &&
				currentPosition.y == matchNode->getPosition()->y)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			m_isTunneling = false;
			Path *path = new Path;
			for (PathNode *node = originalPath->getLastNode(); node != matchNode;
				node = node->getPrevious())
				path->prependNode(node->getPosition(), node->getLayer());
			prependCells(path, obj->getPosition(), parentCell, centerInCell);
			path->optimize(obj, locomotorSet.getValidSurfaces(), blocked);
			parentCell->rva003F6F10();
			rva003D5FC0();
			candidateGoal->rva003F6F10();
			return path;
		}
		parentCell->rva003F6C30(&m_closedList);
		if (cellCount < 2000)
		{
			rva003DAE40(parentCell, const_cast<Object *>(obj));
			cellCount += rva003E6EE0(parentCell, 0, locomotorSet, isHuman,
				centerInCell, radius, startCellNdx, obj, 0);
		}
	}

	m_isTunneling = false;
	if (!candidateGoal->getOpen() && !candidateGoal->getClosed())
		candidateGoal->rva003F6F10();
	rva003D5FC0();
	return 0;
}

// cl: /DNDEBUG /MD
// stlport
//
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
	unsigned char m_pad10[0x28 - 0x10];
	PathfindCell *m_cell;
};
extern PathfindCellInfo *g_bfmePathfindFreeList;
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
			if (g_bfmePathfindFreeList == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, pos);
		}
		else
		{
			m_info->m_prevOpen = 0;
		}
	}
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

extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const Real g_pathfindLevelLimit;
extern const Real g_pathfindCellCenterBias;

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

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	void rva003D6400(PathfindCell *cell);
	PathfindCell *rva003D6490();
	void rva003DAE40(PathfindCell *cell, Object *obj);
	void rva003D5FC0();
	Int rva003E6EE0(PathfindCell *parentCell, PathfindCell *goalCell,
		const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell,
		Int radius, const ICoord2D &startCellNdx, const Object *obj,
		Int attackDistance);
	Bool bfmeInnerE6E90(Object *obj, Int cellX, Int cellY,
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
		if (!bfmeInnerE6E90(const_cast<Object *>(obj), cellX, cellY, layer,
				radius, centerInCell, &blocker, 0))
			return false;
		return blocker == 0;
	}

private:
	virtual Path *findSafePath(const Object *obj,
		const LocomotorSet &locomotorSet, const Coord3D *from,
		const Coord3D *repulsorPos1, const Coord3D *repulsorPos2,
		Real repulsorRadius);

	// Retail reads byte +8 here, but BFME layout witnesses disagree on its member identity.
	unsigned char m_opaque04[0x34 - 4];
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
void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
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
	if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
		diameter = 20.0f;
	}

	if ((object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level > g_pathfindLevelLimit) {
		diameter = (object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_pathfindCellCenterBias );
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

// ?findSafePath@Pathfinder@@EAEPAVPath@@PBVObject@@ABVLocomotorSet@@PBUCoord3D@@22M@Z
Path *Pathfinder::findSafePath(const Object *obj,
	const LocomotorSet &locomotorSet, const Coord3D *from,
	const Coord3D *repulsorPos1, const Coord3D *repulsorPos2,
	Real repulsorRadius)
{
	if (((const unsigned char *)this)[8] == 0)
		return 0;

	const Int MAX_CELLS = 2000;

	Bool centerInCell;
	Int radius;
	getRadiusAndCenter(obj, radius, centerInCell);
	Real repulsorDistSqr = repulsorRadius * repulsorRadius;
	Int cellCount = 0;
	Bool isHuman = true;
	if (obj->getControllingPlayer() &&
		obj->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
		isHuman = false;

	m_bfme2470C.clear();
	m_bfme0C9C.bfmeFillAL();

	ICoord2D startCellNdx;
	worldToCell(obj->getPosition(), &startCellNdx);
	PathfindCell *parentCell = getClippedCell(
		(PathfindLayerEnum)obj->getLayer(), obj->getPosition());
	if (parentCell == 0)
		return 0;
	if (!obj->getAIUpdateInterface())
		return 0;
	parentCell->allocateInfo(&startCellNdx);
	parentCell->startPathfind(0);
	rva003D6400(parentCell);

	Real farthestDistanceSqr = 0;

	while ((parentCell = rva003D6490()) != 0)
	{
		Coord3D cellCenter;
		adjustCoordToCell(parentCell->getXIndex(), parentCell->getYIndex(),
			centerInCell, cellCenter, parentCell->getLayer());

		Real dx = cellCenter.x - repulsorPos1->x;
		Real dy = cellCenter.y - repulsorPos1->y;
		Bool ok = false;
		Real distSqr = dx * dx + dy * dy;
		dx = cellCenter.x - repulsorPos2->x;
		dy = cellCenter.y - repulsorPos2->y;
		Real distSqr2 = dx * dx + dy * dy;
		if (distSqr2 < distSqr)
			distSqr = distSqr2;
		if (distSqr > repulsorDistSqr)
			ok = true;
		if (reinterpret_cast<Gen_003D6440 *>(this)->bfmeFirstLive() == 0 && cellCount > 0)
			ok = true;
		if (distSqr > farthestDistanceSqr)
		{
			farthestDistanceSqr = distSqr;
			if (cellCount > MAX_CELLS)
				ok = true;
		}
		if (ok && checkDestination(obj, parentCell->getXIndex(),
				parentCell->getYIndex(), parentCell->getLayer(), radius,
				centerInCell))
		{
			Path *path = buildActualPath(obj, locomotorSet.getValidSurfaces(),
				obj->getPosition(), parentCell, centerInCell, false);
			parentCell->rva003F6F10();
			rva003D5FC0();
			return path;
		}

		parentCell->rva003F6C30(&m_closedList);
		rva003DAE40(parentCell, const_cast<Object *>(obj));
		cellCount += rva003E6EE0(parentCell, 0, locomotorSet, isHuman,
			centerInCell, radius, startCellNdx, obj, 0);
	}

	m_isTunneling = false;
	rva003D5FC0();
	return 0;
}

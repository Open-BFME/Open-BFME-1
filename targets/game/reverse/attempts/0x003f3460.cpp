// ?findClosestPath@Pathfinder@@EAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@PAU5@_NM4@Z
// partial score=0.891 date=2026-09-27
// cl: /DNDEBUG /MD
// stlport
//
// Retail 0x003F3460: Pathfinder::findClosestPath, the Zero Hour twin at
// AIPathfind.cpp (GeneralsMD) -- "find a short, valid path between the FROM
// location and a location NEAR the to location".  Identity: the named lift
// row this body replaces, the Zero Hour call sequence (getRadiusAndCenter,
// clip, getLayerForDestination, the ignore-obstacle airfield test,
// findClosestHierarchicalPath, startPathfind, buildActualPath) and the
// seven-argument __thiscall frame (ret 0x1c).
//
// BFME reworked the body:
//  - before anything else the destination is pulled back toward `from` in up
//    to five 30-unit steps until slowDoesPathExist accepts it;
//  - cells are found with worldToCell + getCell rather than getClippedCell;
//  - the start-cell validity test is the BFME movement-info check
//    (0x003D4F90) built from the template's +0x444/+0x4cc fields and the
//    computer-controlled flag, and TCheckMovementInfo grew trailing fields;
//  - the open list is a 512-entry bucket queue (+0x34, cursor at +0x834)
//    keyed by the info's total cost >> 7;
//  - the closest-cell score adds a per-waypoint penalty (the 12-byte vector
//    at +0x2470c, cleared on entry) and the screen-distance skip is a
//    threshold that grows with the best screen distance seen.
//
// Helper names below that carry an address token or an opaque class are the
// ledger's own names for those bodies (their thunks are what retail calls).
// Layouts are TU-local shims, like the other Pathfind*.cpp bodies.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <math.h>
#include <stdlib.h>

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

const ObjectID INVALID_ID = 0;

enum PathfindLayerEnum { LAYER_INVALID = 0 };
enum KindOfType { KINDOF_FS_AIRFIELD = 0x23 };
enum PlayerType { PLAYER_HUMAN, PLAYER_COMPUTER };

struct ICoord2D { Int x, y; };

struct Coord3D
{
	Real x, y, z;
	Real Normalize( void );
 void set(const Coord3D *a){x=a->x;y=a->y;z=a->z;}
};

class Player
{
public:
	PlayerType getPlayerType( void ) const { return m_playerType; }

private:
	unsigned char m_prefix[0x2c];
	PlayerType m_playerType;				// +0x2c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;

	void *m_vtable;
	Overridable *m_nextOverride;			// +0x04
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x444 - 0x08];
	Int m_bfme444;							// +0x444
	unsigned char m_pad448[0x4cc - 0x448];
	Bool m_bfme4cc;							// +0x4cc
};

class AIUpdateInterface
{
public:
	Int getIgnoredObstacleID( void );
	Bool canPathThroughUnits( void ) const { return m_canPathThroughUnits; }

private:
	unsigned char m_prefix[0x328];
	Bool m_canPathThroughUnits;				// +0x328
};

class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer( void ) const;
	Int getLayer( void ) const;
	Bool bfmeIsComputerControlled( void ) const;
	const Coord3D *getPosition( void ) const { return &m_position; }
	AIUpdateInterface *getAIUpdateInterface( void ) const { return m_ai; }
	const ThingTemplate *getTemplate( void ) const
	{
		if (m_template && m_template->m_nextOverride)
			return (const ThingTemplate *)m_template->getFinalOverride();
		return m_template;
	}

private:
	void *m_vtable;
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position;						// +0x38
	unsigned char m_pad044[0x204 - 0x44];
	AIUpdateInterface *m_ai;				// +0x204
};

class LocomotorSet
{
public:
	Int getValidSurfaces( void ) const { return m_validLocomotorSurfaces; }

private:
	unsigned char m_prefix[0x10];
	Int m_validLocomotorSurfaces;			// +0x10
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
};
extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination( Object *obj, const Coord3D *pos );
};
extern TerrainLogic *TheTerrainLogic;

class Path
{
public:
	~Path();								// protected virtual in ZH; called directly
};

class PathfindCell;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	static void allocateCellInfos( void );

	UnsignedShort m_x;						// +0x00
	UnsignedShort m_pad02;
	UnsignedShort m_y;						// +0x04
	UnsignedShort m_pad06;
	unsigned char m_pad08[0x0c - 0x08];
	Int m_bfme0c;							// +0x0c
	UnsignedShort m_totalCost;				// +0x10
	UnsignedShort m_costSoFar;				// +0x12
	unsigned char m_pad14[0x20 - 0x14];
	ObjectID m_obstacleID;					// +0x20
	unsigned char m_pad24[0x28 - 0x24];
	PathfindCell *m_cell;					// +0x28
};

extern "C" PathfindCellInfo *g_bfmePathfindFreeList;
PathfindCellInfo *bfmeAcquirePathfindCellInfo( PathfindCellInfo **freeList,
	PathfindCell *cell, const ICoord2D *pos );

// Ledger names of the cell-list helpers (all __thiscall on the cell).
struct BfmeNodeNO;
class BfmeThingBRE { public: void bfmeGoBRE( void *bucket ); };
class BfmeThingNO { public: void bfmeMoveNO( BfmeNodeNO **list ); };
class Gen_003F69E0 { public: void bfmeDetach( void ); };
class Rva003F7380State { public: void finishReset( void ); };

class PathfindCell
{
public:
	Bool startPathfind( PathfindCell *goalCell );

	UnsignedShort getXIndex( void ) const { return m_info->m_x; }
	UnsignedShort getYIndex( void ) const { return m_info->m_y; }
	UnsignedInt getLayer( void ) const { return (m_packed >> 6) & 0x3f; }
	ObjectID getObstacleID( void ) const
	{
		if (m_info)
			return m_info->m_obstacleID;
		return INVALID_ID;
	}

	void allocateInfo( const ICoord2D &pos )
	{
		if (m_info == 0)
		{
			if (g_bfmePathfindFreeList == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo( &g_bfmePathfindFreeList, this, &pos );
		}
		else
		{
			m_info->m_bfme0c = 0;
		}
	}

	void putInBucket( void *bucket ) { ((BfmeThingBRE *)this)->bfmeGoBRE( bucket ); }
	void detachFromBucket( void ) { ((Gen_003F69E0 *)this)->bfmeDetach(); }
	void putOnClosedList( BfmeNodeNO **list ) { ((BfmeThingNO *)this)->bfmeMoveNO( list ); }
	void releaseInfo( void ) { ((Rva003F7380State *)this)->finishReset(); }

	PathfindCellInfo *m_info;				// +0x00
	unsigned char m_pad04[0x0c - 0x04];
	UnsignedInt m_packed;					// +0x0c
};

// TCheckMovementInfo as BFME extended it: the constructor clears the fields
// Zero Hour left to the callee.
struct TCheckMovementInfo
{
	ICoord2D cell;							// +0x00
	PathfindLayerEnum layer;				// +0x08
	Int radius;								// +0x0c
	Bool centerInCell;						// +0x10
	Bool considerTransient;					// +0x11
	Int bfme14;								// +0x14
	Int ignoredObstacle;					// +0x18
	Int bfme1c;								// +0x1c
	Bool bfme20;							// +0x20
	Bool bfme21;							// +0x21
	Int bfme24;								// +0x24
	Int bfme28;								// +0x28
	Bool bfme2c;							// +0x2c
	Bool bfme2d;							// +0x2d
	Bool bfme2e;							// +0x2e
	Int bfme30;								// +0x30

	TCheckMovementInfo() : bfme1c(0), bfme20(false), bfme21(false), bfme24(-1), bfme28(0),
		bfme2c(false), bfme2d(false), bfme2e(false), bfme30(0) {}
};

// Argument of the BFME movement check at 0x003D4F90.
struct BfmeMoveCheckInfo
{
	Int surfaces;							// +0x00
	Bool notFlag4cc;						// +0x04
	Bool isComputer;						// +0x05
	Int limit444;							// +0x08
};

class BfmeGridAL
{
public:
	void bfmeClearAL( void );
	void bfmeFillAL( void );
};

// A 12-byte element with a user assignment, so vector::clear() copies element
// by element through the out-of-line STLport __copy retail calls.
struct Rva003F3460Waypoint
{
	Int a, b, c;
	Rva003F3460Waypoint &operator=( const Rva003F3460Waypoint &o ) { a = o.a; b = o.b; c = o.c; return *this; }
};

class PathfindCellInfoPool { public: void reset( void ); };

class Pathfinder
{
private:
	virtual Path *findClosestPath( Object *obj, const LocomotorSet& locomotorSet, const Coord3D *from,
		Coord3D *rawTo, Bool blocked, Real pathCostMultiplier, Bool moveAllies );

public:
	Bool worldToCell( const Coord3D *pos, ICoord2D *cell );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );
	PathfindCell *getClippedCell( PathfindLayerEnum layer, const Coord3D *pos );
	void clip( Coord3D *from, Coord3D *to );
	void getRadiusAndCenter( const Object *obj, Int &iRadius, Bool &center );
	Bool slowDoesPathExist( Object *obj, const Coord3D *from, const Coord3D *to, const void *movementProfile );
	Bool bfmeStepD4F90( void *info, PathfindCell *cell );
	Bool bfmeStepE05B0( Object *obj, ICoord2D *info );
	Path *rva003EEB90HierarchicalPath( Bool isHuman, Int surfaces, Object *obj, const Coord3D *from,
		const Coord3D *to, Bool blocked, Bool bfme );
	Int rva003db900( PathfindCell *cell, PathfindCell *goal );
	char bfmeInnerE6E90( void *obj, void *x, void *y, void *layer, void *radius, void *center,
		void **blocking, Int bfme );
	void adjustCoordToCell( Int cellX, Int cellY, Bool centerInCell, Coord3D &pos, PathfindLayerEnum layer );
	Bool rva003DF250CanReach( Object *obj, const Coord3D *pos );
	void rva003DAE40ChangeLayers( PathfindCell *cell, Object *obj );
	Int examineNeighboringCells( PathfindCell *parentCell, PathfindCell *goalCell,
		const LocomotorSet& locomotorSet, Bool isHumanPlayer, Bool centerInCell, Int radius,
		const ICoord2D &startCellNdx, const Object *obj, Int attackDistance );
	Path *buildActualPath( const Object *obj, Int surfaces, const Coord3D *fromPos,
		PathfindCell *goalCell, Bool center, Bool blocked );

	PathfindCell *getCell( PathfindLayerEnum layer, const Coord3D *pos )
	{
		ICoord2D cell;
		worldToCell( pos, &cell );
		return getCell( layer, cell.x, cell.y );
	}
	void cleanOpenAndClosedLists( void ) { ((PathfindCellInfoPool *)this)->reset(); }

private:
	unsigned char m_pad004[0x08 - 0x04];
	Bool m_isMapReady;						// +0x008
	unsigned char m_pad009[0x34 - 0x09];
	PathfindCellInfo *m_openBuckets[0x200];	// +0x034
	Int m_openBucket;						// +0x834
	BfmeNodeNO *m_closedList;				// +0x838
	Bool m_isTunneling;						// +0x83c
	unsigned char m_pad83d[0x844 - 0x83d];
	ObjectID m_ignoreObstacleID;			// +0x844
	unsigned char m_pad848[0xc9c - 0x848];
	BfmeGridAL m_zoneManager;				// +0xc9c
	unsigned char m_padc9d[0x2470c - 0xc9d];
	_STL::vector<Rva003F3460Waypoint> m_bfmeWaypoints;	// +0x2470c
};

Path *Pathfinder::findClosestPath( Object *obj, const LocomotorSet& locomotorSet, const Coord3D *from,
	Coord3D *rawTo, Bool blocked, Real pathCostMultiplier, Bool moveAllies )
{
	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
		isHuman = false;

	if (locomotorSet.getValidSurfaces() == 0)
		return 0;

	if (m_isMapReady == false)
		return 0;

	m_isTunneling = false;

	Bool canPathThroughUnits = false;
	if (obj->getAIUpdateInterface())
		canPathThroughUnits = obj->getAIUpdateInterface()->canPathThroughUnits();

	Bool centerInCell;
	Int radius;
	getRadiusAndCenter( obj, radius, centerInCell );

	Coord3D adjustTo; adjustTo.set(rawTo);
	if (!slowDoesPathExist( obj, from, &adjustTo, INVALID_ID ))
	{
		Coord3D delta;
		delta.x = adjustTo.x - from->x;
		delta.y = adjustTo.y - from->y;
		delta.z = 0;
		Int steps = -1 - (Int)(sqrtf( delta.x*delta.x + delta.y*delta.y ) * (-1.0f/30.0f));
		if (steps > 5)
			steps = 5;
		delta.Normalize();
		delta.x *= 30.0f;
		delta.y *= 30.0f;
		delta.z *= 30.0f;
		for (Int i = 0; i < steps; i++)
		{
			adjustTo.x -= delta.x;
			adjustTo.y -= delta.y;
			adjustTo.z -= delta.z;
			if (slowDoesPathExist( obj, from, &adjustTo, INVALID_ID ))
				break;
		}
	}

	Coord3D to = adjustTo;
	if (!centerInCell)
	{
		to.x = adjustTo.x + 5.0f;
		to.y = adjustTo.y + 5.0f;
	}

	Coord3D clipFrom = *from;
	clip( &clipFrom, &to );

	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination( 0, &to );
	ICoord2D startCellNdx;
	worldToCell( &to, &startCellNdx );
	PathfindCell *goalCell = getCell( destinationLayer, startCellNdx.x, startCellNdx.y );
	if (goalCell == 0)
		return 0;

	Bool goalOnObstacle = false;
	if (m_ignoreObstacleID != INVALID_ID)
	{
		Object *goalObj = TheGameLogic->findObjectByID( m_ignoreObstacleID );
		if (goalObj)
		{
			PathfindCell *ignoreCell = getClippedCell( (PathfindLayerEnum)goalObj->getLayer(), goalObj->getPosition() );
			if (goalCell->getObstacleID() == ignoreCell->getObstacleID() && goalCell->getObstacleID() != INVALID_ID)
			{
				Object *newObstacle = TheGameLogic->findObjectByID( goalCell->getObstacleID() );
				if (newObstacle != 0 && newObstacle->isKindOf( KINDOF_FS_AIRFIELD ))
				{
					m_ignoreObstacleID = goalCell->getObstacleID();
					goalOnObstacle = true;
				}
				else if (m_ignoreObstacleID == goalCell->getObstacleID())
				{
					goalOnObstacle = true;
				}
			}
		}
	}

	worldToCell( from, &startCellNdx );
	PathfindCell *parentCell = getCell( (PathfindLayerEnum)obj->getLayer(), &clipFrom );
	if (parentCell == 0)
		return 0;

	BfmeMoveCheckInfo moveInfo;
	Int limit = obj->getTemplate()->m_bfme444;
	Bool flag = obj->getTemplate()->m_bfme4cc;
	moveInfo.isComputer = obj->bfmeIsComputerControlled();
	moveInfo.surfaces = locomotorSet.getValidSurfaces();
	moveInfo.notFlag4cc = !flag;
	moveInfo.limit444 = limit - 1;
	if (!bfmeStepD4F90( &moveInfo, parentCell ))
		m_isTunneling = true;

	TCheckMovementInfo info;
	info.cell = startCellNdx;
	info.layer = (PathfindLayerEnum)obj->getLayer();
	info.radius = radius;
	info.centerInCell = centerInCell;
	info.considerTransient = blocked;
	info.bfme14 = 1;
	if (obj->getAIUpdateInterface())
		info.ignoredObstacle = obj->getAIUpdateInterface()->getIgnoredObstacleID();
	else
		info.ignoredObstacle = 0;
	if (!bfmeStepE05B0( obj, (ICoord2D *)&info ))
		m_isTunneling = true;

	Bool gotHierarchicalPath = false;
	m_bfmeWaypoints.clear();
	if (m_isTunneling)
	{
		m_zoneManager.bfmeFillAL();
	}
	else
	{
		m_zoneManager.bfmeClearAL();
		Path *hPat = rva003EEB90HierarchicalPath( isHuman, locomotorSet.getValidSurfaces(), obj, from, &adjustTo, false, true );
		if (hPat)
		{
			delete hPat;
			gotHierarchicalPath = true;
		}
		else
		{
			m_zoneManager.bfmeFillAL();
		}
	}

	const Bool startedStuck = m_isTunneling;

	{
		ICoord2D pos2d;
		worldToCell( &to, &pos2d );
		goalCell->allocateInfo( pos2d );
		if (parentCell != goalCell)
		{
			worldToCell( &clipFrom, &pos2d );
			parentCell->allocateInfo( pos2d );
		}
	}

	parentCell->startPathfind( goalCell );
	parentCell->m_info->m_totalCost = (UnsignedShort)rva003db900( parentCell, goalCell );
	Int bucket = parentCell->m_info->m_totalCost >> 7;

	PathfindCell *closestCell = 0;
	Real closestDistanceSqr = 3.402823466e+38f;
	Real closestDistScreenSqr = 8.507058665e+37f;
	Real skipDistSqr = 8.507058665e+37f;

	parentCell->putInBucket( &m_openBuckets[bucket] );
	if (bucket < m_openBucket)
		m_openBucket = bucket;

	Int count = 0;
	Bool foundGoal = false;

	while (m_openBucket < 0x200)
	{
		while (m_openBuckets[m_openBucket] == 0)
		{
			if (++m_openBucket >= 0x200)
				goto done;
		}

		parentCell = m_openBuckets[m_openBucket]->m_cell;
		parentCell->detachFromBucket();
		if (parentCell == 0)
			break;

		if (parentCell == goalCell)
		{
			void *blocking;
			if (goalOnObstacle || closestCell == 0 || canPathThroughUnits ||
				(bfmeInnerE6E90( obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
					(void *)parentCell->getLayer(), (void *)radius, (void *)centerInCell, &blocking, 0 ) &&
				 blocking == 0))
			{
				m_isTunneling = false;
				Path *path = buildActualPath( obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, blocked );
				parentCell->releaseInfo();
				goalCell->releaseInfo();
				cleanOpenAndClosedLists();
				return path;
			}
			foundGoal = true;
			parentCell->putOnClosedList( &m_closedList );
			continue;
		}

		parentCell->putOnClosedList( &m_closedList );

		void *blocking;
		if (!m_isTunneling &&
			bfmeInnerE6E90( obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
				(void *)parentCell->getLayer(), (void *)radius, (void *)centerInCell, &blocking, 0 ) &&
			blocking == 0 &&
			(!startedStuck || bfmeStepD4F90( &moveInfo, parentCell )))
		{
			Real dx = (Real)abs( goalCell->getXIndex() - parentCell->getXIndex() );
			Real dy = (Real)abs( goalCell->getYIndex() - parentCell->getYIndex() );
			Real distSqr = dx*dx + dy*dy;
			if (distSqr < closestDistScreenSqr)
			{
				closestDistScreenSqr = distSqr;
				if (dy + dx <= 25.0f)
					skipDistSqr = 4.0f * distSqr;
				else
					skipDistSqr = (sqrtf( distSqr ) + 25.0f) * (sqrtf( distSqr ) + 25.0f);
			}
			Real cost = parentCell->m_info->m_costSoFar;
			Real score = (Real)(m_bfmeWaypoints.size() * 10000) + 0.01f * cost * cost * pathCostMultiplier + distSqr;
			if (score < closestDistanceSqr)
			{
				adjustCoordToCell( parentCell->getXIndex(), parentCell->getYIndex(), centerInCell, clipFrom,
					(PathfindLayerEnum)parentCell->getLayer() );
				if (rva003DF250CanReach( obj, &clipFrom ))
				{
					closestCell = parentCell;
					closestDistanceSqr = score;
				}
			}
		}

		Real dx = (Real)abs( goalCell->getXIndex() - parentCell->getXIndex() );
		Real dy = (Real)abs( goalCell->getYIndex() - parentCell->getYIndex() );
		Real distSqr = dx*dx + dy*dy;
		if (distSqr > skipDistSqr)
		{
			Bool skip = false;
			if (!gotHierarchicalPath)
				skip = true;
			if (count > 2000)
				skip = true;
			if (distSqr < 100.0f)
				skip = false;
			if (skip)
				continue;
		}

		if (!foundGoal)
		{
			rva003DAE40ChangeLayers( parentCell, obj );
			count += examineNeighboringCells( parentCell, goalCell, locomotorSet, isHuman, centerInCell,
				radius, startCellNdx, obj, 0 );
		}
	}

done:
	m_isTunneling = false;
	if (closestCell)
	{
		adjustTo.x = closestCell->getXIndex() * 10 + 5.0f;
		adjustTo.y = closestCell->getYIndex() * 10 + 5.0f;
		Path *path = buildActualPath( obj, locomotorSet.getValidSurfaces(), from, closestCell, centerInCell, blocked );
		cleanOpenAndClosedLists();
		goalCell->releaseInfo();
		return path;
	}

	goalCell->releaseInfo();
	cleanOpenAndClosedLists();
	return 0;
}

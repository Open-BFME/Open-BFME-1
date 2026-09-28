// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003EE360 (771 bytes): BfmeAttackQuery::bfmeCanAttackTarget, the
// attack reachability test Object::getAbleToAttackSpecificObject and
// AIAttackMeleeHordeWaitPathState::update call through ILT 0x0002DB1E on
// TheAI->pathfinder().  BfmeAttackQuery is the established view of the
// Pathfinder (the same object the matched checkCandidate at 0x003EE2B0 runs
// on).  A target cell that is not an obstacle falls through to the
// path-existence query; an obstacle cell is probed one target radius away in
// each of the four axis directions.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned short zoneStorageType;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set( const Coord3D *p ) { x = p->x; y = p->y; z = p->z; }
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[ 2 ];
	Int layer;
};

struct BfmeCellInfo
{
	unsigned char m_pad00[ 0x20 ];
	Int m_field20;
};

struct BfmeCellResult
{
	const void *m_query;
	Int m_ownerId;
	Int m_candidateZone;
	Int m_candidateX;
	Int m_candidateY;
};

class PathfindCell
{
public:
	enum { CELL_OBSTACLE = 4 };

	Int getType() const { return m_packed & 7; }
	zoneStorageType getZone() const { return m_zone; }

	BfmeCellInfo *m_info;
	Int m_ownerId;
	zoneStorageType m_zone;
	unsigned short m_pad0a;
	unsigned int m_packed;
};

class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone( const PathfindMovementProfile &profile,
		zoneStorageType zone ) const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if( !m_overridable )
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[ 0x444 - 0x08 ];
	Int m_int444;
	unsigned char m_pad448[ 0x4cc - 0x448 ];
	Bool m_bool4cc;
};

class LocomotorSet
{
public:
	Int getValidSurfaces() const { return m_validLocomotorSurfaces; }

private:
	unsigned char m_pad00[ 0x10 ];
	Int m_validLocomotorSurfaces;
};

class AIUpdateInterface
{
public:
	const LocomotorSet &getLocomotorSet() const { return m_locomotorSet; }

private:
	unsigned char m_pad000[ 0x1a8 ];
	LocomotorSet m_locomotorSet;
};

struct BfmeShapeE15
{
	unsigned char m_pad00[ 0x10 ];
	Coord3D m_offset;
};

// Object+0xac: the shape container whose indexed accessor is 0x0087E150
// (shapes of 0x24 bytes between +0x2c and +0x30).
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15( Int index );
	Real getReal10() const { return m_real10; }

private:
	unsigned char m_pad00[ 0x10 ];
	Real m_real10;
	unsigned char m_pad14[ 0x2c - 0x14 ];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
};

class Object
{
public:
	const OVERRIDE<ThingTemplate> &getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position38; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	const BfmeObjE15 &getObjE15() const { return m_objE15ac; }
	Bool bfmeIsComputerControlled() const;

	void *m_vtable;
	OVERRIDE<ThingTemplate> m_template;
	unsigned char m_pad008[ 0x38 - 0x08 ];
	Coord3D m_position38;
	unsigned char m_pad044[ 0xac - 0x44 ];
	BfmeObjE15 m_objE15ac;
	unsigned char m_pade0[ 0x204 - 0xe0 ];
	AIUpdateInterface *m_ai;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination( Object *object, const Coord3D *position );
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Bool worldToCell( const Coord3D *pos, ICoord2D *cell );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );
};

// The path-existence query at 0x003EDF90 (ILT 0x0004A327) takes the same
// trailing locomotor argument this query received.
extern void j_0004a327();

class BfmeAttackQuery
{
public:
	Bool checkCandidate( const ICoord2D *base, Int offsetX, Int offsetY,
		Int movementLayer, Int pathLayer, Int fromZone, BfmeCellResult *result,
		const PathfindMovementProfile *profile, const void *extra );

	Bool bfmeCanAttackTarget( const Object *source, const Coord3D *sourcePosition,
		const Object *target, const void *extra ) const;

private:
	unsigned char m_pad000[ 0xc9c ];
	PathfindZoneManager m_zoneManager;
};

static __forceinline Bool pathExists( const BfmeAttackQuery *query, const Object *obj,
	const Coord3D *from, const Coord3D *to, const void *extra )
{
	typedef Bool ( BfmeAttackQuery::*Function )( const Object *, const Coord3D *,
		const Coord3D *, const void * ) const;
	union { void ( *raw )(); Function member; } fn;
	fn.raw = j_0004a327;
	return ( query->*fn.member )( obj, from, to, extra );
}

// ?bfmeCanAttackTarget@BfmeAttackQuery@@QBE_NPBVObject@@PBUCoord3D@@0PBX@Z
Bool BfmeAttackQuery::bfmeCanAttackTarget( const Object *source,
	const Coord3D *sourcePosition, const Object *target, const void *extra ) const
{
	AIUpdateInterface *ai = source->getAIUpdateInterface();
	if( ai == 0 && extra == 0 )
		return false;
	const LocomotorSet *locomotorSet = extra ? (const LocomotorSet *)extra : &ai->getLocomotorSet();
	if( ( locomotorSet->getValidSurfaces() & 0xf ) == 0 )
		return false;

	BfmeAttackQuery *self = const_cast<BfmeAttackQuery *>( this );
	Pathfinder *pathfinder = (Pathfinder *)self;

	Coord3D targetPosition;
	targetPosition.set( target->getPosition() );
	PathfindLayerEnum targetLayer = TheTerrainLogic->getLayerForDestination(
		const_cast<Object *>( source ), &targetPosition );
	PathfindLayerEnum sourceLayer = TheTerrainLogic->getLayerForDestination(
		const_cast<Object *>( source ), sourcePosition );

	ICoord2D cell;
	pathfinder->worldToCell( sourcePosition, &cell );
	PathfindCell *sourceCell = pathfinder->getCell( sourceLayer, cell.x, cell.y );
	pathfinder->worldToCell( &targetPosition, &cell );
	PathfindCell *targetCell = pathfinder->getCell( targetLayer, cell.x, cell.y );
	if( targetCell->getType() != PathfindCell::CELL_OBSTACLE )
	{
		const Coord3D *offset = &const_cast<BfmeObjE15 &>( target->getObjE15() ).bfmeAtE15( 0 )->m_offset;
		targetPosition.x += offset->x;
		targetPosition.y += offset->y;
		targetPosition.z += offset->z;
		pathfinder->worldToCell( &targetPosition, &cell );
		targetCell = pathfinder->getCell( targetLayer, cell.x, cell.y );
		if( targetCell->getType() != PathfindCell::CELL_OBSTACLE )
			return pathExists( this, source, sourcePosition, &targetPosition, locomotorSet );
	}

	Int owner = targetCell->m_info ? targetCell->m_info->m_field20 : 0;
	pathfinder->worldToCell( &targetPosition, &cell );

	Int layer444 = source->getTemplate()->m_int444;
	Bool bool4cc = source->getTemplate()->m_bool4cc;
	Bool computer = source->bfmeIsComputerControlled();
	PathfindMovementProfile profile;
	profile.acceptableSurfaces = locomotorSet->getValidSurfaces();
	profile.crusher = !bool4cc;
	profile.terrainOnly = computer;
	profile.layer = layer444 - 1;
	Int fromZone = m_zoneManager.getEffectiveZone( profile, sourceCell->getZone() );

	BfmeCellResult result;
	result.m_query = this;
	result.m_ownerId = owner;
	result.m_candidateZone = 0;
	result.m_candidateX = -1;
	result.m_candidateY = -1;

	Int radius = 2 - (Int)( target->getObjE15().getReal10() * -0.1f );
	if( self->checkCandidate( &cell, radius, 0, (Int)source, targetLayer, fromZone,
			&result, &profile, locomotorSet ) )
		return true;
	if( self->checkCandidate( &cell, -radius, 0, (Int)source, targetLayer, fromZone,
			&result, &profile, locomotorSet ) )
		return true;
	if( self->checkCandidate( &cell, 0, radius, (Int)source, targetLayer, fromZone,
			&result, &profile, locomotorSet ) )
		return true;
	return self->checkCandidate( &cell, 0, -radius, (Int)source, targetLayer, fromZone,
		&result, &profile, locomotorSet );
}

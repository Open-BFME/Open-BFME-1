// cl: /DNDEBUG /MD
//
// Retail 0x003DEAB0.
//
class LocomotorSet;

typedef int Int;
typedef bool Bool;

struct Coord3D { float x, y, z; };

enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

class Object
{
public:
	Int getLayer( void ) const;

	char m_pad[0x38];
	Coord3D m_pos;
};

class Weapon
{
public:
	Bool isGoalPosWithinAttackRange( const Object *obj, const Coord3D *pos,
		const Object *victim, const Coord3D *victimPos, Int flags ) const;
};

class Pathfinder
{
public:
	Bool checkForAdjust( Object *obj, const LocomotorSet *locomotorSet, Bool center,
		Int cellX, Int cellY, Int layer, Coord3D *pos, Bool isHuman );
	Bool checkDestination( const Object *obj, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int iRadius, Bool center );
};

class Rva003DEAB0Struct
{
public:
	Bool checkCell( Int cellX, Int cellY );

	Pathfinder *m_pathfinder;			// 0x00
	Object *m_obj;						// 0x04
	const LocomotorSet *m_locomotorSet;	// 0x08
	Bool m_center;						// 0x0C
	Int m_layer;						// 0x10
	Coord3D m_pos;						// 0x14
	Bool m_isHuman;						// 0x20
	Weapon *m_weapon;					// 0x24
	Object *m_target;					// 0x28
	Object *m_victim;					// 0x2C
	Int m_radius;						// 0x30
	Coord3D *m_dest;					// 0x34
	Bool m_retryOnTargetLayer;			// 0x38
};

Bool Rva003DEAB0Struct::checkCell( Int cellX, Int cellY )
{
	if( !m_pathfinder->checkForAdjust( m_obj, m_locomotorSet, m_center, cellX, cellY,
			m_layer, &m_pos, m_isHuman ) )
	{
		if( !m_retryOnTargetLayer )
			return false;

		if( !m_pathfinder->checkForAdjust( m_obj, m_locomotorSet, m_center, cellX, cellY,
				m_target->getLayer(), &m_pos, m_isHuman ) )
			return false;
	}

	if( !m_weapon->isGoalPosWithinAttackRange( m_target, &m_pos, m_victim, &m_victim->m_pos, 0 ) )
		return false;

	if( !m_pathfinder->checkDestination( m_target, cellX, cellY, (PathfindLayerEnum)m_layer, m_radius, m_center ) )
		return false;

	*m_dest = m_pos;
	return true;
}

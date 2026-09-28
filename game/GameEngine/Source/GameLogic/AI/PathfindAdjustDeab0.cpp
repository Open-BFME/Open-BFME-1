// cl: /DNDEBUG /MD
//
// Retail 0x003DEAB0.
//
// The record's +0x04/+0x08/+0x20 fields are the first, second and last
// arguments of Pathfinder::checkForPossible (0x003D6210 via ILT 0x00018BE7):
// the movement-profile pointer, the start zone and startingInObstacle.
// targets/game/reverse/identity_evidence/003d6210-checkforpossible.md
//
struct PathfindMovementProfile;

typedef int Int;
typedef bool Bool;

struct Coord3D { float x, y, z; };

enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int getLayer( void ) const;

	char m_pad[0x38];
	Coord3D m_pos;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	Bool isGoalPosWithinAttackRange( const Object *object, const Coord3D *goalPosition,
		const Object *victim, const Coord3D *victimPosition, Int flags ) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool checkForPossible( const PathfindMovementProfile &profile, Int fromZone, Bool center,
		Int cellX, Int cellY, PathfindLayerEnum layer, Coord3D *dest, Bool startingInObstacle );
	Bool checkDestination( const Object *object, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int radius, Bool centerInCell );
};

class Rva003DEAB0Struct
{
public:
	Bool checkCell( Int cellX, Int cellY );

	Pathfinder *m_pathfinder;			// 0x00
	const PathfindMovementProfile *m_profile;	// 0x04
	Int m_fromZone;						// 0x08
	Bool m_centerInCell;						// 0x0C
	Int m_layer;						// 0x10
	Coord3D m_candidatePosition;						// 0x14
	Bool m_startingInObstacle;			// 0x20
	Weapon *m_weapon;					// 0x24
	Object *m_target;					// 0x28
	Object *m_victim;					// 0x2C
	Int m_radius;						// 0x30
	Coord3D *m_destination;					// 0x34
	Bool m_retryOnTargetLayer;			// 0x38
};

Bool Rva003DEAB0Struct::checkCell( Int cellX, Int cellY )
{
	if( !m_pathfinder->checkForPossible( *m_profile, m_fromZone, m_centerInCell, cellX, cellY,
			(PathfindLayerEnum)m_layer, &m_candidatePosition, m_startingInObstacle ) )
	{
		if( !m_retryOnTargetLayer )
			return false;

		if( !m_pathfinder->checkForPossible( *m_profile, m_fromZone, m_centerInCell, cellX, cellY,
				(PathfindLayerEnum)m_target->getLayer(), &m_candidatePosition, m_startingInObstacle ) )
			return false;
	}

	if( !m_weapon->isGoalPosWithinAttackRange( m_target, &m_candidatePosition, m_victim, &m_victim->m_pos, 0 ) )
		return false;

	if( !m_pathfinder->checkDestination( m_target, cellX, cellY, (PathfindLayerEnum)m_layer, m_radius, m_centerInCell ) )
		return false;

	*m_destination = m_candidatePosition;
	return true;
}

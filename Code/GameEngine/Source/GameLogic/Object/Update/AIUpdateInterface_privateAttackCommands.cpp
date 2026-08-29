// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateAttackFollowWaypointPath@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateAttackObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable bodies: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum WeaponSetType
{
	WEAPONSET_MINE_CLEARING_DETAIL = 8
};

enum AIStateType
{
	AI_ATTACK_OBJECT = 0x17,
	AI_ATTACKFOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS = 0x22,
	AI_ATTACKFOLLOW_WAYPOINT_PATH_AS_TEAM = 0x23
};

class WeaponSetFlags
{
public:
	Bool test( WeaponSetType type ) const
	{
		return (m_words[ 0 ] & (1U << type)) != 0;
	}

private:
	unsigned int m_words[ 1 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	void setMaxShotCount( int maxShots )
	{
		m_maxShotCount = maxShots;
		m_shotsFired = 0;
	}

private:
	unsigned char m_unmodelled_00[ 0x20 ];
	int m_shotsFired;
	unsigned char m_unmodelled_24[ 0x34 - 0x24 ];
	int m_maxShotCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const
	{
		return &m_location;
	}

private:
	unsigned char m_unmodelled_00[ 0x0C ];
	Coord3D m_location;
};

enum WeaponSlotType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon( WeaponSlotType *slot );
	Bool isMobile() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void stateMachineAnchor00();
	virtual void stateMachineAnchor04();
	virtual void stateMachineAnchor08();
	virtual void stateMachineAnchor0C();
	virtual void stateMachineAnchor10();
	virtual void clear();
	virtual void stateMachineAnchor18();
	virtual void stateMachineAnchor1C();
	virtual void setState( AIStateType state );

	void setGoalObject( const Object *object );
	Object *getGoalObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIStateMachine : public StateMachine
{
public:
	void setGoalWaypoint( const Waypoint *way );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateAttackObject( Object *victim, int maxShotsToFire, CommandSourceType cmdSource );
	virtual void privateAttackFollowWaypointPath( const Waypoint *way, int maxShotsToFire, Bool asTeam,
		CommandSourceType cmdSource );

	void playAttackVoiceResponse( Object *victim );
	void playMoveVoiceResponse( const Coord3D *position );

private:
	unsigned char m_unmodelled_04[ 4 ];
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x30 - 0x0C ];
	AIStateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[ 0x48 - 0x34 ];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[ 0x32B - 0x4C ];
	Bool m_isAiDead;
};

void AIUpdateInterface::privateAttackObject( Object *victim, int maxShotsToFire, CommandSourceType cmdSource )
{
	if( m_object->getWeaponSetFlags().test( WEAPONSET_MINE_CLEARING_DETAIL ) )
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject( victim );
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState( AI_ATTACK_OBJECT );

	Weapon *weapon = m_object->getCurrentWeapon( 0 );
	if( weapon )
		weapon->setMaxShotCount( maxShotsToFire );

	Object *goal = m_stateMachine->getGoalObject();
	if( goal && (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT) )
		playAttackVoiceResponse( goal );
}

void AIUpdateInterface::privateAttackFollowWaypointPath( const Waypoint *way, int maxShotsToFire, Bool asTeam,
	CommandSourceType cmdSource )
{
	if( m_isAiDead || !m_object->isMobile() )
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalWaypoint( way );
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState( asTeam ? AI_ATTACKFOLLOW_WAYPOINT_PATH_AS_TEAM :
		AI_ATTACKFOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS );

	Weapon *weapon = m_object->getCurrentWeapon( 0 );
	if( weapon )
		weapon->setMaxShotCount( maxShotsToFire );

	if( cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT )
		playMoveVoiceResponse( way->getLocation() );
}

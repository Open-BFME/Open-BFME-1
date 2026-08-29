// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateFollowWaypointPath@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateFollowWaypointPathAsTeam@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateFollowWaypointPathAsTeamExact@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?privateFollowWaypointPathExact@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable bodies: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef unsigned int ObjectID;
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

enum AIStateType
{
	AI_FOLLOW_WAYPOINT_PATH_AS_TEAM = 2,
	AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS = 3,
	AI_FOLLOW_WAYPOINT_PATH_AS_TEAM_EXACT = 4,
	AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS_EXACT = 5
};

enum
{
	NO_FORMATION_ID = 0
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isMobile() const;

	void setFormationID( ObjectID id )
	{
		m_formationID = id;
	}

private:
	unsigned char m_unmodelled_00[ 0x31C ];
	ObjectID m_formationID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIStateMachine
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

	void setGoalWaypoint( const Waypoint *way );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateFollowWaypointPath( const Waypoint *way, CommandSourceType cmdSource );
	virtual void privateFollowWaypointPathExact( const Waypoint *way, CommandSourceType cmdSource );
	virtual void privateFollowWaypointPathAsTeam( const Waypoint *way, CommandSourceType cmdSource );
	virtual void privateFollowWaypointPathAsTeamExact( const Waypoint *way, CommandSourceType cmdSource );

	void playMoveVoiceResponse( const Coord3D *position );

private:
	unsigned char m_unmodelled_04[ 4 ];
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x30 - 0x0C ];
	AIStateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[ 0x48 - 0x34 ];
	CommandSourceType m_lastCommandSource;
};

void AIUpdateInterface::privateFollowWaypointPath( const Waypoint *way, CommandSourceType cmdSource )
{
	if( !m_object->isMobile() )
		return;

	m_object->setFormationID( NO_FORMATION_ID );
	m_stateMachine->clear();
	m_stateMachine->setGoalWaypoint( way );
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState( AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS );

	if( cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT )
		playMoveVoiceResponse( way->getLocation() );
}

void AIUpdateInterface::privateFollowWaypointPathExact( const Waypoint *way, CommandSourceType cmdSource )
{
	if( !m_object->isMobile() )
		return;

	m_object->setFormationID( NO_FORMATION_ID );
	m_stateMachine->clear();
	m_stateMachine->setGoalWaypoint( way );
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState( AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS_EXACT );

	if( cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT )
		playMoveVoiceResponse( way->getLocation() );
}

void AIUpdateInterface::privateFollowWaypointPathAsTeam( const Waypoint *way, CommandSourceType cmdSource )
{
	if( !m_object->isMobile() )
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalWaypoint( way );
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState( AI_FOLLOW_WAYPOINT_PATH_AS_TEAM );

	if( cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT )
		playMoveVoiceResponse( way->getLocation() );
}

void AIUpdateInterface::privateFollowWaypointPathAsTeamExact( const Waypoint *way, CommandSourceType cmdSource )
{
	if( !m_object->isMobile() )
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalWaypoint( way );
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState( AI_FOLLOW_WAYPOINT_PATH_AS_TEAM_EXACT );

	if( cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT )
		playMoveVoiceResponse( way->getLocation() );
}

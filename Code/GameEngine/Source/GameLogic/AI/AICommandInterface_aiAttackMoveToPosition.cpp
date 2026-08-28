// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: AICommandInterface::aiAttackMoveToPosition, retail 0x00153AF0.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_ATTACKMOVE_TO_POSITION = 0x0F
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType cmdSource );

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	void *m_obj;
	void *m_otherObj;
	void *m_team;
	std::vector<Coord3D> m_coords;
	void *m_waypoint;
	void *m_polygon;
	int m_intValue;
	char m_remaining[0x9c - 0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;
	void aiAttackMoveToPosition( const Coord3D *pos, int maxShotsToFire,
		CommandSourceType cmdSource );
};

void AICommandInterface::aiAttackMoveToPosition( const Coord3D *pos,
	int maxShotsToFire, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_ATTACKMOVE_TO_POSITION, cmdSource );
	parms.m_pos = *pos;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand( &parms );
}

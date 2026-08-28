// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: AICommandInterface::aiEnter, retail 0x000D89C0.

#include <vector>

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_MOVE_TO_POSITION = 0,
	AICMD_HUNT = 0x12,
	AICMD_ENTER = 0x17
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
	Object *m_obj;
	Object *m_otherObj;
	void *m_team;
	std::vector<Coord3D> m_coords;
	char m_remaining[0x9c - 0x2c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;
	void aiMoveToPosition( const Coord3D *pos, CommandSourceType cmdSource );
	void aiHunt( CommandSourceType cmdSource );
	void aiEnter( Object *obj, CommandSourceType cmdSource );
};

void AICommandInterface::aiMoveToPosition( const Coord3D *pos, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_MOVE_TO_POSITION, cmdSource );
	parms.m_pos = *pos;
	aiDoCommand( &parms );
}

void AICommandInterface::aiHunt( CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_HUNT, cmdSource );
	aiDoCommand( &parms );
}

void AICommandInterface::aiEnter( Object *obj, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_ENTER, cmdSource );
	parms.m_obj = obj;
	aiDoCommand( &parms );
}

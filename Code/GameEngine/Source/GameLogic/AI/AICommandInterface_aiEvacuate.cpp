// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: AICommandInterface::aiEvacuate, retail 0x000D8AC0.

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
	AICMD_EVACUATE = 0x1b
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

	char m_beforeCoords[0x20];
	std::vector<Coord3D> m_coords;
	char m_beforeIntValue[0x08];
	int m_intValue;
	char m_remaining[0x9c - 0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;
	void aiEvacuate( bool exposeStealthUnits, CommandSourceType cmdSource );
};

void AICommandInterface::aiEvacuate( bool exposeStealthUnits, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_EVACUATE, cmdSource );
	if ( exposeStealthUnits )
		parms.m_intValue = 1;
	else
		parms.m_intValue = 0;
	aiDoCommand( &parms );
}

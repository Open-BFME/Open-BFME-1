// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Near-twin of AICommandInterface::aiBfmeCommand19 (twin 0x00154210,
// AICommandInterface_aiBfmeCommand19.cpp): identical single-Coord3D command
// wrapper, but the AICommandType immediate is 0x38 instead of 0x19.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D { Real x, y, z; };

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

enum AICommandType { AICMD_BFME_38 = 0x38 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
	AICommandType						m_cmd;
	CommandSourceType				m_cmdSource;
	Coord3D									m_pos;
	Object									*m_obj;
	Object									*m_otherObj;
	const Team							*m_team;
	_STL::vector<Coord3D>		m_coords;
	const Waypoint					*m_waypoint;
	const PolygonTrigger		*m_polygon;
	Int											m_intValue;
	DamageInfo							m_damage;
	const CommandButton			*m_commandButton;
	Path										*m_path;

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiBfmeCommand38(const Coord3D *pos, CommandSourceType cmdSource);
};

// @?aiBfmeCommand38@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z 0x00205200
void AICommandInterface::aiBfmeCommand38(const Coord3D *pos, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_38, cmdSource);
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

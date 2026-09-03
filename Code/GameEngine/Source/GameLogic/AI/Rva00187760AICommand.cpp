// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME command wrapper at retail 0x00187760: command 0x3C.

#include <vector>

typedef int Int;
typedef bool Bool;

struct Coord3D { float x, y, z; };
class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

enum AICommandType { AICMD_BFME_3C = 0x3C };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

struct DamageInfo { char m_body[0x5C]; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const Team *m_team;
	_STL::vector<Coord3D> m_coords;
	const Waypoint *m_waypoint;
	const PolygonTrigger *m_polygon;
	Int m_intValue;
	DamageInfo m_damage;
	const CommandButton *m_commandButton;
	Path *m_path;
	AICommandParms(AICommandType, CommandSourceType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *) = 0;
	void bfmeCommand3C(Object *objectToEnter, CommandSourceType cmdSource);
};

void AICommandInterface::bfmeCommand3C(Object *objectToEnter, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_3C, cmdSource);
	parms.m_obj = objectToEnter;
	aiDoCommand(&parms);
}

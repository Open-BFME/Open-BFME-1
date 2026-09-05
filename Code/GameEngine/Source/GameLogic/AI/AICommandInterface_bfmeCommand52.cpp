// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Near-twin of AICommandInterface::bfmeCommand01 (twin 0x00187440,
// Rva00187440AICommand.cpp): identical single-Object command wrapper, but
// the AICommandType immediate is 0x34 instead of 0x01.

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

enum AICommandType { AICMD_BFME_34 = 0x34 };
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
	void bfmeCommand52(Object *objectToEnter, CommandSourceType cmdSource);
};

// @?bfmeCommand52@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z 0x001FCD40
void AICommandInterface::bfmeCommand52(Object *objectToEnter, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_34, cmdSource);
	parms.m_obj = objectToEnter;
	aiDoCommand(&parms);
}

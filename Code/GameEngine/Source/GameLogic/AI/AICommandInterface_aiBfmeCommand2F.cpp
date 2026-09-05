// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface command 0x2F, retail 0x002E9030, 203 bytes.
// Same shape as aiFaceObject (0x002A8160): construct AICommandParms, store the
// object pointer at m_obj (+0x14), aiDoCommand at vtable slot 0. The command
// id is a BFME addition; only the numeric id is recovered from the push 0x2F.
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

enum AICommandType { AICMD_BFME_2F = 0x2F };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// Opaque retail DamageInfo storage, constructor offsets0x38..0x93.
// Its internal virtual pointers are initialized by the external parameter ctor.
struct DamageInfo
{
	char m_bfme_body[0x5C];
};

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
	void aiBfmeCommand2F(Object *target, CommandSourceType cmdSource);
};

void AICommandInterface::aiBfmeCommand2F(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_2F, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

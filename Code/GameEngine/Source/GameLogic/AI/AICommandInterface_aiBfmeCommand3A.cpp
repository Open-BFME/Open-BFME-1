// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface command 0x3A, retail 0x002E9130, 192 bytes.
// Same shape as aiWanderInPlace (0x00300420): construct AICommandParms with
// the command id and cmdSource, then aiDoCommand. No extra field store.
// The command id is a BFME addition; only the numeric id is recovered from
// the push 0x3A.
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

enum AICommandType { AICMD_BFME_3A = 0x3A };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// Opaque retail0x5C storage initialized by external AICommandParms ctor.
struct DamageInfo
{
	char m_bfme_body[0x5C];
};

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

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiBfmeCommand3A(CommandSourceType cmdSource);
};

void AICommandInterface::aiBfmeCommand3A(CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_3A, cmdSource);
	aiDoCommand(&parms);
}

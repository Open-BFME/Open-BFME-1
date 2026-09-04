// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiPanic, retail 0x00300510, 203 bytes.

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

enum AICommandType { AICMD_PANIC = 0x2D };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

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
	void aiPanic(const Waypoint *way, CommandSourceType cmdSource);
};

void AICommandInterface::aiPanic(const Waypoint *way, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_PANIC, cmdSource);
	parms.m_waypoint = way;
	aiDoCommand(&parms);
}

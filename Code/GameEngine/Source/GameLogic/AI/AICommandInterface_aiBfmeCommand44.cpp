// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface command 0x44, retail 0x001549A0, 241 bytes.
//
// Same AICommandParms builder as aiGuardPosition, with an extra pointer
// stored at m_polygon (+0x30) and the command id 0x44. Four args, ret 10h.
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

enum AICommandType { AICMD_BFME_44 = 0x44 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

struct DamageInfo
{
	char m_bfme_body[0x5C];
};

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

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;

	void aiBfmeCommand44(const PolygonTrigger *poly, Int value,
			CommandSourceType cmdSource, const Coord3D *pos);
};

void AICommandInterface::aiBfmeCommand44(const PolygonTrigger *poly, Int value,
		CommandSourceType cmdSource, const Coord3D *pos)
{
	AICommandParms parms(AICMD_BFME_44, cmdSource);
	parms.m_polygon = poly;
	parms.m_intValue = value;
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

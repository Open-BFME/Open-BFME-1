// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiFaceObject, retail 0x002A8160, 203 bytes.
// BFME's face-object command is 0x26 in this translation unit.
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

enum AICommandType { AICMD_FACE_OBJECT = 0x26 };
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

	AICommandParms(AICommandType, CommandSourceType);
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *) = 0;
	void aiFaceObject(Object *target, CommandSourceType cmdSource);
};

void AICommandInterface::aiFaceObject(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FACE_OBJECT, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

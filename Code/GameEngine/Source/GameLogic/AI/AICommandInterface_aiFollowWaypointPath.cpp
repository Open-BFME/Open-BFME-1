// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiFollowWaypointPath, retail 0x00152D20, 203 bytes.
//
// One of the reference's inline command builders, out of line here: build the
// parameter block, put the waypoint in the waypoint slot at +0x2C, then aiDoCommand at vtable slot 0.
//
// Almost the whole body is the block: 0x9C of locals, the coordinate vector at
// +0x20 being the only member with anything to tear down -- the same frame
// AICommandInterface_aiAttackObject.cpp measured.
//
// AICMD_FOLLOW_WAYPOINT_PATH is 0x06 in BFME's command list, which is the reference's
// order -- the values this family already pins (0x0B, 0x0F, 0x12, 0x15, 0x17)
// are exactly the reference's indices.
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

enum AICommandType { AICMD_FOLLOW_WAYPOINT_PATH = 0x06 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
	AICommandType						m_cmd;			// +0x00
	CommandSourceType				m_cmdSource;		// +0x04
	Coord3D									m_pos;			// +0x08
	Object									*m_obj;			// +0x14
	Object									*m_otherObj;		// +0x18
	const Team							*m_team;		// +0x1C
	_STL::vector<Coord3D>		m_coords;			// +0x20
	const Waypoint					*m_waypoint;		// +0x2C
	const PolygonTrigger		*m_polygon;			// +0x30
	Int											m_intValue;		// +0x34
	DamageInfo							m_damage;		// +0x38
	const CommandButton			*m_commandButton;	// +0x94
	Path										*m_path;		// +0x98

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);	// ILT 0x00030EA4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiFollowWaypointPath(const Waypoint *way, CommandSourceType cmdSource);
};

void AICommandInterface::aiFollowWaypointPath( const Waypoint *way, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH, cmdSource);
	parms.m_waypoint = way;
	aiDoCommand(&parms);
}

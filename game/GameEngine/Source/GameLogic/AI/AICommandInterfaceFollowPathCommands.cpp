// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface commands that hand a unit a path to walk.
//
//   ?aiFollowWaypointPath@         0x00152D20, 203 bytes
//   ?aiFollowWaypointPathExact@    0x00152E20, 203 bytes
//   ?aiFollowWaypointPathAsTeam@   0x00152F20, 203 bytes
//   ?aiBfmeCommand33@              0x00153020, 203 bytes
//   ?aiBfmeCommand9FollowPath@     0x00153120, 220 bytes
//   ?aiBfmeCommand36FollowPath@    0x00153240, 231 bytes
//   ?aiBfmeCommand37FollowPath@    0x00153360, 231 bytes
//   ?aiFollowExitProductionPath@   0x00165C30, 220 bytes
//
// The first seven are one run in the retail image, 0x100 to 0x120 apart, and
// they split into two shapes over the same AICommandParms builder.
//
// The 203-byte shape names the path by its head waypoint, stored in the
// waypoint slot at +0x2C; the only thing that separates its four members is the
// command id. AICMD_FOLLOW_WAYPOINT_PATH 0x06 and _AS_TEAM 0x07 are the
// reference's own indices, _EXACT is 0x32 and BFME's own is 0x33.
//
// The 220/231-byte shape carries the path itself, copied into the coordinate
// vector at +0x20 -- that copy is the extra 17 bytes over the waypoint shape --
// and names an object alongside it. Command 9 and AICMD_FOLLOW_EXITPRODUCTION_
// PATH 0x0A are the two-argument form; 0x24 and 0x25 add a second object
// pointer, which is their extra 11 bytes and their fourth argument.
//
// That second pointer does NOT go to m_otherObj. Retail writes it at +0x08, on
// top of the position, and the raw cast below is what reproduces that -- so the
// two BFME commands leave m_otherObj at +0x18 untouched and clobber m_pos.x
// instead. One of the two files merged here said in prose that it "writes two
// object fields (m_obj and m_otherObj)" while its own code did no such thing;
// with both bodies side by side there is only the one account to keep straight.
//
// DamageInfo is opaque here because no body in this TU touches the damage
// block; the reconstructed classes are in AICommandInterfaceAttackCommands.cpp,
// next to aiGoProne, which does.
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

enum AICommandType
{
	AICMD_FOLLOW_WAYPOINT_PATH			= 0x06,
	AICMD_FOLLOW_WAYPOINT_PATH_AS_TEAM	= 0x07,
	AICMD_BFME_9						= 0x09,
	AICMD_FOLLOW_EXITPRODUCTION_PATH	= 0x0A,
	AICMD_BFME_36						= 0x24,
	AICMD_BFME_37						= 0x25,
	AICMD_FOLLOW_WAYPOINT_PATH_EXACT	= 0x32,
	AICMD_BFME_33						= 0x33
};

enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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

	AICommandParms(AICommandType commandType, CommandSourceType commandSource);	// ILT 0x00030EA4
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiFollowWaypointPath(const Waypoint *waypoint, CommandSourceType commandSource);
	void aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType commandSource);
	void aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType commandSource);
	void aiBfmeCommand33(const Waypoint *waypoint, CommandSourceType commandSource);
	void aiBfmeCommand9FollowPath(const _STL::vector<Coord3D> *path, Object *ignoreObject, CommandSourceType commandSource);
	void aiBfmeCommand36FollowPath(const _STL::vector<Coord3D> *path, Object *object, Object *otherObject, CommandSourceType commandSource);
	void aiBfmeCommand37FollowPath(const _STL::vector<Coord3D> *path, Object *object, Object *otherObject, CommandSourceType commandSource);
	void aiFollowExitProductionPath(const _STL::vector<Coord3D> *path, Object *ignoreObject, CommandSourceType commandSource);
};

void AICommandInterface::aiFollowWaypointPath( const Waypoint *waypoint, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH, commandSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

void AICommandInterface::aiFollowWaypointPathExact( const Waypoint *waypoint, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH_EXACT, commandSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

void AICommandInterface::aiFollowWaypointPathAsTeam( const Waypoint *waypoint, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH_AS_TEAM, commandSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand33( const Waypoint *waypoint, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_BFME_33, commandSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand9FollowPath( const _STL::vector<Coord3D> *path, Object *ignoreObject, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_BFME_9, commandSource);
	parms.m_coords = *path;
	parms.m_obj = ignoreObject;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand36FollowPath( const _STL::vector<Coord3D> *path, Object *object, Object *otherObject, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_BFME_36, commandSource);
	parms.m_coords = *path;
	parms.m_obj = object;
	*(Object **)&parms.m_pos.x = otherObject;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand37FollowPath( const _STL::vector<Coord3D> *path, Object *object, Object *otherObject, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_BFME_37, commandSource);
	parms.m_coords = *path;
	parms.m_obj = object;
	*(Object **)&parms.m_pos.x = otherObject;
	aiDoCommand(&parms);
}

void AICommandInterface::aiFollowExitProductionPath( const _STL::vector<Coord3D> *path, Object *ignoreObject, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_FOLLOW_EXITPRODUCTION_PATH, commandSource);
	parms.m_coords = *path;
	parms.m_obj = ignoreObject;
	aiDoCommand(&parms);
}

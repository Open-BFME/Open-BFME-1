// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface commands that post a guard, plus the one
// BFME command built on the same payload.
//
//   ?aiGuardPosition@   0x00154550, 230 bytes, AICMD 0x1E
//   ?aiGuardObject@     0x00154670, 214 bytes, AICMD 0x1F
//   ?aiBfmeCommand20@   0x00154780, 214 bytes, AICMD 0x20
//   ?aiGuardArea@       0x00154890, 214 bytes, AICMD 0x21
//   ?aiBfmeCommand44@   0x001549A0, 241 bytes, AICMD 0x44
//
// Five contiguous bodies in the retail image, laid down in command order, and
// the same builder each time: construct AICommandParms, name what is being
// guarded, put the guard mode in the misc integer at +0x34, then aiDoCommand at
// vtable slot 0. Command 0x44 is aiGuardArea's payload -- a polygon and an
// integer -- with a position added, which is the extra 27 bytes and the fourth
// argument.
//
// Command 0x20 is the reason to read the run rather than the four named
// members. Its own file could only say it "writes m_team and an integer"; here
// it is the 214-byte body sitting between GUARD_OBJECT and GUARD_AREA, in a run
// whose addresses ascend with the command id, putting a team in the slot its
// neighbours fill with an object or a polygon and the same second argument in
// the same misc integer at +0x34. That is a guard command over a team.
//
// AICMD_GUARD_POSITION 0x1E, GUARD_OBJECT 0x1F and GUARD_AREA 0x21 are the
// reference's own indices: BFME dropped the two ALLOW_SURRENDER prisoner
// commands and added one position command after DOCK, and inserting two more
// later (0x19 and this 0x20) realigns the list with the reference exactly from
// GUARD_AREA on.
//
// GuardMode reaches the mangled names of three of these five, so it is declared;
// none of the five reads a value out of it, and the two BFME commands take a
// plain Int in the same position. DamageInfo is opaque here for the same reason
// -- no body in this TU touches the damage block. The reconstructed DamageInfo,
// DamageInfoInput and DamageInfoOutput are in
// AICommandInterfaceAttackCommands.cpp, next to aiGoProne, which does.
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
	AICMD_GUARD_POSITION	= 0x1E,
	AICMD_GUARD_OBJECT		= 0x1F,
	AICMD_BFME_20			= 0x20,
	AICMD_GUARD_AREA		= 0x21,
	AICMD_BFME_44			= 0x44
};

enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum GuardMode {};

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

	AICommandParms(AICommandType cmd, CommandSourceType commandSource);	// ILT 0x00030EA4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType commandSource);
	void aiGuardObject(Object *objToGuard, GuardMode guardMode, CommandSourceType commandSource);
	void aiBfmeCommand20(const Team *team, Int value, CommandSourceType commandSource);
	void aiGuardArea(const PolygonTrigger *areaToGuard, GuardMode guardMode, CommandSourceType commandSource);
	void aiBfmeCommand44(const PolygonTrigger *polygon, Int value,
			CommandSourceType commandSource, const Coord3D *position);
};

void AICommandInterface::aiGuardPosition( const Coord3D *position, GuardMode guardMode, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_GUARD_POSITION, commandSource);
	parms.m_pos = *position;
	parms.m_intValue = guardMode;
	aiDoCommand(&parms);
}

void AICommandInterface::aiGuardObject( Object *objToGuard, GuardMode guardMode, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_GUARD_OBJECT, commandSource);
	parms.m_obj = objToGuard;
	parms.m_intValue = guardMode;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand20(const Team *team, Int value, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_20, commandSource);
	parms.m_team = team;
	parms.m_intValue = value;
	aiDoCommand(&parms);
}

void AICommandInterface::aiGuardArea( const PolygonTrigger *areaToGuard, GuardMode guardMode, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_GUARD_AREA, commandSource);
	parms.m_polygon = areaToGuard;
	parms.m_intValue = guardMode;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand44(const PolygonTrigger *polygon, Int value,
		CommandSourceType commandSource, const Coord3D *position)
{
	AICommandParms parms(AICMD_BFME_44, commandSource);
	parms.m_polygon = polygon;
	parms.m_intValue = value;
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

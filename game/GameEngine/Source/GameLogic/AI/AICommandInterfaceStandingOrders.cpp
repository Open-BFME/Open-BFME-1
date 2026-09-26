// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the four AICommandInterface commands that give a unit a standing
// behaviour instead of a target.
//
//   ?aiGuardTunnelNetwork@  0x00300220, 203 bytes, AICMD 0x37
//   ?aiWander@              0x00300320, 203 bytes, AICMD 0x2B
//   ?aiWanderInPlace@       0x00300420, 192 bytes, AICMD 0x2C
//   ?aiPanic@               0x00300510, 203 bytes, AICMD 0x2D
//
// One run in the retail image, 0x100 to 0xF0 apart, and none of the four names
// an object: two take the waypoint that bounds the wandering, one takes a guard
// mode, and aiWanderInPlace takes nothing at all. That last one is why the run
// is worth reading together -- at 192 bytes it is the AICommandParms block with
// no field store after it, which prices the block itself and makes the other
// three exactly one store (11 bytes) more expensive.
//
// aiWander 0x2B, aiWanderInPlace 0x2C and aiPanic 0x2D are consecutive command
// ids in address order; aiGuardTunnelNetwork 0x37 is not, so retail did not lay
// this TU down in enum order the way it did the object and guard runs.
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
	AICMD_WANDER					= 0x2B,
	AICMD_WANDER_IN_PLACE			= 0x2C,
	AICMD_PANIC						= 0x2D,
	AICMD_GUARD_TUNNEL_NETWORK		= 0x37
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
	AICommandType m_cmd;					// +0x00
	CommandSourceType m_cmdSource;			// +0x04
	Coord3D m_pos;							// +0x08
	Object *m_obj;							// +0x14
	Object *m_otherObj;						// +0x18
	const Team *m_team;						// +0x1C
	_STL::vector<Coord3D> m_coords;			// +0x20
	const Waypoint *m_waypoint;				// +0x2C
	const PolygonTrigger *m_polygon;		// +0x30
	Int m_intValue;							// +0x34
	DamageInfo m_damage;					// +0x38
	const CommandButton *m_commandButton;	// +0x94
	Path *m_path;							// +0x98

	AICommandParms(AICommandType commandType, CommandSourceType commandSource);	// ILT 0x00030EA4
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiGuardTunnelNetwork(Int guardMode, CommandSourceType commandSource);
	void aiWander(const Waypoint *waypoint, CommandSourceType commandSource);
	void aiWanderInPlace(CommandSourceType commandSource);
	void aiPanic(const Waypoint *waypoint, CommandSourceType commandSource);
};

void AICommandInterface::aiGuardTunnelNetwork(Int guardMode, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_GUARD_TUNNEL_NETWORK, commandSource);
	parms.m_intValue = guardMode;
	aiDoCommand(&parms);
}

void AICommandInterface::aiWander(const Waypoint *waypoint, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_WANDER, commandSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

void AICommandInterface::aiWanderInPlace(CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_WANDER_IN_PLACE, commandSource);
	aiDoCommand(&parms);
}

void AICommandInterface::aiPanic(const Waypoint *waypoint, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_PANIC, commandSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

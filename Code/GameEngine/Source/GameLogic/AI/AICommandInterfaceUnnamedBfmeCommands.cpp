// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface commands under these flags whose only
// recovered identity is the command byte pushed into AICommandParms.
//
//   ?bfmeCommand01@     0x00187440, 203 bytes, AICMD 0x01
//   ?bfmeCommand3C@     0x00187760, 203 bytes, AICMD 0x3C
//   ?bfmeCommand52@     0x001FCD40, 203 bytes, AICMD 0x34
//   ?aiBfmeCommand2F@   0x002E9030, 203 bytes, AICMD 0x2F
//   ?aiBfmeCommand3A@   0x002E9130, 192 bytes, AICMD 0x3A
//
// Four of the five are the 203-byte object shape -- construct the block, store
// one pointer at m_obj (+0x14), aiDoCommand at vtable slot 0 -- and differ from
// each other in nothing but the command id. The fifth stores no field at all,
// which is the 192-byte shape aiWanderInPlace also has (see
// AICommandInterfaceStandingOrders.cpp). No caller has been recovered for any
// of them, so the parameter names below are guesses and the AICMD constant is
// the only thing here that is evidence.
//
// The method names are worse than guesses, and having the five in one place is
// the only way to see it: THREE numbering schemes are in play. bfmeCommand01
// and bfmeCommand3C spell the command byte in hex; bfmeCommand52 spells it in
// decimal, so it is command 0x34, and its own enumerator says AICMD_BFME_34
// while its method says 52. The same decimal spelling hides four more elsewhere
// -- aiBfmeCommand39 (position) is 0x27, aiBfmeCommand54 is 0x36,
// aiBfmeCommand36FollowPath is 0x24 and aiBfmeCommand37FollowPath is 0x25.
// And the `ai` prefix is not a signal either: aiBfmeCommand2F and
// aiBfmeCommand3A carry it, bfmeCommand01 and its two siblings do not, and all
// five are the same kind of unnamed body. Read the AICMD constant.
//
// bfmeCommand52's file also pointed at "Rva00187440AICommand.cpp" for its twin.
// That file was renamed away in 60d19aab7e; the twin it meant is bfmeCommand01,
// three declarations up.
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
	AICMD_BFME_01	= 0x01,
	AICMD_BFME_2F	= 0x2F,
	AICMD_BFME_34	= 0x34,		// ?bfmeCommand52@ -- 52 decimal
	AICMD_BFME_3A	= 0x3A,
	AICMD_BFME_3C	= 0x3C
};

enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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

	AICommandParms(AICommandType cmd, CommandSourceType commandSource);	// ILT 0x00030EA4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void bfmeCommand01(Object *object, CommandSourceType commandSource);
	void bfmeCommand3C(Object *object, CommandSourceType commandSource);
	void bfmeCommand52(Object *object, CommandSourceType commandSource);
	void aiBfmeCommand2F(Object *object, CommandSourceType commandSource);
	void aiBfmeCommand3A(CommandSourceType commandSource);
};

void AICommandInterface::bfmeCommand01(Object *object, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_01, commandSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::bfmeCommand3C(Object *object, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_3C, commandSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::bfmeCommand52(Object *object, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_34, commandSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand2F(Object *object, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_2F, commandSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand3A(CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_3A, commandSource);
	aiDoCommand(&parms);
}

// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface commands whose whole payload is one object.
//
//   ?aiRepair@              0x00153D10, 203 bytes, AICMD 0x13
//   ?aiResumeConstruction@  0x00153E10, 203 bytes, AICMD 0x14
//   ?aiGetHealed@           0x00153F10, 203 bytes, AICMD 0x15
//   ?aiGetRepaired@         0x00154010, 203 bytes, AICMD 0x16
//   ?aiDock@                0x00154110, 203 bytes, AICMD 0x18
//   ?aiExit@                0x00154330, 203 bytes, AICMD 0x1A
//
// Six bodies of the reference's inline command builder, emitted out of line and
// laid down in command order 0x100 apart: build the parameter block, put the
// object in the object slot at +0x14, then aiDoCommand at vtable slot 0. Nothing
// separates any two of them but the command id. The gaps in the address run are
// the two commands of the same stretch that are not object commands --
// aiBfmeCommand19 (0x19) takes a position, and the missing 0x17 is aiEnter,
// which retail emitted far away at 0x000D89C0 under different flags.
//
// Almost all 203 bytes are the block itself. AICommandParms is the reference's
// struct exactly, which the frame proves: 0x9C of locals, the object at +0x14,
// and the coordinate vector at +0x20 -- the only member with anything to tear
// down, which is why the tail is a lone STLport deallocation, dividing the
// capacity span by the twelve bytes of a Coord3D and choosing the node allocator
// or operator delete on the 0x80 boundary. The DamageInfo at +0x38 is the same
// 0x5C block TunnelTracker_healObject.cpp measured, and it lands
// m_commandButton and m_path on +0x94 and +0x98. It is opaque here because no
// body in this TU touches it; the reconstructed classes are in
// AICommandInterfaceAttackCommands.cpp, next to aiGoProne, which does.
//
// AICMD_REPAIR 0x13 through AICMD_EXIT 0x1A are BFME's list, which is the
// reference's with the two ALLOW_SURRENDER prisoner commands dropped and one
// position command added after DOCK. That carries ATTACK_OBJECT 0x0B, ATTACKMOVE
// 0x0F and HUNT 0x12 through unchanged while GET_HEALED lands at 0x15, ENTER at
// 0x17 and EVACUATE at 0x1B.
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
	AICMD_REPAIR				= 0x13,
	AICMD_RESUME_CONSTRUCTION	= 0x14,
	AICMD_GET_HEALED			= 0x15,
	AICMD_GET_REPAIRED			= 0x16,
	AICMD_DOCK					= 0x18,
	AICMD_EXIT					= 0x1A
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

	void aiRepair(Object *object, CommandSourceType cmdSource);
	void aiResumeConstruction(Object *object, CommandSourceType cmdSource);
	void aiGetHealed(Object *healDepot, CommandSourceType cmdSource);
	void aiGetRepaired(Object *repairDepot, CommandSourceType cmdSource);
	void aiDock(Object *object, CommandSourceType cmdSource);
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
};

void AICommandInterface::aiRepair( Object *object, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_REPAIR, cmdSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::aiResumeConstruction( Object *object, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_RESUME_CONSTRUCTION, cmdSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::aiGetHealed( Object *healDepot, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_GET_HEALED, cmdSource);
	parms.m_obj = healDepot;
	aiDoCommand(&parms);
}

void AICommandInterface::aiGetRepaired( Object *repairDepot, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_GET_REPAIRED, cmdSource);
	parms.m_obj = repairDepot;
	aiDoCommand(&parms);
}

void AICommandInterface::aiDock( Object *object, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_DOCK, cmdSource);
	parms.m_obj = object;
	aiDoCommand(&parms);
}

void AICommandInterface::aiExit( Object *objectToExit, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_EXIT, cmdSource);
	parms.m_obj = objectToExit;
	aiDoCommand(&parms);
}

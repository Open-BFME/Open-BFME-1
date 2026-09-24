// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface commands whose whole payload is one
// position, written into the coordinate slot at +0x08.
//
//   ?aiBfmeCommand54@              0x000FFB80, 219 bytes, AICMD 0x36
//   ?aiTightenToPosition@          0x001527C0, 219 bytes, AICMD 0x02
//   ?aiMoveToAndEvacuate@          0x001528E0, 219 bytes, AICMD 0x03
//   ?aiMoveToAndEvacuateAndExit@   0x00152A00, 219 bytes, AICMD 0x04
//   ?aiBfmeCommand35@              0x00153480, 219 bytes, AICMD 0x35
//   ?aiBfmeCommand19@              0x00154210, 219 bytes, AICMD 0x19
//   ?aiBfmeCommand38@              0x00205200, 219 bytes, AICMD 0x38
//   ?aiBfmeCommand41@              0x00205320, 219 bytes, AICMD 0x41
//   ?aiBfmeCommand40@              0x0025D270, 219 bytes, AICMD 0x40
//   ?aiBfmeCommand39@              0x00266A30, 219 bytes, AICMD 0x27
//
// Ten copies of one body at ten addresses. Every one is 219 bytes: the
// AICommandParms block (0x9C of locals, the coordinate vector at +0x20 the only
// member with anything to tear down) plus the three-float copy into m_pos that
// makes them 16 bytes longer than their object-command siblings. The command id
// is the only thing that differs between any two of them.
//
// Three of the ten have real names -- TIGHTEN_TO_POSITION 0x02,
// MOVE_TO_POSITION_AND_EVACUATE 0x03 and _AND_EXIT 0x04 come straight from the
// reference's list. The other seven are still address-derived, and the naming
// of that family drifted: MOST aiBfmeCommandNN methods spell NN as the hex
// digits of the command byte (0x19, 0x35, 0x38, 0x40, 0x41 here; 0x20, 0x33,
// 0x44, 0x45 elsewhere), but FOUR spell NN as its decimal value --
// aiBfmeCommand39 here is 0x27, aiBfmeCommand54 is 0x36, and
// aiBfmeCommand36FollowPath and aiBfmeCommand37FollowPath (in
// AICommandInterfaceFollowPathCommands.cpp) are 0x24 and 0x25. So the name
// "aiBfmeCommand36" belongs to command 0x24 while command 0x36 answers to
// "aiBfmeCommand54", and aiBfmeCommand39 is an overload pair covering two
// unrelated commands: this one at 0x27 taking a position, and the object-taking
// one at 0x001536B0 which really is 0x39. The mangled names are pinned, so read
// the AICMD constant, never the method name.
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
	AICMD_TIGHTEN_TO_POSITION							= 0x02,
	AICMD_MOVE_TO_POSITION_AND_EVACUATE					= 0x03,
	AICMD_MOVE_TO_POSITION_AND_EVACUATE_AND_EXIT		= 0x04,
	AICMD_BFME_19										= 0x19,
	AICMD_BFME_39										= 0x27,
	AICMD_BFME_35										= 0x35,
	AICMD_BFME_54										= 0x36,
	AICMD_BFME_38										= 0x38,
	AICMD_BFME_40										= 0x40,
	AICMD_BFME_41										= 0x41
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
	CommandSourceType				m_commandSource;		// +0x04
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

	void aiBfmeCommand54(const Coord3D *position, CommandSourceType commandSource);
	void aiTightenToPosition(const Coord3D *position, CommandSourceType commandSource);
	void aiMoveToAndEvacuate(const Coord3D *position, CommandSourceType commandSource);
	void aiMoveToAndEvacuateAndExit(const Coord3D *position, CommandSourceType commandSource);
	void aiBfmeCommand35(const Coord3D *position, CommandSourceType commandSource);
	void aiBfmeCommand19(const Coord3D *position, CommandSourceType commandSource);
	void aiBfmeCommand38(const Coord3D *position, CommandSourceType commandSource);
	void aiBfmeCommand41(const Coord3D *position, CommandSourceType commandSource);
	void aiBfmeCommand40(const Coord3D *position, CommandSourceType commandSource);
	void aiBfmeCommand39(const Coord3D *position, CommandSourceType commandSource);
};

void AICommandInterface::aiBfmeCommand54(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_54, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiTightenToPosition( const Coord3D *position, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_TIGHTEN_TO_POSITION, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiMoveToAndEvacuate( const Coord3D *position, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_MOVE_TO_POSITION_AND_EVACUATE, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiMoveToAndEvacuateAndExit( const Coord3D *position, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_MOVE_TO_POSITION_AND_EVACUATE_AND_EXIT, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand35(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_35, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand19(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_19, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand38(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_38, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand41(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_41, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand40(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_40, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiBfmeCommand39(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_BFME_39, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

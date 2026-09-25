// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the three AICommandInterface commands that point a unit at
// something.
//
//   ?aiFacePosition@   0x002A7F40, 219 bytes, AICMD 0x47
//   ?aiMoveToObject@   0x002A8060, 203 bytes, AICMD 0x48
//   ?aiFaceObject@     0x002A8160, 203 bytes, AICMD 0x26
//
// One run in the retail image, 0x120 then 0x100 apart. aiFacePosition is the
// 219-byte position shape (the three-float copy into m_pos at +0x08); the other
// two are the 203-byte object shape (one store into m_obj at +0x14).
//
// Three files each hedged its command id with "in this translation unit",
// because on its own no one body can say whether 0x47 and 0x26 belong to the
// same numbering. Together they still cannot -- but the run makes the shape of
// the question plain: aiFacePosition 0x47 and aiMoveToObject 0x48 are adjacent
// ids in address order, and aiFaceObject 0x26 sits immediately after them at an
// id 0x21 lower. In the reference the two face commands are neighbours; in BFME
// they are not, and that is a fact about BFME's list, not about these bodies.
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
	AICMD_FACE_OBJECT		= 0x26,
	AICMD_FACE_POSITION		= 0x47,
	AICMD_MOVE_TO_OBJECT	= 0x48
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

	AICommandParms(AICommandType commandType, CommandSourceType commandSource);	// ILT 0x00030EA4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiFacePosition(const Coord3D *position, CommandSourceType commandSource);
	void aiMoveToObject(Object *target, CommandSourceType commandSource);
	void aiFaceObject(Object *target, CommandSourceType commandSource);
};

void AICommandInterface::aiFacePosition(const Coord3D *position, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_FACE_POSITION, commandSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiMoveToObject(Object *target, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_MOVE_TO_OBJECT, commandSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

void AICommandInterface::aiFaceObject(Object *target, CommandSourceType commandSource)
{
	AICommandParms parms(AICMD_FACE_OBJECT, commandSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the AICommandInterface commands that pick a victim, and the
// AICommandParms constructor every one of them calls.
//
//   ?aiAttackObject@                  0x001535A0, 214 bytes
//   ?aiForceAttackObject@             0x001537B0, 214 bytes
//   ?aiAttackTeam@                    0x001538C0, 214 bytes
//   ?aiAttackPosition@                0x001539D0, 230 bytes
//   ?aiAttackArea@                    0x00153C10, 203 bytes
//   ?aiGoProne@                       0x00154430, 222 bytes
//   ??0AICommandParms@                0x00185910
//   ?aiAttackFollowWaypointPath@      0x00187540, 214 bytes
//   ?aiAttackFollowWaypointPathAsTeam@0x00187650, 214 bytes
//
// Every one is one of the reference's inline command builders, emitted out of
// line here: construct the parameter block, drop the victim into whichever slot
// names it, then aiDoCommand at vtable slot 0. Almost all of the 203 bytes are
// the block itself, and the frame proves its shape -- 0x9C of locals, the object
// at +0x14, the coordinate vector at +0x20 (the only member with anything to
// tear down) and the misc integer at +0x34.
//
// BFME's command list is the reference's with the two ALLOW_SURRENDER prisoner
// commands dropped and one position command added after DOCK. That carries
// ATTACK_OBJECT 0x0B, ATTACKMOVE 0x0F and HUNT 0x12 through unchanged while
// GET_HEALED lands at 0x15, ENTER at 0x17 and EVACUATE at 0x1B; two commands
// inserted later (0x19 and 0x20) realign the list with the reference exactly
// from GUARD_AREA 0x21 on.
//
// aiGoProne is the only member of the family that carries a payload bigger than
// a pointer, and its extra 19 bytes are the inlined DamageInfo::operator=
// already landed at 0x00150620: Input::operator= at ILT 0x0000617C on this+4,
// then the three output fields written one at a time. That body used to model
// DamageInfo as an opaque char[4] followed by a 0x4c-byte input and an output
// starting at +0x50; the real classes below put a vptr at the head of each --
// DamageInfo at +0x00, its input at +0x04, its output at +0x4C -- which lands
// the three named output fields on exactly the same +0x50/+0x54/+0x58 the
// opaque account measured, and totals the 0x5C the parameter block reserves.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;

	void zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

enum AICommandType
{
	AICMD_ATTACK_OBJECT							= 0x0B,
	AICMD_FORCE_ATTACK_OBJECT					= 0x0C,
	AICMD_ATTACK_TEAM							= 0x0D,
	AICMD_ATTACK_POSITION						= 0x0E,
	AICMD_ATTACKFOLLOW_WAYPOINT_PATH			= 0x10,
	AICMD_ATTACKFOLLOW_WAYPOINT_PATH_AS_TEAM	= 0x11,
	AICMD_GO_PRONE								= 0x1D,
	AICMD_ATTACK_AREA							= 0x23
};

enum CommandSourceType { CMD_FROM_PLAYER = 0 };

enum DamageType
{
	DAMAGE_EXPLOSION = 0,
	DAMAGE_PARTICLE_BEAM = 0x16,
	DAMAGE_UNRESISTABLE = 0x0B
};

enum DeathType { DEATH_NORMAL = 0, DEATH_BFME_DEFAULT = 0x0F };
typedef Int ObjectID;
const ObjectID INVALID_ID = 0;

class Snapshot
{
protected:
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

struct DamageInfoInputTail
{
	Int m_z0;
	Int m_z1;
	Int m_z2;
	Int m_z3;
	Int m_z4;
	Int m_z5;
	Real m_shockWaveTaperOff;

	void initialize()
	{
		m_z0 = 0;
		m_z1 = 0;
		m_z2 = 0;
		m_z3 = 0;
		m_z4 = 0;
		m_z5 = 0;
		m_shockWaveTaperOff = 1.0f;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput : public Snapshot
{
public:
	__forceinline DamageInfoInput()
	{
		m_sourceID = INVALID_ID;
		m_unk08 = 0;
		m_amount = 0;
		m_fxOverride = 0;
		m_kill = false;
		m_shock0 = 0;
		m_shock1 = 0;
		m_shock2 = 0;
		m_damageType = DAMAGE_PARTICLE_BEAM;
		m_deathType = DEATH_BFME_DEFAULT;
		m_unk59 = true;
		m_tail.initialize();
	}

	DamageInfoInput &operator=(const DamageInfoInput &other);	// ILT 0x0000617C

	ObjectID m_sourceID;
	unsigned short m_unk08;
	unsigned short m_pad0A;
	DamageType m_damageType;
	DeathType m_deathType;
	Real m_amount;
	Int m_fxOverride;
	Bool m_kill;
	Bool m_unk59;
	unsigned short m_pad1E;
	Int m_shock0;
	Int m_shock1;
	Int m_shock2;
	DamageInfoInputTail m_tail;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput : public Snapshot
{
public:
	__forceinline DamageInfoOutput()
	{
		m_actualDamageDealt = 0;
		m_actualDamageClipped = 0;
		m_noEffect = false;
	}

	Real m_actualDamageDealt;				// DamageInfo+0x50
	Real m_actualDamageClipped;				// DamageInfo+0x54
	Bool m_noEffect;						// DamageInfo+0x58
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo : public Snapshot
{
public:
	__forceinline DamageInfo() {}

	DamageInfoInput in;						// +0x04
	DamageInfoOutput out;					// +0x4C
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

	AICommandParms(AICommandType commandType, CommandSourceType commandSource);	// ILT 0x00030EA4
};

// ??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z
AICommandParms::AICommandParms(AICommandType commandType, CommandSourceType commandSource)
	: m_cmd(commandType),
	  m_cmdSource(commandSource),
	  m_obj(0),
	  m_otherObj(0),
	  m_team(0),
	  m_waypoint(0),
	  m_polygon(0),
	  m_intValue(0),
	  m_commandButton(0),
	  m_path(0)
{
	m_pos.zero();
	m_coords.clear();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;	// slot 0, vtable+0x00

	void aiAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType commandSource);
	void aiForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType commandSource);
	void aiAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType commandSource);
	void aiAttackPosition(const Coord3D *position, Int maxShotsToFire, CommandSourceType commandSource);
	void aiAttackArea(const PolygonTrigger *attackArea, CommandSourceType commandSource);
	void aiGoProne(const DamageInfo *damageInfo, CommandSourceType commandSource);
	void aiAttackFollowWaypointPath(const Waypoint *waypoint, Int maxShotsToFire, CommandSourceType commandSource);
	void aiAttackFollowWaypointPathAsTeam(const Waypoint *waypoint, Int maxShotsToFire, CommandSourceType commandSource);
};

void AICommandInterface::aiAttackObject( Object *victim, Int maxShotsToFire, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_ATTACK_OBJECT, commandSource);
	parms.m_obj = victim;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

void AICommandInterface::aiForceAttackObject( Object *victim, Int maxShotsToFire, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_FORCE_ATTACK_OBJECT, commandSource);
	parms.m_obj = victim;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

void AICommandInterface::aiAttackTeam( const Team *team, Int maxShotsToFire, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_ATTACK_TEAM, commandSource);
	parms.m_team = team;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

void AICommandInterface::aiAttackPosition( const Coord3D *position, Int maxShotsToFire, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_ATTACK_POSITION, commandSource);
	parms.m_pos = *position;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

void AICommandInterface::aiAttackArea( const PolygonTrigger *attackArea, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_ATTACK_AREA, commandSource);
	parms.m_polygon = attackArea;
	aiDoCommand(&parms);
}

void AICommandInterface::aiGoProne( const DamageInfo *damageInfo, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_GO_PRONE, commandSource);
	parms.m_damage.in = damageInfo->in;
	parms.m_damage.out.m_actualDamageDealt = damageInfo->out.m_actualDamageDealt;
	parms.m_damage.out.m_actualDamageClipped = damageInfo->out.m_actualDamageClipped;
	parms.m_damage.out.m_noEffect = damageInfo->out.m_noEffect;
	aiDoCommand(&parms);
}

void AICommandInterface::aiAttackFollowWaypointPath( const Waypoint *waypoint, Int maxShotsToFire, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_ATTACKFOLLOW_WAYPOINT_PATH, commandSource);
	parms.m_waypoint = waypoint;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

void AICommandInterface::aiAttackFollowWaypointPathAsTeam( const Waypoint *waypoint, Int maxShotsToFire, CommandSourceType commandSource )
{
	AICommandParms parms(AICMD_ATTACKFOLLOW_WAYPOINT_PATH_AS_TEAM, commandSource);
	parms.m_waypoint = waypoint;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

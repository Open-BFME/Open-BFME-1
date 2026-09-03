// ??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z
// partial score=0.82 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandParms::AICommandParms, retail 0x00185910, 211 bytes.
//
// Named by 27 byte-true AICommandInterface call sites. Zero Hour's constructor
// (AIStates.cpp) with the BFME DamageInfo layout store/reconstitute already
// measured: input block at +4, output at +0x50 of DamageInfo, parms damage at
// +0x38.
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
class ThingTemplate;

enum AICommandType { AICMD_NONE = 0 };
enum CommandSourceType { CMD_FROM_AI = 0 };
enum DamageType
{
	DAMAGE_EXPLOSION = 0,
	DAMAGE_PARTICLE_BEAM = 0x16,
	DAMAGE_UNRESISTABLE = 0x0B
};
enum DeathType { DEATH_NORMAL = 0, DEATH_BFME_DEFAULT = 0x0F };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
typedef Int ObjectID;
typedef UnsignedInt PlayerMaskType;
const ObjectID INVALID_ID = 0;

class Snapshot
{
protected:
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

class DamageInfoInput : public Snapshot
{
public:
	DamageInfoInput()
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
		m_z0 = 0;
		m_z1 = 0;
		m_z2 = 0;
		m_z3 = 0;
		m_z4 = 0;
		m_z5 = 0;
		m_shockWaveTaperOff = 1.0f;
	}

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
	Int m_z0;
	Int m_z1;
	Int m_z2;
	Int m_z3;
	Int m_z4;
	Int m_z5;
	Real m_shockWaveTaperOff;
};

class DamageInfoOutput : public Snapshot
{
public:
	DamageInfoOutput()
	{
		m_actualDamageDealt = 0;
		m_actualDamageClipped = 0;
		m_noEffect = false;
	}

	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

class DamageInfo : public Snapshot
{
public:
	__forceinline DamageInfo() {}
	DamageInfoInput in;
	DamageInfoOutput out;
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

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
};

// ??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z
AICommandParms::AICommandParms(AICommandType cmd, CommandSourceType cmdSource) :
	m_cmd(cmd),
	m_cmdSource(cmdSource),
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

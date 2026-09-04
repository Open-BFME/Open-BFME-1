// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiGoProne, retail 0x00154430, 222 bytes.
//
// Same command-builder family as aiExit (0x00154330, AICMD 0x1A) and
// aiGuardPosition (0x00154550, AICMD 0x1E). AICMD_GO_PRONE is 0x1D, the
// remaining slot between Evacuate/Exit and GuardPosition after BFME dropped
// the two ALLOW_SURRENDER prisoner commands.
//
// The extra 19 bytes over the 203B object-slot siblings are the inlined
// DamageInfo::operator= already landed at 0x00150620: Input::operator= at
// ILT 0x0000617C on this+4, then the three output fields at +0x50/+0x54/+0x58.
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

enum AICommandType { AICMD_GO_PRONE = 0x1D };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput
{
public:
	DamageInfoInput &operator=(const DamageInfoInput &other);	// ILT 0x0000617C

private:
	char m_unreconstructed_00[0x4c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput
{
public:
	Real m_actualDamageDealt;				// DamageInfo+0x50
	Real m_actualDamageClipped;				// DamageInfo+0x54
	Bool m_noEffect;						// DamageInfo+0x58
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	char m_unreconstructed_00[4];
	DamageInfoInput in;						// +0x04
	DamageInfoOutput out;					// +0x50
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

	void aiGoProne(const DamageInfo *damageInfo, CommandSourceType cmdSource);
};

void AICommandInterface::aiGoProne(const DamageInfo *damageInfo, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_GO_PRONE, cmdSource);
	parms.m_damage.in = damageInfo->in;
	parms.m_damage.out.m_actualDamageDealt = damageInfo->out.m_actualDamageDealt;
	parms.m_damage.out.m_actualDamageClipped = damageInfo->out.m_actualDamageClipped;
	parms.m_damage.out.m_noEffect = damageInfo->out.m_noEffect;
	aiDoCommand(&parms);
}

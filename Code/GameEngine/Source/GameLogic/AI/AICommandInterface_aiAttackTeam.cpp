// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiAttackTeam, retail 0x001538C0, 214 bytes.
//
// One of the reference's inline command builders, out of line here: build the
// parameter block, put the team in the team slot and the shot limit in the misc integer, then
// aiDoCommand at vtable slot 0 -- the frame
// AICommandInterface_aiAttackObject.cpp measured.
//
// AICMD_ATTACK_TEAM is 0x0D. BFME's command list is the reference's with the
// two ALLOW_SURRENDER prisoner commands dropped and one position command added
// after DOCK, which is what carries ATTACK_OBJECT 0x0B, ATTACKMOVE 0x0F and
// HUNT 0x12 through unchanged while GET_HEALED lands at 0x15, ENTER at 0x17 and
// EVACUATE at 0x1B -- all five already pinned by this family.
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

enum AICommandType { AICMD_ATTACK_TEAM = 0x0D };
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

	void aiAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource);
};

void AICommandInterface::aiAttackTeam( const Team *team, Int maxShotsToFire, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_ATTACK_TEAM, cmdSource);
	parms.m_team = team;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface path-command, retail 0x00153360, 231 bytes.
//
// Byte-identical twin of aiBfmeCommand36FollowPath
// (AICommandInterface_aiBfmeCommand36FollowPath.cpp, retail 0x00153240,
// 231 bytes): same build-parms/copy-path/set-object/set-object/aiDoCommand
// shape, only the AICMD constant differs (0x25 here, not 0x24). The second
// object pointer lands via a raw cast at &parms.m_pos.x -- that's the
// retail frame position for it, not the m_otherObj field the struct
// comment would suggest. Address-derived name pending the real command
// enumerator/caller.
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

enum AICommandType { AICMD_BFME_37 = 0x25 };
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

	void aiBfmeCommand37FollowPath(const _STL::vector<Coord3D> *path, Object *obj, Object *otherObj, CommandSourceType cmdSource);
};

void AICommandInterface::aiBfmeCommand37FollowPath( const _STL::vector<Coord3D> *path, Object *obj, Object *otherObj, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_BFME_37, cmdSource);
	parms.m_coords = *path;
	parms.m_obj = obj;
	*(Object **)&parms.m_pos.x = otherObj;
	aiDoCommand(&parms);
}

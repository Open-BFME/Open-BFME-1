// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiGetHealed, retail 0x00153F10, 203 bytes.
//
// The reference's three lines, out of line here rather than inlined in the
// header: build the command block, put the heal depot in it, and hand it to
// aiDoCommand at vtable slot 0.
//
// Almost all 203 bytes are the block itself. AICommandParms is the reference's
// struct exactly, which the frame proves: 0x9C of locals, the object at +0x14
// where the depot is stored, and the coordinate vector at +0x20 -- the only
// member with anything to tear down, which is why the tail is a lone STLport
// deallocation, dividing the capacity span by the twelve bytes of a Coord3D
// and choosing the node allocator or operator delete on the 0x80 boundary. The
// DamageInfo at +0x38 is the same 0x5C block TunnelTracker_healObject.cpp
// measured, and it lands m_commandButton and m_path on +0x94 and +0x98.
//
// AICMD_GET_HEALED is 0x15 in BFME's command list.
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

enum AICommandType { AICMD_GET_HEALED = 0x15 };
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

	void aiGetHealed(Object *healDepot, CommandSourceType cmdSource);
};

void AICommandInterface::aiGetHealed( Object *healDepot, CommandSourceType cmdSource )
{
	AICommandParms parms(AICMD_GET_HEALED, cmdSource);
	parms.m_obj = healDepot;
	aiDoCommand(&parms);
}

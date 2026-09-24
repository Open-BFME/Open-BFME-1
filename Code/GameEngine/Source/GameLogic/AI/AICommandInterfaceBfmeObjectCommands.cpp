// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the exceptions-on AICommandInterface commands whose whole payload
// is one object and whose only recovered identity is the command byte.
//
//   ?aiBfmeCommand42@        0x00152B20, 203 bytes, AICMD 0x42
//   ?aiBfmeCommand45@        0x00152C20, 203 bytes, AICMD 0x45
//   ?aiBfmeCommand39@        0x001536B0, 203 bytes, AICMD 0x39
//   ?aiBfmeObjectCommand3D@  0x00240680, 203 bytes, AICMD 0x3D
//   ?aiBfmeObjectCommand3E@  0x00240780, 203 bytes, AICMD 0x3E
//   ?aiBfmeCommand2E@        0x00251320, 203 bytes, AICMD 0x2E
//   ?aiBfmeCommand63@        0x0025D170, 203 bytes, AICMD 0x3F
//
// Seven copies of one body: construct AICommandParms with the command id and
// the caller's command source, drop the object into m_obj at +0x14, hand the
// address to the pure virtual aiDoCommand, then run the inlined AICommandParms
// destructor -- which is nothing but the std::vector<Coord3D> at +0x20, so the
// epilogue is the STLport size dispatch between operator delete and the node
// allocator. That is the whole 203 bytes; nothing but the command id separates
// any two of them.
//
// The 0x3D and 0x3E pair were emitted into HordeContain's translation unit,
// which is the only placement evidence any of the seven has. No caller is
// recovered for the rest, so the parameter names are guesses and the AICMD
// constant is the only evidence here.
//
// Three naming conventions are visible in the seven names above, and one of
// them lies: aiBfmeCommand63 is command 0x3F, because 63 is the DECIMAL value
// of that byte. aiBfmeObjectCommand3D and 3E spell theirs in hex, as do the
// other four. The same decimal spelling hides four more elsewhere in the class
// -- aiBfmeCommand39 (the position overload) is 0x27, aiBfmeCommand54 is 0x36,
// aiBfmeCommand36FollowPath is 0x24 and aiBfmeCommand37FollowPath is 0x25 --
// and note that the aiBfmeCommand39 in THIS file is the object overload, which
// really is 0x39. Read the AICMD constant, never the method name.
//
// DamageInfo at +0x38 is opaque here because no body in this TU touches it; the
// reconstructed classes are in AICommandInterfaceAttackCommands.cpp, next to
// aiGoProne, which does. std::vector is STLport's own vector -- the same
// _STL::vector the /DWIN32 TUs spell explicitly.
#include <vector>

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_BFME_2E = 0x2E,
	AICMD_BFME_39 = 0x39,
	AICMD_BFME_3D = 0x3D,
	AICMD_BFME_3E = 0x3E,
	AICMD_BFME_3F = 0x3F,			// ?aiBfmeCommand63@ -- 63 decimal
	AICMD_BFME_42 = 0x42,
	AICMD_BFME_45 = 0x45
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType commandSource );	// ILT 0x00030EA4

	AICommandType m_cmd;					// +0x00
	CommandSourceType m_cmdSource;			// +0x04
	Coord3D m_pos;							// +0x08
	Object *m_obj;							// +0x14
	Object *m_otherObj;						// +0x18
	const Team *m_team;						// +0x1C
	std::vector<Coord3D> m_coords;			// +0x20
	const Waypoint *m_waypoint;				// +0x2C
	const PolygonTrigger *m_polygon;		// +0x30
	int m_intValue;							// +0x34
	DamageInfo m_damage;					// +0x38
	const CommandButton *m_commandButton;	// +0x94
	Path *m_path;							// +0x98
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;

	void aiBfmeCommand42( Object *object, CommandSourceType commandSource );
	void aiBfmeCommand45( Object *object, CommandSourceType commandSource );
	void aiBfmeCommand39( Object *object, CommandSourceType commandSource );
	void aiBfmeObjectCommand3D( Object *object, CommandSourceType commandSource );
	void aiBfmeObjectCommand3E( Object *object, CommandSourceType commandSource );
	void aiBfmeCommand2E( Object *object, CommandSourceType commandSource );
	void aiBfmeCommand63( Object *object, CommandSourceType commandSource );
};

void AICommandInterface::aiBfmeCommand42( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_42, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeCommand45( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_45, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeCommand39( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_39, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeObjectCommand3D( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_3D, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeObjectCommand3E( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_3E, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeCommand2E( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_2E, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeCommand63( Object *object, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_BFME_3F, commandSource );
	parms.m_obj = object;
	aiDoCommand( &parms );
}

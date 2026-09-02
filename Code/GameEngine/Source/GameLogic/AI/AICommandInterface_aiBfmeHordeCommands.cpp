// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: two AICommandInterface object commands emitted into HordeContain's
// translation unit, retail 0x00240680 and 0x00240780.
//
// Same shape as the rest of the converted family (aiEnter, aiDock, aiExit, ...):
// construct AICommandParms with the command id and the caller's command source,
// drop the object into m_obj, hand the address to the pure virtual aiDoCommand,
// then run the inlined AICommandParms destructor -- which is nothing but the
// std::vector<Coord3D> member at 0x20, so the epilogue is the STLport size
// dispatch between operator delete and the node allocator.
//
// The two commands are BFME additions past the Zero Hour enum, so only their
// numeric ids (0x3d and 0x3e) are recoverable; they are named for those.

#include <vector>

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_BFME_OBJECT_3D = 0x3d,
	AICMD_BFME_OBJECT_3E = 0x3e
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType cmdSource );

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	void *m_team;
	std::vector<Coord3D> m_coords;
	char m_remaining[0x9c - 0x2c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;
	void aiBfmeObjectCommand3D( Object *obj, CommandSourceType cmdSource );
	void aiBfmeObjectCommand3E( Object *obj, CommandSourceType cmdSource );
};

void AICommandInterface::aiBfmeObjectCommand3D( Object *obj, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_BFME_OBJECT_3D, cmdSource );
	parms.m_obj = obj;
	aiDoCommand( &parms );
}

void AICommandInterface::aiBfmeObjectCommand3E( Object *obj, CommandSourceType cmdSource )
{
	AICommandParms parms( AICMD_BFME_OBJECT_3E, cmdSource );
	parms.m_obj = obj;
	aiDoCommand( &parms );
}

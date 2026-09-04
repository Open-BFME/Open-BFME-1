// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiBfmeCommand45, retail 0x00152C20, 203 bytes.
//
// Same 203-byte object-command shape as aiEnter / aiDock / aiExit. AICMD 0x45
// with the object in m_obj. Named by the matched first-member group wrapper
// at 0x00156A90 (ILT 0x00019628).

#include <vector>

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_BFME_45 = 0x45
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class AICommandParms
{
public:
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	void *m_team;
	std::vector<Coord3D> m_coords;
	char m_remaining[0x9c - 0x2c];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiBfmeCommand45(Object *obj, CommandSourceType cmdSource);
};

void AICommandInterface::aiBfmeCommand45(Object *obj, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_45, cmdSource);
	parms.m_obj = obj;
	aiDoCommand(&parms);
}

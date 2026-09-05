// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Near-twin of AICommandInterface::aiBfmeCommand45 (twin 0x00152C20,
// AICommandInterface_aiBfmeCommand45.cpp): identical single-Object command
// wrapper, but the AICommandType immediate is 0x3f instead of 0x45.

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
	AICMD_BFME_3F = 0x3f
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
	void aiBfmeCommand63(Object *obj, CommandSourceType cmdSource);
};

// @?aiBfmeCommand63@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z 0x0025D170
void AICommandInterface::aiBfmeCommand63(Object *obj, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_3F, cmdSource);
	parms.m_obj = obj;
	aiDoCommand(&parms);
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandInterface::aiBfmeCommand42, retail 0x00152B20, 203 bytes.
//
// 203B twin of aiBfmeCommand45 (AICommandInterface_aiBfmeCommand45.cpp,
// retail 0x00152C20): identical object-command shape, only the AICMD
// constant differs (0x42 here, not 0x45). Address-derived name pending the
// real command enumerator.

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
	AICMD_BFME_42 = 0x42
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
	void aiBfmeCommand42(Object *obj, CommandSourceType cmdSource);
};

void AICommandInterface::aiBfmeCommand42(Object *obj, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_42, cmdSource);
	parms.m_obj = obj;
	aiDoCommand(&parms);
}

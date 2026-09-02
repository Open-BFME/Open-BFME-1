class Object;

enum CommandSourceType
{
	COMMAND_SOURCE_SCRIPT = 2
};

class AICommandInterface
{
public:
	void aiAttackObject(Object *object, int mode, CommandSourceType source);
};

class BfmeActiveState
{
public:
	void bfmeSet(int value, int enabled);

	char m_bfmeFields[0x204];
	struct BfmeAIHolder *m_bfmeAI;
};

struct BfmeAIHolder
{
	char m_bfmeFields[0x20];
	AICommandInterface m_bfmeCommands;
};

struct BfmeAttackForwardInfo
{
	char m_bfmeFields[8];
	int m_bfmeMode;
	int m_bfmeValue;
	void *m_bfmeFirst;
	void *m_bfmeSecond;
};

class Gen_0027FED0
{
public:
	void bfmeRun(void *context, Object *object);

private:
	void bfmeForward(void *record, void *first, void *second);

	char m_bfmeFields[4];
	BfmeAttackForwardInfo *m_bfmeInfo;
	BfmeActiveState *m_bfmeState;
};

// ?bfmeRun@Gen_0027FED0@@QAEXPAXPAVObject@@@Z
void Gen_0027FED0::bfmeRun(void *context, Object *object)
{
	BfmeActiveState *state = m_bfmeState;
	BfmeAttackForwardInfo *info = m_bfmeInfo;

	if (state->m_bfmeAI != 0) {
		state->bfmeSet(info->m_bfmeValue, 1);
		state->m_bfmeAI->m_bfmeCommands.aiAttackObject(
			object, info->m_bfmeMode, COMMAND_SOURCE_SCRIPT);

		if (info->m_bfmeFirst != 0)
			bfmeForward(info->m_bfmeFirst, context, state);

		if (info->m_bfmeSecond != 0)
			bfmeForward(info->m_bfmeSecond, state, object);
	}
}

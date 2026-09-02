// ?d_00287670@@YAXXZ
// partial score=0.99 date=2026-09-03
class Object;

class GameLogicFrameSlice
{
public:
	Object *bfmeFind(int id);
};

extern GameLogicFrameSlice *TheGameLogic;

class BfmeResettable
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void bfmeReset(int value);
};

enum CommandSourceType
{
	COMMAND_SOURCE_SCRIPT = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

struct BfmeAIHolder
{
	char m_bfmeFields[0x20];
	AICommandInterface m_bfmeCommands;
};

enum ModelConditionFlagType
{
	MODEL_CONDITION_RESET = 0x49
};

class Object
{
public:
	void bfmePrepare(int value);
	void clearModelConditionState(ModelConditionFlagType condition);
	void bfmeFinish(int value);

	char m_bfmeFields[0x98];
	unsigned char m_bfmeConditionB;
	char m_bfme99[0x16B];
	BfmeAIHolder *m_bfmeAI;
	char m_bfme208[0x13C];
	unsigned char m_bfmeConditionA;
};

class Gen_00287670
{
public:
	int bfmeUpdate(void);

private:
	char m_bfmeFields[0x10];
	BfmeResettable m_bfmeResettable;
	char m_bfme14[4];
	int m_bfmeObjectID;
};

// ?bfmeUpdate@Gen_00287670@@QAEHXZ
int Gen_00287670::bfmeUpdate(void)
{
	if (m_bfmeObjectID != 0) {
		Object *object = TheGameLogic->bfmeFind(m_bfmeObjectID);
		if (object != 0) {
			if ((object->m_bfmeConditionA & 1) ||
				(object->m_bfmeConditionB & 1))
				return 11;
		}

		m_bfmeResettable.bfmeReset(0);

		Object *owner = *reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 8);
		owner->bfmePrepare(0x3F);
		owner->clearModelConditionState(MODEL_CONDITION_RESET);
		owner->bfmeFinish(0x49);
		owner->m_bfmeAI->m_bfmeCommands.aiIdle(COMMAND_SOURCE_SCRIPT);
	}

	return 11;
}

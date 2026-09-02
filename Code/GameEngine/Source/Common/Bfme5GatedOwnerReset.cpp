#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

enum CommandSourceType
{
	COMMAND_SOURCE_SCRIPT = 2
};

enum ModelConditionFlagType
{
	MODEL_CONDITION_RESET = 0x49
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

class BfmeRelationInterface
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void bfmeReset(int value);
};

class Object
{
public:
	BfmeRelationInterface *bfmeGetInterface(void);
	void bfmePrepare(int value);
	void clearModelConditionState(ModelConditionFlagType condition);
	void bfmeFinish(int value);

	char m_bfmeFields[0x204];
	BfmeAIHolder *m_bfmeAI;
};

class GameLogicFrameSlice
{
public:
	Object *bfmeFind(int id);
};

extern GameLogicFrameSlice *TheGameLogic;

class Gen_002875C0
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual bool bfmeAccept(Object *object);

	void bfmeRun(void);

private:
	int m_bfmeObjectID;
	char m_bfme08[4];
	int m_bfmeState;
};

// ?bfmeRun@Gen_002875C0@@QAEXXZ
void Gen_002875C0::bfmeRun(void)
{
	Object *secondary = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 0x18);
	Object *object = TheGameLogic->bfmeFind(m_bfmeObjectID);
	if (object != 0) {
		BfmeRelationInterface *relation = object->bfmeGetInterface();
		if (relation != 0 && bfmeAccept(object)) {
			relation->bfmeReset(0);
			m_bfmeObjectID = 0;
			m_bfmeState = 0;

			secondary->bfmeFinish(0x40);
			object->bfmePrepare(0x3F);
			object->clearModelConditionState(MODEL_CONDITION_RESET);
			object->bfmeFinish(0x49);
			object->m_bfmeAI->m_bfmeCommands.aiIdle(COMMAND_SOURCE_SCRIPT);
		}
	}
}

#undef BFME_TEN_VIRTUALS

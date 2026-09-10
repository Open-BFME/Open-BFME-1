// ?privateMoveToObject@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
// partial score=0.92 date=2026-09-04
class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class BfmeHostHA
{
public:
	virtual void bfmeSpare00HA(void) = 0;
	virtual void bfmeSpare01HA(void) = 0;
	virtual void bfmeSpare02HA(void) = 0;
	virtual void bfmeSpare03HA(void) = 0;
	virtual void bfmeSpare04HA(void) = 0;
	virtual void bfmePrepHA(void) = 0;          // +0x14 slot 5
	virtual void bfmeSpare06HA(void) = 0;
	virtual void bfmeSpare07HA(void) = 0;
	virtual void bfmePulseHA(int code) = 0;     // +0x20 slot 8
	virtual void bfmeSpare09HA(void) = 0;
	virtual void bfmeSpare10HA(void) = 0;
	virtual void bfmeSpare11HA(void) = 0;
	virtual void bfmeSpare12HA(void) = 0;
	virtual void bfmeSpare13HA(void) = 0;
	virtual void bfmeAimHA(void *who) = 0;      // +0x38 slot 14
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *objectToMoveTo,
		CommandSourceType commandSource);
};

extern BFMEActionManager *TheActionManager;

class BFMEGoalObjectMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void clear() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void setState(unsigned int state) = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;
};

struct BFMEAIUpdateFields
{
	char m_beforeObject[8];
	Object *m_object;
	char m_beforeMachine[0x30 - 0x0C];
	BFMEGoalObjectMachine *m_stateMachine;
	char m_beforeSource[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
};

class UpdateModule
{
	public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;

	protected:
	unsigned char m_bfmePad04[4];
	Object *m_bfmeObject;
	unsigned char m_bfmePad0C[0x20 - 0x0C];
};

class AICommandInterface
{
	public:
	virtual void aiDoCommand() = 0;
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
	protected:
	virtual void privateMoveToObject(Object *obj, CommandSourceType cmdSource);

	private:
	BFMEGoalObjectMachine *getMachine() const
	{
		return m_bfmeStateMachine;
	}

	unsigned char m_bfmePad24[0x30 - 0x24];
	BFMEGoalObjectMachine *m_bfmeStateMachine;
	unsigned char m_bfmePad34[0x48 - 0x34];
	CommandSourceType m_bfmeLastCommandSource;
};

void AIUpdateInterface::privateMoveToObject(Object *obj, CommandSourceType cmdSource)
{
	const bool accepted = TheActionManager->canEnterObject(m_bfmeObject, obj, cmdSource);
	if (!accepted)
		return;
	getMachine()->clear();
	getMachine()->setGoalObject(obj);
	m_bfmeLastCommandSource = cmdSource;
	getMachine()->setState(0x3c);
}

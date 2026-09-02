// cl: /DNDEBUG /MD
//
// Retail 0x002787D0: AIUpdateInterface two-arg command. isMobile, clear,
// StateMachine+0x38(0), prepare thunk (setGoalPositionClipped), setState(0x1b).

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum StateID
{
	BFME_AI_STATE_1B = 0x1B
};

class Object
{
public:
	Bool isMobile() const;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38(int);
};

class Rva002BC470StateAction
{
public:
	void prepare(void *first, void *second);
};

class AIUpdateInterface
{
protected:
	virtual void bfmePrivateCommand1B(void *first, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
};

void AIUpdateInterface::bfmePrivateCommand1B(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	m_stateMachine->slot38(0);
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_1B);
}

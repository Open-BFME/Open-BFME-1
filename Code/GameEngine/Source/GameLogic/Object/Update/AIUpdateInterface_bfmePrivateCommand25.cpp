// cl: /DNDEBUG /MD
//
// Retail 0x00278430: AIUpdateInterface two-arg move command. isMobile, clear,
// prepare thunk (setGoalPositionClipped), clear blocked flags, setState(0x25).

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum StateID
{
	BFME_AI_STATE_25 = 0x25
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isMobile() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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
};

class Rva002BC470StateAction
{
public:
	void prepare(void *first, void *second);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void bfmePrivateCommand25(void *first, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x16C - 0x4C];
	int m_blockedFrames;
	unsigned char m_unmodelled_170[0x325 - 0x170];
	unsigned char m_isBlocked;
	unsigned char m_isBlockedAndStuck;
};

void AIUpdateInterface::bfmePrivateCommand25(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_25);
}

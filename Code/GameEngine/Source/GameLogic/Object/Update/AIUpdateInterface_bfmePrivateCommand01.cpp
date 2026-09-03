// cl: /DNDEBUG /MD
//
// Retail 0x00273400: AIUpdateInterface two-arg command. Flag at +0x32b,
// isMobile, locomotor set, clear, StateMachine+0x38(arg1), blocked flags,
// setState(1), move voice at arg1+0x38.

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

enum StateID
{
	BFME_AI_STATE_01 = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
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
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38(void *arg);
};

class Rva001B5CC0
{
public:
	void set(const char *other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void bfmePrivateCommand01(void *first, CommandSourceType cmdSource);
	void playMoveVoiceResponse(const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x16C - 0x4C];
	int m_blockedFrames;
	unsigned char m_unmodelled_170[0x1CC - 0x170];
	Rva001B5CC0 *m_curLocomotor;
	unsigned char m_unmodelled_1D0[0x325 - 0x1D0];
	unsigned char m_isBlocked;
	unsigned char m_isBlockedAndStuck;
	unsigned char m_unmodelled_327[0x32B - 0x327];
	unsigned char m_flag32b;
};

void AIUpdateInterface::bfmePrivateCommand01(void *first, CommandSourceType cmdSource)
{
	if (m_flag32b)
		return;
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	m_stateMachine->slot38(first);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_01);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse((const Coord3D *)((const char *)first + 0x38));
}

// cl: /DNDEBUG /MD
//
// Retail 0x002785E0: AIUpdateInterface two-arg move command. Same shape as
// 0x002784A0 with setState(0x1e).

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

enum StateID
{
	BFME_AI_STATE_1E = 0x1E
};

struct Coord3D
{
	float x, y, z;
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
};

class Rva002BC470StateAction
{
public:
	void prepare(void *first, void *second);
};

class Rva001B5CC0
{
public:
	void set(const char *other);
};

class AIUpdateInterface
{
protected:
	virtual void bfmePrivateCommand1E(const Coord3D *pos, CommandSourceType cmdSource);
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
};

void AIUpdateInterface::bfmePrivateCommand1E(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare((void *)pos, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_1E);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
		playMoveVoiceResponse(pos);
}

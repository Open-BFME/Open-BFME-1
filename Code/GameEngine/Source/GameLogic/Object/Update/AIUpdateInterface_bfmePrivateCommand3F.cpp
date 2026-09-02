// cl: /DNDEBUG /MD
//
// Retail 0x00278390: AIUpdateInterface two-arg command. isMobile, weapon-set
// bit 8, locomotor set, clear, prepare, blocked flags, setState(0x3f).

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum StateID
{
	BFME_AI_STATE_3F = 0x3F
};

class WeaponSetFlags
{
public:
	Bool test(int type) const { return (m_words[0] & (1U << type)) != 0; }
	UnsignedInt m_words[1];
};

class Object
{
public:
	Bool isMobile() const;
	const WeaponSetFlags &getWeaponSetFlags() const;
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
	virtual void bfmePrivateCommand3F(void *first, CommandSourceType cmdSource);

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

void AIUpdateInterface::bfmePrivateCommand3F(void *first, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;
	if (m_object->getWeaponSetFlags().test(8))
		return;

	if (m_curLocomotor)
		m_curLocomotor->set((const char *)m_object);

	m_stateMachine->clear();
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)cmdSource);
	m_blockedFrames = 0;
	m_isBlocked = 0;
	m_isBlockedAndStuck = 0;
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_STATE_3F);
}

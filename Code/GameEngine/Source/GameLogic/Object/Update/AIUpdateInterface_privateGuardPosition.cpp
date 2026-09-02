// cl: /DNDEBUG /MD
//
// Retail 0x00279450: sibling of privateGuardObject. Same guards, guard
// target type 2, object-to-guard cleared, copies arg1+8 to +0x68,
// setState(0x10).

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_LOCATION = 2,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_GUARD = 0x10
};

struct Coord3D
{
	float x, y, z;
};

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;

private:
	virtual void slot00();
	void *m_template;
};

class Object : public Thing
{
public:
	Bool isMobile() const;

	unsigned char m_unmodelled_08[0x94 - 8];
	unsigned char m_flags;
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

class AIUpdateInterface
{
protected:
	virtual void privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	GuardMode m_guardMode;
	GuardTargetType m_guardTargetType[2];
	unsigned char m_unmodelled_58[0x64 - 0x58];
	UnsignedInt m_objectToGuard;
	UnsignedInt m_guardExtra;
};

void AIUpdateInterface::privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_LOCATION;
	else
		m_guardTargetType[0] = GUARDTARGET_LOCATION;

	m_guardMode = guardMode;
	m_objectToGuard = 0;
	m_guardExtra = *(UnsignedInt *)&pos->z;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

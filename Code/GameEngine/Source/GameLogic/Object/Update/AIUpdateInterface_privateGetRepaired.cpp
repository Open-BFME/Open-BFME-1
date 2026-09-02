// cl: /DNDEBUG /MD
//
// Retail 0x00279360: AIUpdateInterface::privateGetRepaired. Guards the
// object's +0x94 flag and isMobile / isKindOf(0x19), stores the depot at
// +0x4C, clears the state machine, then setState(0x18) which this TU already
// numbers BFME_AI_GET_REPAIRED.

typedef bool Bool;

enum KindOfType
{
	KINDOF_BFME_19 = 0x19
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum StateID
{
	BFME_AI_GET_REPAIRED = 0x18
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
	virtual void privateGetRepaired(Object *repairDepot, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	Object *m_repairDepot;
};

void AIUpdateInterface::privateGetRepaired(Object *repairDepot, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_BFME_19))
		return;

	m_repairDepot = repairDepot;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GET_REPAIRED);
}

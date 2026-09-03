// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction for the AIAttackState destructor at 0x0017CA40.

class State
{
public:
	virtual ~State();

	char m_stateFields[ 0x20 ];
};

class NotifyWeaponFiredInterface
{
public:
	virtual void notifyFired() = 0;
	virtual void notifyNewVictimChosen( void *victim ) = 0;
	virtual bool isWeaponSlotOkToFire( int slot ) const = 0;
	virtual bool isAttackingObject() const = 0;
	virtual const void *getOriginalVictimPos() const = 0;
};

class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject();

public:
	void deleteInstance()
	{
		if ( this )
			delete this;
	}
};

class AttackStateMachine : public MemoryPoolObject
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void halt();
};

class AsciiString
{
public:
	void *m_buffer;
	~AsciiString();
};

class AIAttackState : public State, public NotifyWeaponFiredInterface
{
protected:
	virtual ~AIAttackState();

	AttackStateMachine *m_attackMachine;
	void *m_attackParameters;
	void *m_victimTeam;
	char m_originalVictimPos[ 0x0C ];
	AsciiString m_lockedWeaponName;
	bool m_follow;
	bool m_isAttackingObject;
	bool m_isForceAttacking;
};

AIAttackState::~AIAttackState()
{
	if ( m_attackMachine )
	{
		m_attackMachine->halt();
		m_attackMachine->deleteInstance();
		m_attackMachine = 0;
	}
}

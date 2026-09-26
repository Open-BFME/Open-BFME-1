// cl: /DNDEBUG /MD /EHsc
//
// These empty derived destructors reproduce six retail 30-byte scalar-
// deleting wrappers. Matched constructors install the dedicated vtables
// whose slot-zero ILTs identify each wrapper.

class StateMachine
{
public:
	virtual ~StateMachine();
};

#define PUBLIC_STATE_MACHINE_DTOR(name) \
	class name : public StateMachine \
	{ \
	public: \
		virtual ~name() {} \
	}; \
	void force##name##DeletingDestructor() \
	{ \
		name value; \
	}

PUBLIC_STATE_MACHINE_DTOR(AttackMeleeStateMachine)
PUBLIC_STATE_MACHINE_DTOR(AttackFireWhileMovingMachine)
PUBLIC_STATE_MACHINE_DTOR(AttackHordeStateMachine)
PUBLIC_STATE_MACHINE_DTOR(AttackFireWhileChargingMachine)
PUBLIC_STATE_MACHINE_DTOR(BackAwayAndCowerStateMachine)

class AIAttackThenIdleStateMachine : public StateMachine
{
	friend void forceAIAttackThenIdleStateMachineDeletingDestructor();

protected:
	virtual ~AIAttackThenIdleStateMachine() {}
};

void forceAIAttackThenIdleStateMachineDeletingDestructor()
{
	AIAttackThenIdleStateMachine value;
}

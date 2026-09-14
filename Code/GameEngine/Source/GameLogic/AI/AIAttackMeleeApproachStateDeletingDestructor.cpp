// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIAttackMeleeApproachState scalar-deleting destructor at retail
// RVA 0x00185450 (30 bytes). AttackMeleeStateMachine constructs this state,
// assigns vtable 0x0109A6C0, and passes the matching literal name. Vtable slot
// zero routes through ILT 0x00003643 to this wrapper; the complete destructor
// chains to the exact AIInternalMoveToState destructor.

class AIAttackMeleeApproachState
{
protected:
	virtual ~AIAttackMeleeApproachState();

private:
	friend void forceAIAttackMeleeApproachStateDeletingDestructor();
};

void forceAIAttackMeleeApproachStateDeletingDestructor()
{
	AIAttackMeleeApproachState value;
}

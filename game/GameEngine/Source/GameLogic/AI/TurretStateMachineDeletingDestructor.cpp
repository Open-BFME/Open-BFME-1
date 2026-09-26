// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TurretStateMachine.
// The retail TurretAI header uses MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE,
// which places the virtual destructor in the protected pool-glue section.
// Its dedicated constructor vtable and complete-destructor tail route make
// this 30-byte wrapper's class identity exact.

class TurretStateMachine
{
protected:
	virtual ~TurretStateMachine();
private:
	friend void forceTurretStateMachineDeletingDestructor();
};

void forceTurretStateMachineDeletingDestructor()
{
	TurretStateMachine value;
}

// cl: /DNDEBUG /MD /EHsc
//
// The shipped class declaration uses pool glue, making this virtual destructor
// protected. Constructor 0x0015F240 installs vtable 0x01096420; slot-zero ILT
// 0x000380C8 reaches wrapper 0x0015EBB0, which calls complete-dtor ILT
// 0x0001F4F1.

class AIGuardRetaliateMachine
{
protected:
	virtual ~AIGuardRetaliateMachine();

private:
	friend void forceAIGuardRetaliateMachineDeletingDestructor();
};

void forceAIGuardRetaliateMachineDeletingDestructor()
{
	AIGuardRetaliateMachine value;
}

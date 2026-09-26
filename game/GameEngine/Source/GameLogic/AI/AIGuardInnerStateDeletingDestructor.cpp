// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIGuardInnerState scalar-deleting destructor at retail RVA
// 0x0015D110 (30 bytes). The exact constructor at 0x0015CE00 installs vtable
// 0x01096160, whose slot zero routes through ILT 0x00012030 to this wrapper.
// The wrapper calls the empty complete destructor through ILT 0x000434CD;
// that path tail-calls the already identified State base destructor.

class AIGuardInnerState
{
protected:
	virtual ~AIGuardInnerState();

private:
	friend void forceAIGuardInnerStateDeletingDestructor();
};

void forceAIGuardInnerStateDeletingDestructor()
{
	AIGuardInnerState value;
}

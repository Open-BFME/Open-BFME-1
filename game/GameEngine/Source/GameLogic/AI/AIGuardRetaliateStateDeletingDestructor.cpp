// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIGuardRetaliateState protected scalar-deleting destructor at
// retail RVA 0x00180260 (30 bytes). The exact constructor at 0x00171750
// installs vtable 0x01098248, whose slot zero routes through ILT 0x0003395B;
// the wrapper calls the complete destructor through ILT 0x000348C9.

class AIGuardRetaliateState
{
protected:
	virtual ~AIGuardRetaliateState();
private:
	friend void forceAIGuardRetaliateStateDeletingDestructor();
};

void forceAIGuardRetaliateStateDeletingDestructor()
{
	AIGuardRetaliateState value;
}

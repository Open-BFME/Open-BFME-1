// cl: /DNDEBUG /MD /EHsc
//
// The exact constructor at 0x00185A20 installs AIStateMachine's dedicated
// vtable 0x0109AEF8. Slot-zero ILT 0x0001DA11 reaches the retail 30-byte
// scalar-deleting wrapper at 0x00187240, which calls complete-dtor ILT
// 0x00020D9C and the matched body at 0x00187270.

class AIStateMachine
{
protected:
	virtual ~AIStateMachine();

private:
	friend void forceAIStateMachineDeletingDestructor();
};

void forceAIStateMachineDeletingDestructor()
{
	AIStateMachine value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIRampageState scalar-deleting destructor at retail RVA
// 0x00180510 (30 bytes). Constructor 0x001719F0 passes the literal class name
// and installs vtable 0x010984D8. Its slot zero routes through ILT 0x0003F07B
// to this wrapper, and slot two returns the same "AIRampageState" name.

class AIRampageState
{
protected:
	virtual ~AIRampageState();

private:
	friend void forceAIRampageStateDeletingDestructor();
};

void forceAIRampageStateDeletingDestructor()
{
	AIRampageState value;
}

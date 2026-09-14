// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AICowerState scalar-deleting destructor at retail RVA
// 0x00182320 (30 bytes). Constructor 0x001744C0 installs vtable 0x010991D0,
// whose slot zero routes through ILT 0x0000C38D to this wrapper. The same
// table owns the exact AICowerState onEnter and onExit bodies, while its name
// path returns the literal "AICowerState".

class AICowerState
{
protected:
	virtual ~AICowerState();

private:
	friend void forceAICowerStateDeletingDestructor();
};

void forceAICowerStateDeletingDestructor()
{
	AICowerState value;
}

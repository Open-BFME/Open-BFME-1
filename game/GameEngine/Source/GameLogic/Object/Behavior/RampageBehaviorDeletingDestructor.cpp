// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RampageBehavior.
// Vtable 0x00CA5A24 slots name this class (?getModuleNameKey@RampageBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0002F900 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001D732 reaches cleanup body 0x00203BC0.

class RampageBehavior
{
protected:
	virtual ~RampageBehavior();
private:
	friend void forceRampageBehaviorDeletingDestructor();
};

void forceRampageBehaviorDeletingDestructor()
{
	RampageBehavior value;
}

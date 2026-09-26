// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SlowDeathBehavior.
// Vtable 0x00CA66B4 slots name this class (?getModuleNameKey@SlowDeathBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00002BD0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00032691 reaches cleanup body 0x002077A0.

class SlowDeathBehavior
{
protected:
	virtual ~SlowDeathBehavior();
private:
	friend void forceSlowDeathBehaviorDeletingDestructor();
};

void forceSlowDeathBehaviorDeletingDestructor()
{
	SlowDeathBehavior value;
}

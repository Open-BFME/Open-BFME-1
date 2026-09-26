// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for WargBehavior.
// Vtable 0x00CA7314 slots name this class (?getModuleNameKey@WargBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00042109 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000299C9 reaches cleanup body 0x0020D930.

class WargBehavior
{
protected:
	virtual ~WargBehavior();
private:
	friend void forceWargBehaviorDeletingDestructor();
};

void forceWargBehaviorDeletingDestructor()
{
	WargBehavior value;
}

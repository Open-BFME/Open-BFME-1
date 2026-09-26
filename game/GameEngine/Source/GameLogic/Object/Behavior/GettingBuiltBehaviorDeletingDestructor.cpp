// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for GettingBuiltBehavior.
// Vtable 0x00CA46F4 slots name this class (?getModuleNameKey@GettingBuiltBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00022309 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0004186C reaches cleanup body 0x001FEB50.

class GettingBuiltBehavior
{
protected:
	virtual ~GettingBuiltBehavior();
private:
	friend void forceGettingBuiltBehaviorDeletingDestructor();
};

void forceGettingBuiltBehaviorDeletingDestructor()
{
	GettingBuiltBehavior value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ObjectGuardingHelper.
// Vtable 0x00CB3614 slots name this class (?getModuleNameKey@ObjectGuardingHelper@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00020D4C to this 30-byte wrapper, whose complete destructor
// route ILT 0x00004D3B reaches cleanup body 0x00256890.

class ObjectGuardingHelper
{
protected:
	virtual ~ObjectGuardingHelper();
private:
	friend void forceObjectGuardingHelperDeletingDestructor();
};

void forceObjectGuardingHelperDeletingDestructor()
{
	ObjectGuardingHelper value;
}

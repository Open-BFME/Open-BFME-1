// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ObjectGuardingHelper.
// Vtable 0x00CB3614 slots name this class (?getModuleNameKey@ObjectGuardingHelper@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00020D4C to this 30-byte wrapper, whose complete destructor
// route ILT 0x00004D3B reaches cleanup body 0x00256890.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva00256890Module (0x00256890, defined in
// Rva00256890ModuleDestructor.cpp) rather than an ObjectGuardingHelper
// complete destructor nothing defines. An explicit empty derived destructor
// inlines into the generated ??_G wrapper, leaving the direct base call.
struct Rva00256890Module
{
	virtual ~Rva00256890Module();
};

class ObjectGuardingHelper : public Rva00256890Module
{
protected:
	virtual ~ObjectGuardingHelper();
private:
	friend void forceObjectGuardingHelperDeletingDestructor();
};

// ??1ObjectGuardingHelper@@MAE@XZ present-unmatched
ObjectGuardingHelper::~ObjectGuardingHelper()
{
}

void forceObjectGuardingHelperDeletingDestructor()
{
	ObjectGuardingHelper value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DelayedWorldTextEventModule.
// Vtable 0x00CED9C0 slots name this class (?rva003BC1E0@DelayedWorldTextEventModule@@UAE_NXZ); its slot zero routes
// through ILT 0x00007F36 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00013183 reaches cleanup body 0x003BC170.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva003BC170 (0x003BC170, defined in
// V4StringMemberEhDtors.cpp) rather than a DelayedWorldTextEventModule
// complete destructor nothing defines. An explicit empty derived destructor
// inlines into the generated ??_G wrapper, leaving the direct base call.
struct Rva003BC170
{
	virtual ~Rva003BC170();
};

class DelayedWorldTextEventModule : public Rva003BC170
{
protected:
	virtual ~DelayedWorldTextEventModule();
private:
	friend void forceDelayedWorldTextEventModuleDeletingDestructor();
};

// ??1DelayedWorldTextEventModule@@MAE@XZ present-unmatched
DelayedWorldTextEventModule::~DelayedWorldTextEventModule()
{
}

void forceDelayedWorldTextEventModuleDeletingDestructor()
{
	DelayedWorldTextEventModule value;
}

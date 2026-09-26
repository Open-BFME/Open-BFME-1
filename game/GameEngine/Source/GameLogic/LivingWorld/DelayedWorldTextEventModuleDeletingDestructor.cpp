// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DelayedWorldTextEventModule.
// Vtable 0x00CED9C0 slots name this class (?rva003BC1E0@DelayedWorldTextEventModule@@UAE_NXZ); its slot zero routes
// through ILT 0x00007F36 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00013183 reaches cleanup body 0x003BC170.

class DelayedWorldTextEventModule
{
protected:
	virtual ~DelayedWorldTextEventModule();
private:
	friend void forceDelayedWorldTextEventModuleDeletingDestructor();
};

void forceDelayedWorldTextEventModuleDeletingDestructor()
{
	DelayedWorldTextEventModule value;
}

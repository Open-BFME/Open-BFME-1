// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for Script.
// Constructor 0x00352BA0 installs dedicated vtable 0x00CE858C; its slot
// zero routes through ILT 0x0002D510 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003F94F reaches cleanup body 0x00352C20.

class Script
{
protected:
	virtual ~Script();
private:
	friend void forceScriptDeletingDestructor();
};

void forceScriptDeletingDestructor()
{
	Script value;
}

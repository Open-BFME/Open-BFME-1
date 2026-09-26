// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ShellGameLoadScreen.
// Constructor 0x003367B0 installs dedicated vtable 0x00CE7530; its slot
// zero routes through ILT 0x00005E1B to this 30-byte wrapper, whose complete
// destructor route ILT 0x0002842F reaches cleanup body 0x003367E0.

class ShellGameLoadScreen
{
protected:
	virtual ~ShellGameLoadScreen();
private:
	friend void forceShellGameLoadScreenDeletingDestructor();
};

void forceShellGameLoadScreenDeletingDestructor()
{
	ShellGameLoadScreen value;
}

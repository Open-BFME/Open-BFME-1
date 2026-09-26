// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LoadScreen.
// Vtable 0x00CF9AF0 slots name this class (?update@LoadScreen@@UAEXH@Z); its slot zero routes
// through ILT 0x0003A571 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0004634E reaches cleanup body 0x00490470.

class LoadScreen
{
protected:
	virtual ~LoadScreen();
private:
	friend void forceLoadScreenDeletingDestructor();
};

void forceLoadScreenDeletingDestructor()
{
	LoadScreen value;
}

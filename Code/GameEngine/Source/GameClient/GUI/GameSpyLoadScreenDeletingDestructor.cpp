// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for GameSpyLoadScreen.
// Vtable 0x00CF9B44 slots name this class (?update@GameSpyLoadScreen@@UAEXH@Z); its slot zero routes
// through ILT 0x00023F65 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00041272 reaches cleanup body 0x00490AC0.

class GameSpyLoadScreen
{
protected:
	virtual ~GameSpyLoadScreen();
private:
	friend void forceGameSpyLoadScreenDeletingDestructor();
};

void forceGameSpyLoadScreenDeletingDestructor()
{
	GameSpyLoadScreen value;
}

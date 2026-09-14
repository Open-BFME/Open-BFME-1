// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FullFadeTransition.
// Vtable 0x00D0C814 slots name this class (?init@FullFadeTransition@@UAEXPAVGameWindow@@@Z and ?update@FullFadeTransition@@UAEXH@Z); its slot zero routes
// through ILT 0x00005768 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00012DFA reaches cleanup body 0x0059D400.

class FullFadeTransition
{
protected:
	virtual ~FullFadeTransition();
private:
	friend void forceFullFadeTransitionDeletingDestructor();
};

void forceFullFadeTransitionDeletingDestructor()
{
	FullFadeTransition value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for MainMenuScaleUpTransition.
// Vtable 0x00D0C9F8 slots name this class (?init@MainMenuScaleUpTransition@@UAEXPAVGameWindow@@@Z and ?update@MainMenuScaleUpTransition@@UAEXH@Z); its slot zero routes
// through ILT 0x0001EBDC to this 30-byte wrapper, whose complete destructor
// route ILT 0x000293ED reaches cleanup body 0x0059E4C0.

class MainMenuScaleUpTransition
{
protected:
	virtual ~MainMenuScaleUpTransition();
private:
	friend void forceMainMenuScaleUpTransitionDeletingDestructor();
};

void forceMainMenuScaleUpTransitionDeletingDestructor()
{
	MainMenuScaleUpTransition value;
}

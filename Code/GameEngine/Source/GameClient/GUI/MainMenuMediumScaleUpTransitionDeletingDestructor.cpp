// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for MainMenuMediumScaleUpTransition.
// Vtable 0x00D0C994 slots name this class (?update@MainMenuMediumScaleUpTransition@@UAEXH@Z and ?reverse@MainMenuMediumScaleUpTransition@@UAEXXZ); its slot zero routes
// through ILT 0x00005231 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00029D4D reaches cleanup body 0x0059DFF0.

class MainMenuMediumScaleUpTransition
{
protected:
	virtual ~MainMenuMediumScaleUpTransition();
private:
	friend void forceMainMenuMediumScaleUpTransitionDeletingDestructor();
};

void forceMainMenuMediumScaleUpTransitionDeletingDestructor()
{
	MainMenuMediumScaleUpTransition value;
}

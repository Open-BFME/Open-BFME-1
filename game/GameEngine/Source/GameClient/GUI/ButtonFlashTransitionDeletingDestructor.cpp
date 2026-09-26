// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ButtonFlashTransition.
// Vtable 0x00D0C604 slots name this class (?init@ButtonFlashTransition@@UAEXPAVGameWindow@@@Z and ?skip@ButtonFlashTransition@@UAEXXZ); its slot zero routes
// through ILT 0x00021E81 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000BF32 reaches cleanup body 0x0059A690.

class ButtonFlashTransition
{
protected:
	virtual ~ButtonFlashTransition();
private:
	friend void forceButtonFlashTransitionDeletingDestructor();
};

void forceButtonFlashTransitionDeletingDestructor()
{
	ButtonFlashTransition value;
}

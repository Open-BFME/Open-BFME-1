// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ReverseSoundTransition.
// Vtable 0x00D0CAB8 slots name this class (?init@ReverseSoundTransition@@UAEXPAVGameWindow@@@Z and ?update@ReverseSoundTransition@@UAEXH@Z); its slot zero routes
// through ILT 0x00036B06 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003D028 reaches cleanup body 0x0059EDF0.

class ReverseSoundTransition
{
protected:
	virtual ~ReverseSoundTransition();
private:
	friend void forceReverseSoundTransitionDeletingDestructor();
};

void forceReverseSoundTransitionDeletingDestructor()
{
	ReverseSoundTransition value;
}

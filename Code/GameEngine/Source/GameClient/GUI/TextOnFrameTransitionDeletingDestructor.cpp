// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TextOnFrameTransition.
// Vtable 0x00D0CC98 slots name this class (?init@TextOnFrameTransition@@UAEXPAVGameWindow@@@Z and ?update@TextOnFrameTransition@@UAEXH@Z); its slot zero routes
// through ILT 0x0000D1F2 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002AA9A reaches cleanup body 0x005A01D0.

class TextOnFrameTransition
{
protected:
	virtual ~TextOnFrameTransition();
private:
	friend void forceTextOnFrameTransitionDeletingDestructor();
};

void forceTextOnFrameTransitionDeletingDestructor()
{
	TextOnFrameTransition value;
}

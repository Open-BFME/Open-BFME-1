// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME7: BfmeAptScreenOnlineHome scalar-deleting destructor at retail
// RVA 0x00546690 (30 bytes). The matched constructor at 0x005484E0 installs
// vtable 0x01107B70; the complete destructor at 0x00545FF0 unregisters the
// OnlineHome gadgets and callback before closing the screen and clearing its
// singleton slot.

class BfmeAptScreenOnlineHome
{
public:
	virtual ~BfmeAptScreenOnlineHome();
};

void forceBfmeAptScreenOnlineHomeDeletingDestructor()
{
	BfmeAptScreenOnlineHome value;
}

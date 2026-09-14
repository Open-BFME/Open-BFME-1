// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME7: BfmeAptScreenOnlineChat scalar-deleting destructor at retail
// RVA 0x0052E490 (30 bytes). The matched constructor at 0x00536DC0 installs
// vtable 0x01106F58; the complete destructor at 0x0052D7C0 unregisters the
// AptOnlineChat callback and releases the four chat slots and trailing string
// members established by the authored OnlineChat layout.

class BfmeAptScreenOnlineChat
{
public:
	virtual ~BfmeAptScreenOnlineChat();
};

void forceBfmeAptScreenOnlineChatDeletingDestructor()
{
	BfmeAptScreenOnlineChat value;
}

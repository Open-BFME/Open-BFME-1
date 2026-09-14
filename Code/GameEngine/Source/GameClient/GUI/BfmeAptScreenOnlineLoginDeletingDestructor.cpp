// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME7: BfmeAptScreenOnlineLogin scalar-deleting destructor at retail
// RVA 0x0054D9E0 (30 bytes). The matched constructor at 0x005538A0 installs
// vtable 0x01107F58; the complete destructor at 0x0054CB60 closes the login
// screen and performs the exact WindowManager and IME teardown before clearing
// the OnlineLogin singleton.

class BfmeAptScreenOnlineLogin
{
public:
	virtual ~BfmeAptScreenOnlineLogin();
};

void forceBfmeAptScreenOnlineLoginDeletingDestructor()
{
	BfmeAptScreenOnlineLogin value;
}

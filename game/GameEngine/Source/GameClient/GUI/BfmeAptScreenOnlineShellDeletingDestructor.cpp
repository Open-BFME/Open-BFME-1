// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeAptScreenOnlineShell scalar-deleting destructor at retail RVA
// 0x0055D000 (30 bytes). The exact OnlineShell.apt constructor at 0x0055D150
// installs primary vtable 0x01108F48 and secondary vtable 0x01108F44; the
// matched complete destructor at 0x0055CB50 resets both views and tears down
// the screen-reference vector and singleton state.

class BfmeAptScreenOnlineShell
{
public:
	virtual ~BfmeAptScreenOnlineShell();
};

void forceBfmeAptScreenOnlineShellDeletingDestructor()
{
	BfmeAptScreenOnlineShell value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeAptScreenLanLobby scalar-deleting destructor at retail RVA
// 0x0051A570 (30 bytes). The exact LanLobby.apt constructor at 0x00519F90
// installs primary vtable 0x01105A78, while the matched complete destructor
// at 0x005199A0 resets all three screen vtables and tears down lobby state.

class BfmeAptScreenLanLobby
{
public:
	virtual ~BfmeAptScreenLanLobby();
};

void forceBfmeAptScreenLanLobbyDeletingDestructor()
{
	BfmeAptScreenLanLobby value;
}

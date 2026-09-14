// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeOnlineProfileScreen scalar-deleting destructor at retail RVA
// 0x005543A0 (30 bytes). The exact OnlineProfile constructor at 0x00557C00
// installs vtable 0x011085E8, whose slot zero routes through ILT 0x0003F666;
// the matched complete destructor at 0x00553EE0 resets that view and tears
// down the registered profile images and tooltips.

class BfmeOnlineProfileScreen
{
public:
	virtual ~BfmeOnlineProfileScreen();
};

void forceBfmeOnlineProfileScreenDeletingDestructor()
{
	BfmeOnlineProfileScreen value;
}

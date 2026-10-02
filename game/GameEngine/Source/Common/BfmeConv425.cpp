class BfmeOneATC
{
public:
	void bfmeStopATC(int what);
};

struct BfmeTwoATC
{
	unsigned char m_bfmeHead[0x59];
	bool m_bfmeFlag;
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
// BfmeOneATC above is this TU's view of the pointee, so the member call casts.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// Retail global 0x012F4B58; EA's own name for this pointer is
// `Shell *TheShell`, defined once in
// game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp.  BfmeTwoATC above is
// this TU's view of the pointee, so the flag stores cast at the use.
class Shell;

extern Shell *TheShell;

class BfmeThingATC
{
public:
	void bfmeGoATC();
	unsigned char m_bfmeHead[0x264];
	int m_bfmeState;
};

void BfmeThingATC::bfmeGoATC()
{
	if (m_bfmeState == 2)
	{
		m_bfmeState = 0;
		((BfmeOneATC *)g_rva012F19E8WindowManager)->bfmeStopATC(0);
		((BfmeTwoATC *)TheShell)->m_bfmeFlag = true;
		return;
	}
	((BfmeTwoATC *)TheShell)->m_bfmeFlag = true;
}

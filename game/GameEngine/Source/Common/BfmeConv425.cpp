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
extern BfmeTwoATC *g_bfmeTwoATC;

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
		g_bfmeTwoATC->m_bfmeFlag = true;
		return;
	}
	g_bfmeTwoATC->m_bfmeFlag = true;
}

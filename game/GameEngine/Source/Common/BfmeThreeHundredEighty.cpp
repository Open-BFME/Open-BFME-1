struct BfmeSlotAAA
{
	void *m_bfmeWhat;
	unsigned char m_bfmeRest[0x14];
};

struct BfmeModeAAA
{
	unsigned char m_bfmeHead[0x1b4];
	int m_bfmeMode;
};

class BfmeSinkAAA
{
public:
	void bfmeSendAAA(void *what, bool flag, int more);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
extern BfmeSinkAAA *g_bfmeSinkAAA;

class BfmeThingAAA
{
public:
	void bfmeGoAAA(int at);
	unsigned char m_bfmeHead[0x1c];
	BfmeSlotAAA m_bfmeSlots[12];
};

void BfmeThingAAA::bfmeGoAAA(int at)
{
	if (at < 0)
		return;
	if (at >= 0xc)
		return;
	void *what = m_bfmeSlots[at].m_bfmeWhat;
	if (what == 0)
		return;
	g_bfmeSinkAAA->bfmeSendAAA(what, ((BfmeModeAAA *)g_rva012F19E8WindowManager)->m_bfmeMode != 2, 0);
}

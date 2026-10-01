struct BfmeSlotAAB
{
	void *m_bfmeWhat;
	unsigned char m_bfmeRest[0x14];
};

struct BfmeModeAAB
{
	unsigned char m_bfmeHead[0x1b4];
	int m_bfmeMode;
};

class BfmeSinkAAB
{
public:
	void bfmeSendAAB(void *what, bool flag, int more);
};

// Retail global at 0x012F19E8; the canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, so the pointee must be
// the real WindowManager and only the member read needs the TU-local view.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern BfmeSinkAAB *g_bfmeSinkAAB;

class BfmeThingAAB
{
public:
	void bfmeGoAAB(int at);
	unsigned char m_bfmeHead[0x198];
	BfmeSlotAAB m_bfmeSlots[12];
};

void BfmeThingAAB::bfmeGoAAB(int at)
{
	if (at < 0)
		return;
	if (at >= 0xc)
		return;
	void *what = m_bfmeSlots[at].m_bfmeWhat;
	if (what == 0)
		return;
	g_bfmeSinkAAB->bfmeSendAAB(what, ((BfmeModeAAB *)g_rva012F19E8WindowManager)->m_bfmeMode != 2, 0);
}

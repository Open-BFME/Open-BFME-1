// ?tick@Rva006E1670@@QAEXXZ
// partial score=0.88 date=2026-09-12
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006E1670. Sibling of BfmeTimerGF::bfmeTickGF at 0x006E1620:
// enter phase 1 when the global mode is 4 and this is not, then count
// the timer down and notify. No named caller; name stays address-derived.

struct BfmeModeAZC
{
	void bfmeStopAZC(int a);

	unsigned char m_pad[0xC];
	int m_state;
};

extern BfmeModeAZC *g_bfmeModeAZC;

class Rva006E1670
{
public:
	void tick(void);

	unsigned char m_head[0xC];
	int m_state;
	int m_phase;
	int m_timer;
};

void Rva006E1670::tick(void)
{
	int gstate = g_bfmeModeAZC->m_state;
	int four = 4;
	if (gstate == four)
	{
		if (m_state != four)
		{
			m_phase = 1;
			m_state = four;
			m_timer = 0xFF;
		}
	}

	int phase = m_phase;
	if (phase != 0)
	{
		if (phase == 1)
		{
			int remaining = --m_timer;
			if (remaining > 0)
				return;
			m_timer = 0;
			m_phase = 0;
			if (g_bfmeModeAZC->m_state == four)
				g_bfmeModeAZC->bfmeStopAZC(0);
			m_state = 0;
		}
	}
}

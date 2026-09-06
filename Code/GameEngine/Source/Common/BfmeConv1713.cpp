class BfmeModeGF
{
public:
	void bfmeStopGF(int flag);

	unsigned char m_bfmeHeadGF[0xc];
	int m_bfmeKindGF;
};

extern BfmeModeGF *g_bfmeModeGF;

class BfmeTimerGF
{
public:
	void bfmeTickGF(void);

	unsigned char m_bfmeHeadGF[0xc];
	int m_bfmeOtherGF;
	int m_bfmeStateGF;
	int m_bfmeCountGF;
};

void BfmeTimerGF::bfmeTickGF(void)
{
	if (m_bfmeStateGF != 1)
		return;

	int remaining = --m_bfmeCountGF;

	if (remaining > 0)
		return;

	m_bfmeCountGF = 0;
	m_bfmeStateGF = 0;

	if (g_bfmeModeGF->m_bfmeKindGF == 4)
		g_bfmeModeGF->bfmeStopGF(0);

	m_bfmeOtherGF = 0;
}

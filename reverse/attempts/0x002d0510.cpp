// ?bfmeStepEQG@BfmeCounterEQG@@QAEHXZ (identity unknown)
// partial score=0.8 date=2026-09-06
// 41/41 bytes; every diff traces to MSVC materialising 0 in edx (xor edx,edx).
struct BfmeCounterEQG
{
	int bfmeStepEQG(void);
	unsigned char m_bfmeHeadEQG[0x14];
	volatile int m_bfmeTicksEQG;
	unsigned char m_bfmeMidEQG[0x14];
	volatile unsigned int m_bfmeBusyEQG;
};

int BfmeCounterEQG::bfmeStepEQG(void)
{
	if (m_bfmeBusyEQG > 0)
	{
		m_bfmeTicksEQG = 0;
		return 1;
	}
	bool empty = (m_bfmeTicksEQG == 0);
	if (empty)
	{
		m_bfmeTicksEQG = 0;
		return 1;
	}
	--m_bfmeTicksEQG;
	return 1;
}

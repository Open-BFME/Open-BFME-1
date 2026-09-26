struct BfmeStateEQF
{
	unsigned char m_bfmeHeadEQF[0x128];
	int m_bfmeMaskEQF;
	unsigned char m_bfmeMidEQF[0x218];
	unsigned char m_bfmeFlagEQF;
};

struct BfmeHolderEQF
{
	int bfmeRankEQF(void);
	unsigned char m_bfmeHeadEQF[8];
	BfmeStateEQF *m_bfmeStateEQF;
};

int BfmeHolderEQF::bfmeRankEQF(void)
{
	if ((m_bfmeStateEQF->m_bfmeFlagEQF & 1) != 0)
		return 0x3fffffff;
	BfmeStateEQF *state = m_bfmeStateEQF;
	if (state != 0 && (state->m_bfmeMaskEQF & 0x1000) != 0)
		return 1;
	return 5;
}

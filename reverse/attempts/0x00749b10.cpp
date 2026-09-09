// ?bfmeSetBitAAP@BfmeBitmapAAP@@QAEXHH_N@Z
// partial score=0.94 date=2026-09-08
class BfmeBitmapAAP
{
public:
	void bfmeSetBitAAP(int x, int y, bool on);

	unsigned char m_bfmeHeadAAP[8];
	int m_bfmeWidthAAP;
	int m_bfmeHeightAAP;
	unsigned char m_bfmeGapAAP[0x34 - 0x10];
	int m_bfmeStrideAAP;
	unsigned char m_bfmeGapBAAP[0x68 - 0x38];
	unsigned char *m_bfmeBeginAAP;
	unsigned char *m_bfmeEndAAP;
};

void BfmeBitmapAAP::bfmeSetBitAAP(int x, int y, bool on)
{
	if (x < 0 || y < 0 || y >= m_bfmeHeightAAP || x >= m_bfmeWidthAAP)
		return;

	int idx = m_bfmeStrideAAP * y + (x >> 3);

	if ((unsigned int)idx >= (unsigned int)(m_bfmeEndAAP - m_bfmeBeginAAP))
		return;

	unsigned char *p = *(unsigned char *volatile *)&m_bfmeBeginAAP + idx;
	unsigned char mask = (unsigned char)(1 << (x & 7));

	*p = on ? (unsigned char)(*p | mask) : (unsigned char)(*p & ~mask);
}

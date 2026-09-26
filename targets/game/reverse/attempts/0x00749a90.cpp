// ?d_00749a90@@YAXXZ
// partial score=0.85 date=2026-09-07
class BfmeMaskEUB
{
public:
	void bfmeSetBitEUB(int x, int y, char set);

	unsigned char m_bfmeHeadEUB[8];
	int m_bfmeWEUB;
	int m_bfmeHEUB;
	unsigned char m_bfmePadAEUB[0x24];
	int m_bfmePitchEUB;
	unsigned char *m_bfmeBeginEUB;
	unsigned char *m_bfmeEndEUB;
};

void BfmeMaskEUB::bfmeSetBitEUB(int x, int y, char set)
{
	if (x < 0 || y < 0 || y >= m_bfmeHEUB || x >= m_bfmeWEUB)
		return;

	int offset = m_bfmePitchEUB * y + (x >> 3);

	if ((unsigned int)offset >= (unsigned int)(m_bfmeEndEUB - m_bfmeBeginEUB))
		return;

	unsigned char *p = *(unsigned char *volatile *)&m_bfmeBeginEUB + offset;
	unsigned char mask = (unsigned char)(1 << (x & 7));

	if (set)
		*p |= mask;
	else
		*p &= ~mask;
}

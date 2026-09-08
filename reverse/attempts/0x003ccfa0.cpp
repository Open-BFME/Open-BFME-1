// ?bfmeAtABL@BfmeGridABL@@QAEPAUBfmeCellABL@@MM@Z
// partial score=0.9 date=2026-09-09
struct BfmeCellABL
{
	unsigned char m_bfmeBodyABL[0x3c];
};

struct BfmeInfoABL
{
	unsigned char m_bfmeHeadABL[0xc];
	float m_bfme0CABL;
};

class BfmeGridABL
{
public:
	BfmeCellABL *bfmeAtABL(float x, float y);

	float m_bfme00ABL;
	float m_bfme04ABL;
	BfmeCellABL *m_bfme08ABL;
	BfmeCellABL *m_bfme0CABL;
	unsigned char m_bfmeGapABL[4];
	BfmeInfoABL *m_bfme14ABL;
	int m_bfme18ABL;
};

BfmeCellABL *BfmeGridABL::bfmeAtABL(float x, float y)
{
	float fx = x - m_bfme00ABL;
	float cs = m_bfme14ABL->m_bfme0CABL;
	float fy = y - m_bfme04ABL;

	int col = (int)(fx / cs);

	if (col < 0)
		return 0;

	int w = m_bfme18ABL;

	if (col >= w)
		return 0;

	int idx = (int)(fy / cs) * w + col;

	if (idx < 0)
		return 0;

	if ((unsigned int)idx >= (unsigned int)(m_bfme0CABL - m_bfme08ABL))
		return 0;

	return m_bfme08ABL + idx;
}

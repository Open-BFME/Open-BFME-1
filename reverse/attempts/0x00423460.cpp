// ?bfmeAtZC@BfmeHostZC@@QAEXH@Z
// partial score=0.60 date=2026-09-09
struct BfmeAZC
{
	unsigned char m_bfmePadZC[0x1c];
};

struct BfmeBZC
{
	void bfmeUseZC(BfmeAZC *a);

	unsigned char m_bfmePadZC[0x18];
};

class BfmeHostZC
{
public:
	void bfmeAtZC(int i);

	unsigned char m_bfmeHeadZC[0xc];
	BfmeAZC *m_bfme0CZC;
	BfmeAZC *m_bfme10ZC;
	unsigned char m_bfmeMidZC[0x4c - 0x14];
	BfmeBZC *m_bfme4CZC;
	BfmeBZC *m_bfme50ZC;
};

void BfmeHostZC::bfmeAtZC(int i)
{
	if (i == -1)
		return;

	if (i < 0)
		return;

	if ((unsigned int)i >= (unsigned int)(m_bfme50ZC - m_bfme4CZC))
		return;

	if (m_bfme10ZC - m_bfme0CZC != m_bfme50ZC - m_bfme4CZC)
		return;

	m_bfme4CZC[i].bfmeUseZC(&m_bfme0CZC[i]);
}

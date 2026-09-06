// ?bfmeSetERB@BfmeHostERB@@QAEXPAPAVBfmeTexERB@@@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 54/54; only the two tail stores are transposed (retail +0x4c then +0x50).
// Pin needed: ?bfmeReleaseERB@BfmeTexERB@@QAEXXZ,0x009EB7A0 (Release_Ref)
class BfmeTexERB
{
public:
	void bfmeReleaseERB(void);
	void bfmeAddRefERB(void) { ++m_bfmeRefERB; }

	unsigned char m_bfmeHeadERB[4];
	unsigned short m_bfmeRefERB;
};

class BfmeHostERB
{
public:
	void bfmeSetERB(BfmeTexERB **slot);

	unsigned char m_bfmeHeadERB[0x4c];
	BfmeTexERB *m_bfmeTexERB;
	int m_bfmeMaskERB;
};

void BfmeHostERB::bfmeSetERB(BfmeTexERB **slot)
{
	BfmeTexERB *value = *slot;
	if (value == m_bfmeTexERB)
		return;
	if (value != 0)
		value->bfmeAddRefERB();
	if (m_bfmeTexERB != 0)
		m_bfmeTexERB->bfmeReleaseERB();
	BfmeTexERB *fresh = *slot;
	m_bfmeMaskERB = (fresh != 0) ? -1 : 0;
	m_bfmeTexERB = fresh;
}

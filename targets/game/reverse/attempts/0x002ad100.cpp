// ?bfmeRunXG@BfmeHostXG@@QAEXXZ
// partial score=0.9 date=2026-09-08
// pin needed: ?bfmeApplyXG@BfmeHostXG@@QAEXPAUBfmeFieldAXG@@PAUBfmeFieldBXG@@@Z,0x0001B04A
struct BfmeFieldAXG
{
	int m_bfmeVXG;
};

struct BfmeFieldBXG
{
	int m_bfmeVXG;
};

struct RvaC4390First
{
	unsigned char m_bfmeHeadXG[0x38];
	BfmeFieldBXG m_bfme38XG;
};

class RvaC4390Second
{
public:
	RvaC4390First *resolve(int k);

	unsigned char m_bfmeHeadXG[0x38];
	BfmeFieldAXG m_bfme38XG;
};

class BfmeHostXG
{
public:
	void bfmeRunXG();
	void bfmeApplyXG(BfmeFieldAXG *a, BfmeFieldBXG *b);

	unsigned char m_bfmeHeadXG[8];
	RvaC4390Second *m_bfme08XG;
};

void BfmeHostXG::bfmeRunXG()
{
	RvaC4390First *p = m_bfme08XG->resolve(0);

	if (p == 0)
		bfmeApplyXG(&m_bfme08XG->m_bfme38XG, &((RvaC4390First *)m_bfme08XG)->m_bfme38XG);
	else
		bfmeApplyXG(&m_bfme08XG->m_bfme38XG, &p->m_bfme38XG);
}

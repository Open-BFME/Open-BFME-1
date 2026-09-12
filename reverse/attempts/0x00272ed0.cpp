// ?bfmeApplyGN@BfmeSelfGN@@QAE_NH@Z
// partial score=0.92 date=2026-09-08
class BfmeNodeGN
{
public:
	BfmeNodeGN *bfmeGetGN();
	float bfmeComputeGN(int v);

	unsigned char m_bfmeHeadGN[4];
	BfmeNodeGN *m_bfmeSubGN;
};

class BfmeOwnerGN
{
public:
	unsigned char m_bfmeGapGN[4];
	BfmeNodeGN *volatile m_bfmeNodeGN;
};

class BfmeSelfGN
{
public:
	bool bfmeApplyGN(int v);
	bool bfmeCheckGN(int v);
	void bfmeBeginGN();

	unsigned char m_bfmeHeadGN[8];
	BfmeOwnerGN *m_bfmeOwnerGN;
	unsigned char m_bfmeGap2GN[0x1c4];
	int m_bfmeValueGN;
	float m_bfmeResultGN;
	unsigned char m_bfmeGap3GN[0x14f];
	char m_bfmeFlagAGN;
	unsigned char m_bfmeGap4GN[0xf];
	char m_bfmeFlagBGN;
};

static __forceinline BfmeNodeGN *bfmeDerefGN(BfmeNodeGN *p)
{
	if (p->m_bfmeSubGN != 0)
		return p->m_bfmeSubGN->bfmeGetGN();

	return 0;
}

bool BfmeSelfGN::bfmeApplyGN(int v)
{
	if (v == 0 && m_bfmeFlagAGN != 0)
		v = 1;

	if (v == m_bfmeValueGN)
		return true;

	if (m_bfmeFlagBGN == 0 && bfmeCheckGN(v))
	{
		bfmeBeginGN();

		BfmeNodeGN *n = m_bfmeOwnerGN->m_bfmeNodeGN;
		BfmeNodeGN *r = (n != 0) ? bfmeDerefGN(n) : 0;

		m_bfmeResultGN = r->bfmeComputeGN(m_bfmeValueGN);

		return true;
	}
	else
	{
		return false;
	}
}

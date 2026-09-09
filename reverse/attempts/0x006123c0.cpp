// ?bfmeFindFD@BfmeHostFD@@QAEHI@Z
// partial score=0.92 date=2026-09-09
class BfmeNodeFD
{
public:
	BfmeNodeFD *m_bfmeNextFD;
	unsigned int m_bfmeKeyFD;
	int m_bfmeValFD;
};

class BfmeHostFD
{
public:
	int bfmeFindFD(unsigned int key);

	unsigned char m_bfmeHeadFD[0x214];
	BfmeNodeFD **volatile m_bfmeBeginFD;
	BfmeNodeFD **volatile m_bfmeEndFD;
};

int BfmeHostFD::bfmeFindFD(unsigned int key)
{
	BfmeNodeFD **b = m_bfmeBeginFD;
	unsigned int n = (unsigned int)(m_bfmeEndFD - b);
	BfmeNodeFD *p = m_bfmeBeginFD[key % n];

	while (p != 0 && p->m_bfmeKeyFD != key)
		p = p->m_bfmeNextFD;

	if (p == 0)
		return 0;

	return p->m_bfmeValFD;
}

class BfmeNodeCU
{
public:
	// The new-expression below reaches this body again through ILT, so the
	// body is the class's recursive copy constructor (identity_evidence/
	// 00350380-00350410-node-copy-constructors.md).
	BfmeNodeCU(const BfmeNodeCU &src);

	BfmeNodeCU *m_bfmeItemCU;
	int m_bfmeBCU;
	int m_bfmeCCU;
};

BfmeNodeCU::BfmeNodeCU(const BfmeNodeCU &src)
{
	BfmeNodeCU *p;

	if (src.m_bfmeItemCU != 0)
		p = new BfmeNodeCU(*src.m_bfmeItemCU);
	else
		p = 0;

	m_bfmeItemCU = p;
	m_bfmeBCU = src.m_bfmeBCU;
	m_bfmeCCU = src.m_bfmeCCU;
}

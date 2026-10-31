class BfmeNodeCV
{
public:
	// The new-expression below reaches this body again through ILT, so the
	// body is the class's recursive copy constructor (identity_evidence/
	// 00350380-00350410-node-copy-constructors.md).
	BfmeNodeCV(const BfmeNodeCV &src);

	BfmeNodeCV *m_bfmeItemCV;
	int m_bfmeBCV;
	int m_bfmeCCV;
};

BfmeNodeCV::BfmeNodeCV(const BfmeNodeCV &src)
{
	BfmeNodeCV *p;

	if (src.m_bfmeItemCV != 0)
		p = new BfmeNodeCV(*src.m_bfmeItemCV);
	else
		p = 0;

	m_bfmeItemCV = p;
	m_bfmeBCV = src.m_bfmeBCV;
	m_bfmeCCV = src.m_bfmeCCV;
}

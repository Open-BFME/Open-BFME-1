class BfmeObjCF
{
public:
	~BfmeObjCF();

	unsigned char m_bfmeHeadCF[0x10];
	int m_bfmeCountCF;
};

class BfmeRefCF
{
public:
	BfmeRefCF *bfmeAssignCF(const BfmeRefCF &other);

	BfmeObjCF *m_bfmePtrCF;
};

BfmeRefCF *BfmeRefCF::bfmeAssignCF(const BfmeRefCF &other)
{
	if (this != &other)
	{
		--m_bfmePtrCF->m_bfmeCountCF;

		if (m_bfmePtrCF->m_bfmeCountCF == 0)
			delete m_bfmePtrCF;

		m_bfmePtrCF = other.m_bfmePtrCF;
		m_bfmePtrCF->m_bfmeCountCF++;
	}

	return this;
}

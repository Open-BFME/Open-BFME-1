class BfmeVecUC
{
public:
	BfmeVecUC(const BfmeVecUC &other) throw()
	{
		m_bfmeXUC = other.m_bfmeXUC;
		m_bfmeYUC = other.m_bfmeYUC;
		m_bfmeZUC = other.m_bfmeZUC;
	}
	~BfmeVecUC() throw() {}

	int m_bfmeXUC;
	int m_bfmeYUC;
	int m_bfmeZUC;
};

class BfmeTgtUC
{
public:
	void bfmeRunUC(void *first, BfmeVecUC value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);
};

class BfmeOwnUC
{
public:
	void bfmeFwdUC(void *first, BfmeVecUC value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);

	unsigned char m_bfmeHeadUC[0x10];
	BfmeTgtUC *m_bfmeTgtUC;
};

void BfmeOwnUC::bfmeFwdUC(void *first, BfmeVecUC value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh, void *eighth, void *ninth)
{
	if (m_bfmeTgtUC)
		m_bfmeTgtUC->bfmeRunUC(first, value, third, fourth, fifth, sixth, seventh,
			eighth, ninth);
}

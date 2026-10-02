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

class BfmeVecUE
{
public:
	BfmeVecUE(const BfmeVecUE &other) throw()
	{
		m_bfmeXUE = other.m_bfmeXUE;
		m_bfmeYUE = other.m_bfmeYUE;
		m_bfmeZUE = other.m_bfmeZUE;
	}
	~BfmeVecUE() throw() {}

	int m_bfmeXUE;
	int m_bfmeYUE;
	int m_bfmeZUE;
};

class BfmeTgtUE
{
public:
	void bfmeRunUE(void *first, BfmeVecUE value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);
};

class BfmeOwnUE
{
public:
	void bfmeFwdUE(void *first, BfmeVecUE value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);

	unsigned char m_bfmeHeadUE[0x3098];
	BfmeTgtUE *m_bfmeTgtUE;
};

class BfmeOwnUC
{
public:
	void bfmeFwdUC(void *first, BfmeVecUC value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);

	unsigned char m_bfmeHeadUC[0x10];
	BfmeOwnUE *m_bfmeTgtUC;
};

void BfmeOwnUC::bfmeFwdUC(void *first, BfmeVecUC value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh, void *eighth, void *ninth)
{
	if (m_bfmeTgtUC)
		m_bfmeTgtUC->bfmeFwdUE(first, *(BfmeVecUE *)&value, third, fourth, fifth, sixth, seventh,
			eighth, ninth);
}

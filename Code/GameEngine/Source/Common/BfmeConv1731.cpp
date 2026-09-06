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

void BfmeOwnUE::bfmeFwdUE(void *first, BfmeVecUE value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh, void *eighth, void *ninth)
{
	if (m_bfmeTgtUE)
		m_bfmeTgtUE->bfmeRunUE(first, value, third, fourth, fifth, sixth, seventh,
			eighth, ninth);
}

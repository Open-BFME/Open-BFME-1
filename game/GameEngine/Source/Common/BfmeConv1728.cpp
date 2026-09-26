class BfmeVecUB
{
public:
	BfmeVecUB(const BfmeVecUB &other) throw()
	{
		m_bfmeXUB = other.m_bfmeXUB;
		m_bfmeYUB = other.m_bfmeYUB;
		m_bfmeZUB = other.m_bfmeZUB;
	}
	~BfmeVecUB() throw() {}

	int m_bfmeXUB;
	int m_bfmeYUB;
	int m_bfmeZUB;
};

class BfmeTgtUB
{
public:
	void bfmeRunUB(void *first, BfmeVecUB value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);
};

class BfmeOwnUB
{
public:
	void bfmeFwdUB(void *first, BfmeVecUB value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);

	unsigned char m_bfmeHeadUB[0x10];
	BfmeTgtUB *m_bfmeTgtUB;
};

void BfmeOwnUB::bfmeFwdUB(void *first, BfmeVecUB value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh, void *eighth, void *ninth)
{
	if (m_bfmeTgtUB)
		m_bfmeTgtUB->bfmeRunUB(first, value, third, fourth, fifth, sixth, seventh,
			eighth, ninth);
}

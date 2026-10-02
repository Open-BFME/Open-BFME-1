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

class BfmeVecUD
{
public:
	BfmeVecUD(const BfmeVecUD &other) throw()
	{
		m_bfmeXUD = other.m_bfmeXUD;
		m_bfmeYUD = other.m_bfmeYUD;
		m_bfmeZUD = other.m_bfmeZUD;
	}
	~BfmeVecUD() throw() {}

	int m_bfmeXUD;
	int m_bfmeYUD;
	int m_bfmeZUD;
};

class BfmeTgtUD
{
public:
	void bfmeRunUD(void *first, BfmeVecUD value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);
};

class BfmeOwnUD
{
public:
	void bfmeFwdUD(void *first, BfmeVecUD value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);

	unsigned char m_bfmeHeadUD[0x3094];
	BfmeTgtUD *m_bfmeTgtUD;
};

class BfmeOwnUB
{
public:
	void bfmeFwdUB(void *first, BfmeVecUB value, void *third, void *fourth,
		void *fifth, void *sixth, void *seventh, void *eighth, void *ninth);

	unsigned char m_bfmeHeadUB[0x10];
	BfmeOwnUD *m_bfmeTgtUB;
};

void BfmeOwnUB::bfmeFwdUB(void *first, BfmeVecUB value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh, void *eighth, void *ninth)
{
	if (m_bfmeTgtUB)
		m_bfmeTgtUB->bfmeFwdUD(first, *(BfmeVecUD *)&value, third, fourth, fifth, sixth, seventh,
			eighth, ninth);
}

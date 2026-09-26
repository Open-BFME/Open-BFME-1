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

void BfmeOwnUD::bfmeFwdUD(void *first, BfmeVecUD value, void *third, void *fourth,
	void *fifth, void *sixth, void *seventh, void *eighth, void *ninth)
{
	if (m_bfmeTgtUD)
		m_bfmeTgtUD->bfmeRunUD(first, value, third, fourth, fifth, sixth, seventh,
			eighth, ninth);
}

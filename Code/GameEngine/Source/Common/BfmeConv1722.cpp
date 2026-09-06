class BfmeArgKD
{
public:
	BfmeArgKD(const BfmeArgKD &other) throw()
	{
		m_bfmeAKD = other.m_bfmeAKD;
		m_bfmeBKD = other.m_bfmeBKD;
		m_bfmeCKD = other.m_bfmeCKD;
	}
	~BfmeArgKD() throw() {}

	int m_bfmeAKD;
	int m_bfmeBKD;
	int m_bfmeCKD;
};

class BfmeTgtKD
{
public:
	char bfmeRunKD(void *first, BfmeArgKD arg, void *last);
};

class BfmeOwnKD
{
public:
	char bfmeFwdKD(void *first, BfmeArgKD arg, void *last);

	unsigned char m_bfmeHeadKD[0x3094];
	BfmeTgtKD *m_bfmeTgtKD;
};

char BfmeOwnKD::bfmeFwdKD(void *first, BfmeArgKD arg, void *last)
{
	if (m_bfmeTgtKD)
		return m_bfmeTgtKD->bfmeRunKD(first, arg, last);

	return 0;
}

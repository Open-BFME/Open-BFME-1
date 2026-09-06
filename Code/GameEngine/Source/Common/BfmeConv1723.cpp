class BfmeArgKE
{
public:
	BfmeArgKE(const BfmeArgKE &other) throw()
	{
		m_bfmeAKE = other.m_bfmeAKE;
		m_bfmeBKE = other.m_bfmeBKE;
		m_bfmeCKE = other.m_bfmeCKE;
	}
	~BfmeArgKE() throw() {}

	int m_bfmeAKE;
	int m_bfmeBKE;
	int m_bfmeCKE;
};

class BfmeTgtKE
{
public:
	char bfmeRunKE(void *first, BfmeArgKE arg, void *last);
};

class BfmeOwnKE
{
public:
	char bfmeFwdKE(void *first, BfmeArgKE arg, void *last);

	unsigned char m_bfmeHeadKE[0x3098];
	BfmeTgtKE *m_bfmeTgtKE;
};

char BfmeOwnKE::bfmeFwdKE(void *first, BfmeArgKE arg, void *last)
{
	if (m_bfmeTgtKE)
		return m_bfmeTgtKE->bfmeRunKE(first, arg, last);

	return 0;
}

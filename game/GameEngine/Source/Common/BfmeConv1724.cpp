class BfmeArgLA
{
public:
	BfmeArgLA(const BfmeArgLA &other) throw()
	{
		m_bfmeALA = other.m_bfmeALA;
		m_bfmeBLA = other.m_bfmeBLA;
	}
	~BfmeArgLA() throw() {}

	int m_bfmeALA;
	int m_bfmeBLA;
};

struct BfmePairLA
{
	void *m_bfmeFirstLA;
	void *m_bfmeLastLA;
};

class BfmeTgtLA
{
public:
	void bfmeRunLA(BfmeArgLA arg, void *first, void *last);
};

class BfmeOwnLA
{
public:
	void bfmeFwdLA(BfmePairLA pair);

	BfmeTgtLA *m_bfmeTgtLA;
	BfmeArgLA m_bfmeArgLA;
};

void BfmeOwnLA::bfmeFwdLA(BfmePairLA pair)
{
	if (m_bfmeTgtLA)
		m_bfmeTgtLA->bfmeRunLA(m_bfmeArgLA, pair.m_bfmeFirstLA, pair.m_bfmeLastLA);
}

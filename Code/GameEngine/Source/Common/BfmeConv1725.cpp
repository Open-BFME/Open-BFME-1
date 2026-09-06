class BfmeArgLB
{
public:
	BfmeArgLB(const BfmeArgLB &other) throw()
	{
		m_bfmeALB = other.m_bfmeALB;
		m_bfmeBLB = other.m_bfmeBLB;
	}
	~BfmeArgLB() throw() {}

	int m_bfmeALB;
	int m_bfmeBLB;
};

struct BfmePairLB
{
	void *m_bfmeFirstLB;
	void *m_bfmeLastLB;
};

class BfmeTgtLB
{
public:
	void bfmeRunLB(BfmeArgLB arg, void *first, void *last);
};

class BfmeOwnLB
{
public:
	void bfmeFwdLB(BfmePairLB pair);

	BfmeTgtLB *m_bfmeTgtLB;
	BfmeArgLB m_bfmeArgLB;
};

void BfmeOwnLB::bfmeFwdLB(BfmePairLB pair)
{
	if (m_bfmeTgtLB)
		m_bfmeTgtLB->bfmeRunLB(m_bfmeArgLB, pair.m_bfmeFirstLB, pair.m_bfmeLastLB);
}

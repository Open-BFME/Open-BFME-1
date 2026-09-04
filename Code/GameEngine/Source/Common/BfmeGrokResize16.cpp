// cl: /O2

struct BfmePod16WR
{
	char m_b[16];
};

struct BfmeTagWR
{
};

BfmePod16WR *bfmeCopyWR(BfmePod16WR *first, BfmePod16WR *last, BfmePod16WR *result, const BfmeTagWR &, int *);

class BfmeVecWR
{
public:
	BfmePod16WR *begin() { return m_start; }
	BfmePod16WR *end() { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }

	void resize(unsigned n, BfmePod16WR value);
	void resize(unsigned n);
	void fillInsert(BfmePod16WR *pos, unsigned n, const BfmePod16WR &value);

	BfmePod16WR *m_start;
	BfmePod16WR *m_finish;
	BfmePod16WR *m_end;
};

void BfmeVecWR::resize(unsigned n, BfmePod16WR value)
{
	if (n < size())
	{
		BfmePod16WR *dest = m_start + n;
		m_finish = bfmeCopyWR(end(), end(), dest, *reinterpret_cast<BfmeTagWR *>(&n), (int *)0);
	}
	else
		fillInsert(end(), n - size(), value);
}

void BfmeVecWR::resize(unsigned n)
{
	BfmePod16WR value;
	resize(n, value);
}

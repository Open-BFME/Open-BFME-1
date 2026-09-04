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
	if (n < size())
	{
		BfmePod16WR *dest = m_start + n;
		m_finish = bfmeCopyWR(end(), end(), dest,
			*reinterpret_cast<BfmeTagWR *>(&n), (int *)0);
	}
	else
		fillInsert(end(), n - size(), value);
}

struct BfmePod16WRDefault
{
	int m_words[4];
};

struct BfmeTagWRDefault
{
};

BfmePod16WRDefault *bfmeCopyWRDefault(BfmePod16WRDefault *first,
	BfmePod16WRDefault *last, BfmePod16WRDefault *result,
	const BfmeTagWRDefault &, int *);

class BfmeVecWRDefault
{
public:
	void resize(unsigned n);

private:
	BfmePod16WRDefault *begin() { return m_start; }
	BfmePod16WRDefault *end() { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }
	void fillInsert(BfmePod16WRDefault *pos, unsigned n,
		const BfmePod16WRDefault &value);

	BfmePod16WRDefault *m_start;
	BfmePod16WRDefault *m_finish;
	BfmePod16WRDefault *m_end;
};

void BfmeVecWRDefault::resize(unsigned n)
{
	BfmePod16WRDefault value = {};
	if (n < size())
	{
		BfmePod16WRDefault *dest = m_start + n;
		m_finish = bfmeCopyWRDefault(end(), end(), dest,
			*reinterpret_cast<BfmeTagWRDefault *>(&n), (int *)0);
	}
	else
		fillInsert(end(), n - size(), value);
}

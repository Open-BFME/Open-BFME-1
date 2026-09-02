// ?d_00747770@@YAXXZ
// partial score=0.85 date=2026-09-02
// cl: /O2

struct BfmeRecWT
{
	int m_value;
	int m_lo;
	int m_span;
	char m_pad[28];
};

class BfmeFindWT
{
public:
	int find(int key);

private:
	char m_pad[0x80BC];
	int m_count;
	BfmeRecWT m_recs[1];
};

int BfmeFindWT::find(int key)
{
	register int k = key >> 2;
	register int n = m_count;
	register int i = 0;
	if (n <= 0)
		return -1;
	BfmeRecWT *p = &m_recs[0];
	do
	{
		register int lo = p->m_lo;
		if (lo >= 0 && k >= lo && k < lo + p->m_span)
			return m_recs[i].m_value;
		++p;
		++i;
	}
	while (i < n);
	return -1;
}

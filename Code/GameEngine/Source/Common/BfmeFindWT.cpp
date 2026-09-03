// cl: /O2
// ?find@BfmeFindWT@@QAEHH@Z

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
	key >>= 2;
	int n = m_count;
	int i = 0;
	if (n > 0)
	{
		int *p = &m_recs[0].m_lo;
		do
		{
			int lo = *p;
			if (lo >= 0)
			{
				if (key >= lo)
				{
					int hi = lo + p[1];
					if (key < hi)
						return m_recs[i].m_value;
				}
			}
			++i;
			p += 10;
		}
		while (i < n);
	}
	return -1;
}

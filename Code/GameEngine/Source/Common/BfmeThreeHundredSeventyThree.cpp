struct BfmeNodeXC
{
	BfmeNodeXC *m_bfmeNext;
	BfmeNodeXC *m_bfmePrev;
	unsigned short m_bfmeKey;
};

void bfmeFreeSizedXC(void *what, unsigned int bytes);

class BfmeListXC
{
public:
	void bfmeEraseXC(unsigned short *key);
	BfmeNodeXC *m_bfmeEnd;
};

void BfmeListXC::bfmeEraseXC(unsigned short *key)
{
	BfmeNodeXC *end = m_bfmeEnd;
	BfmeNodeXC *at = end->m_bfmeNext;
	while (at != end)
	{
		BfmeNodeXC *next = at->m_bfmeNext;
		if (*key == at->m_bfmeKey)
		{
			BfmeNodeXC *prev = at->m_bfmePrev;
			prev->m_bfmeNext = next;
			next->m_bfmePrev = prev;
			bfmeFreeSizedXC(at, 0xc);
		}
		at = next;
	}
}

struct BfmePairCXD
{
	void *m_bfmeA;
	void *m_bfmeB;
};

void bfmeCallCXD(BfmePairCXD *item, void *a, void *b, void *arg);

void bfmeGoCXD(BfmePairCXD *begin, BfmePairCXD *end, void *arg)
{
	while (begin != end)
	{
		bfmeCallCXD(begin, begin->m_bfmeA, begin->m_bfmeB, arg);
		++begin;
	}
}

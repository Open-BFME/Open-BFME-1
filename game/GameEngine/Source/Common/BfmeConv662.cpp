struct BfmePairCXC
{
	void *m_bfmeA;
	void *m_bfmeB;
};

void bfmeCallCXC(BfmePairCXC *item, void *a, void *b, void *arg);

void bfmeGoCXC(BfmePairCXC *begin, BfmePairCXC *end, void *spare, void *arg)
{
	while (begin != end)
	{
		bfmeCallCXC(begin, begin->m_bfmeA, begin->m_bfmeB, arg);
		++begin;
	}
}

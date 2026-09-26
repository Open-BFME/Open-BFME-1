struct BfmePairCXA
{
	void *m_bfmeA;
	void *m_bfmeB;
};

void bfmeCallCXA(BfmePairCXA *item, void *a, void *b, void *arg);

void bfmeGoCXA(BfmePairCXA *begin, BfmePairCXA *end, void *spare, void *arg)
{
	while (begin != end)
	{
		bfmeCallCXA(begin, begin->m_bfmeA, begin->m_bfmeB, arg);
		++begin;
	}
}

struct BfmePairCXB
{
	void *m_bfmeA;
	void *m_bfmeB;
};

void bfmeCallCXB(BfmePairCXB *item, void *a, void *b, void *arg);

void bfmeGoCXB(BfmePairCXB *begin, BfmePairCXB *end, void *arg)
{
	while (begin != end)
	{
		bfmeCallCXB(begin, begin->m_bfmeA, begin->m_bfmeB, arg);
		++begin;
	}
}

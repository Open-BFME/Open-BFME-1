struct BfmeDestWE
{
	unsigned char m_bfmeHead[4];
	unsigned char m_bfmeField[4];
};

class BfmeSubWE
{
public:
	void bfmeTwoWE(void *what);
	unsigned char m_bfmeHead[4];
};

struct BfmeNodeWE
{
	unsigned char m_bfmeHead[4];
	BfmeSubWE m_bfmeSub;
	unsigned char m_bfmeRest[8];
	void bfmeOneWE(BfmeDestWE *to);
};

void bfmeCopyWE(BfmeNodeWE *first, BfmeNodeWE *last, BfmeDestWE *to)
{
	while (first != last)
	{
		first->bfmeOneWE(to);
		first->m_bfmeSub.bfmeTwoWE(&to->m_bfmeField);
		++first;
	}
}

BfmeNodeWE *bfmeUninitCopyWE(BfmeNodeWE *first, BfmeNodeWE *last, BfmeNodeWE *to)
{
	int count = last - first;

	while (count > 0)
	{
		to->bfmeOneWE((BfmeDestWE *)first);
		to->m_bfmeSub.bfmeTwoWE(&first->m_bfmeSub);
		++first;
		++to;
		--count;
	}

	return to;
}

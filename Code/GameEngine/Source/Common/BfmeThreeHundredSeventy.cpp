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

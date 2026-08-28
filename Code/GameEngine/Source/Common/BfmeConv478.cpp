struct BfmeSubBKC
{
	void bfmeDoBKC(void *what, int flag);
	unsigned char m_bfmeHead[4];
};

struct BfmeThingBKC
{
	unsigned char m_bfmeHead[0x50];
	BfmeSubBKC m_bfmeSub;
};

void bfmeGoBKC(void *one, BfmeThingBKC *two)
{
	if (two != 0)
		two->m_bfmeSub.bfmeDoBKC(one, 0);
}

class BfmeSubCJH
{
public:
	void bfmeDtorCJH();
};

class BfmeThingCJH
{
public:
	void bfmeTailCJH();
	void bfmeGoCJH();
	unsigned char m_bfmeHead[0x90];
	BfmeSubCJH *m_bfmeSub;
};

void bfmeFreeCJH(void *what);

void BfmeThingCJH::bfmeGoCJH()
{
	BfmeSubCJH *sub = m_bfmeSub;
	if (sub != 0)
	{
		sub->bfmeDtorCJH();
		bfmeFreeCJH(sub);
	}
	m_bfmeSub = 0;
	bfmeTailCJH();
}

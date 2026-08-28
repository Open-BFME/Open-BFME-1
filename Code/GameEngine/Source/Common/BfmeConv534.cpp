class BfmeInnerBUE
{
public:
	virtual void bfmeSpareBUE0();
	virtual void bfmeRunBUE(void *what);
};

struct BfmeSubBUE
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerBUE m_bfmeInner;
};

class BfmeOuterBUE
{
public:
	bool bfmeAskBUE();
};

class BfmeThingBUE
{
public:
	void bfmeGoBUE(void *what);
	unsigned char m_bfmeHead[0xd0];
	BfmeSubBUE *m_bfmeSub;
};

void BfmeThingBUE::bfmeGoBUE(void *what)
{
	if (((BfmeOuterBUE *)((char *)this - 0x10))->bfmeAskBUE())
		m_bfmeSub->m_bfmeInner.bfmeRunBUE(what);
}

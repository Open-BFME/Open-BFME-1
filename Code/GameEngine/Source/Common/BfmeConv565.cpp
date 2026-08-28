class BfmeInnerCAE
{
public:
	virtual void bfmeSpareCAE0();
	virtual void bfmeSpareCAE1();
	virtual void bfmeSpareCAE2();
	virtual void bfmeSpareCAE3();
	virtual void bfmeSpareCAE4();
	virtual void bfmeSpareCAE5();
	virtual void bfmeSpareCAE6();
	virtual void bfmeSpareCAE7();
	virtual int bfmeRunCAE();
};

struct BfmeSubCAE
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerCAE m_bfmeInner;
};

class BfmeOuterCAE
{
public:
	bool bfmeAskCAE();
};

class BfmeThingCAE
{
public:
	int bfmeGoCAE();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubCAE *m_bfmeSub;
};

int BfmeThingCAE::bfmeGoCAE()
{
	if (((BfmeOuterCAE *)((char *)this - 0x10))->bfmeAskCAE())
		return m_bfmeSub->m_bfmeInner.bfmeRunCAE();
	return 3;
}

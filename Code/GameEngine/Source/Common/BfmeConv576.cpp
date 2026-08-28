class BfmeInnerCCE
{
public:
	virtual void bfmeSpareCCE0();
	virtual void bfmeSpareCCE1();
	virtual void bfmeSpareCCE2();
	virtual void bfmeSpareCCE3();
	virtual void bfmeSpareCCE4();
	virtual void bfmeSpareCCE5();
	virtual void bfmeSpareCCE6();
	virtual void bfmeSpareCCE7();
	virtual void bfmeSpareCCE8();
	virtual void bfmeSpareCCE9();
	virtual void bfmeSpareCCE10();
	virtual void bfmeSpareCCE11();
	virtual void bfmeSpareCCE12();
	virtual void bfmeSpareCCE13();
	virtual void bfmeSpareCCE14();
	virtual void bfmeSpareCCE15();
	virtual void bfmeSpareCCE16();
	virtual void bfmeSpareCCE17();
	virtual void bfmeSpareCCE18();
	virtual bool bfmeRunCCE();
};

struct BfmeSubCCE
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerCCE m_bfmeInner;
};

class BfmeOuterCCE
{
public:
	bool bfmeAskCCE();
};

class BfmeThingCCE
{
public:
	int bfmeGoCCE();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubCCE *m_bfmeSub;
};

int BfmeThingCCE::bfmeGoCCE()
{
	if (((BfmeOuterCCE *)((char *)this - 0x10))->bfmeAskCCE())
		return m_bfmeSub->m_bfmeInner.bfmeRunCCE();
	return 0;
}

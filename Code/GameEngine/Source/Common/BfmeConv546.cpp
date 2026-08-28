class BfmeSubBWE
{
public:
	virtual void bfmeSpareBWE0();
	virtual void bfmeSpareBWE1();
	virtual void bfmeSpareBWE2();
	virtual void bfmeSpareBWE3();
	virtual void bfmeSpareBWE4();
	virtual void bfmeSpareBWE5();
	virtual void bfmeSpareBWE6();
	virtual void bfmeSpareBWE7();
	virtual void bfmeSpareBWE8();
	virtual void bfmeSpareBWE9();
	virtual void bfmeSpareBWE10();
	virtual void bfmeSpareBWE11();
	virtual void bfmeSpareBWE12();
	virtual void bfmeSpareBWE13();
	virtual void bfmeSpareBWE14();
	virtual void bfmeSpareBWE15();
	virtual void bfmeSpareBWE16();
	virtual void bfmeSpareBWE17();
	virtual void bfmeSpareBWE18();
	virtual void bfmeSpareBWE19();
	virtual void bfmeSpareBWE20();
	virtual void bfmeSpareBWE21();
	virtual void bfmeSpareBWE22();
	virtual void bfmeSpareBWE23();
	virtual void bfmeSpareBWE24();
	virtual void bfmeSpareBWE25();
	virtual void bfmeSpareBWE26();
	virtual void bfmeSpareBWE27();
	virtual void bfmeSpareBWE28();
	virtual void bfmeSpareBWE29();
	virtual void bfmeSpareBWE30();
	virtual void bfmeSpareBWE31();
	virtual void bfmeSpareBWE32();
	virtual void bfmeSpareBWE33();
	virtual void bfmeSpareBWE34();
	virtual void bfmeSpareBWE35();
	virtual void bfmeSpareBWE36();
	virtual void bfmeSpareBWE37();
	virtual void bfmeSpareBWE38();
	virtual void bfmeSpareBWE39();
	virtual bool bfmeAskBWE();
};

struct BfmeMidBWE
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubBWE *m_bfmeSub;
};

struct BfmeHolderBWE
{
	unsigned char m_bfmeHead[0x214];
	BfmeMidBWE *m_bfmeMid;
};

struct BfmeOuterBWE
{
	BfmeHolderBWE *m_bfmeHolder;
};

class BfmeThingBWE
{
public:
	bool bfmeGoBWE();
};

bool BfmeThingBWE::bfmeGoBWE()
{
	BfmeMidBWE *mid = ((BfmeOuterBWE *)((char *)this - 0x18))->m_bfmeHolder->m_bfmeMid;
	if (mid)
	{
		BfmeSubBWE *sub = mid->m_bfmeSub;
		if (sub)
			return sub->bfmeAskBWE();
	}
	return false;
}

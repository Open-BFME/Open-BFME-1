class BfmeInnerDHC
{
public:
	virtual void bfmeSpareDHC0();
	virtual void bfmeSpareDHC1();
	virtual void bfmeSpareDHC2();
	virtual void bfmeSpareDHC3();
	virtual void bfmeSpareDHC4();
	virtual void bfmeSpareDHC5();
	virtual void bfmeSpareDHC6();
	virtual void bfmeSpareDHC7();
	virtual void bfmeSpareDHC8();
	virtual void bfmeSpareDHC9();
	virtual void bfmeSpareDHC10();
	virtual void bfmeSpareDHC11();
	virtual void bfmeSpareDHC12();
	virtual void bfmeSpareDHC13();
	virtual void bfmeSpareDHC14();
	virtual void bfmeSpareDHC15();
	virtual void bfmeSpareDHC16();
	virtual void bfmeSpareDHC17();
	virtual int bfmeRunDHC();
};

struct BfmeSubDHC
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerDHC m_bfmeInner;
};

class BfmeOuterDHC
{
public:
	bool bfmeAskDHC();
};

class BfmeThingDHC
{
public:
	int bfmeGoDHC();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubDHC *m_bfmeSub;
};

int BfmeThingDHC::bfmeGoDHC()
{
	if (((BfmeOuterDHC *)((char *)this - 0x10))->bfmeAskDHC())
		return m_bfmeSub->m_bfmeInner.bfmeRunDHC();
	return 0;
}

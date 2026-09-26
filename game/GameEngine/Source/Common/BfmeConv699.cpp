class BfmeInnerDHB
{
public:
	virtual void bfmeSpareDHB0();
	virtual void bfmeSpareDHB1();
	virtual void bfmeSpareDHB2();
	virtual void bfmeSpareDHB3();
	virtual void bfmeSpareDHB4();
	virtual void bfmeSpareDHB5();
	virtual void bfmeSpareDHB6();
	virtual void bfmeSpareDHB7();
	virtual void bfmeSpareDHB8();
	virtual void bfmeSpareDHB9();
	virtual void bfmeSpareDHB10();
	virtual void bfmeSpareDHB11();
	virtual void bfmeSpareDHB12();
	virtual void bfmeSpareDHB13();
	virtual void bfmeSpareDHB14();
	virtual int bfmeRunDHB();
};

struct BfmeSubDHB
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerDHB m_bfmeInner;
};

class BfmeOuterDHB
{
public:
	bool bfmeAskDHB();
};

class BfmeThingDHB
{
public:
	int bfmeGoDHB();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubDHB *m_bfmeSub;
};

int BfmeThingDHB::bfmeGoDHB()
{
	if (((BfmeOuterDHB *)((char *)this - 0x10))->bfmeAskDHB())
		return m_bfmeSub->m_bfmeInner.bfmeRunDHB();
	return 0;
}

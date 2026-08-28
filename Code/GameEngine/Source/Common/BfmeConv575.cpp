class BfmeInnerCCD
{
public:
	virtual void bfmeSpareCCD0();
	virtual void bfmeSpareCCD1();
	virtual void bfmeSpareCCD2();
	virtual void bfmeSpareCCD3();
	virtual void bfmeSpareCCD4();
	virtual void bfmeSpareCCD5();
	virtual void bfmeSpareCCD6();
	virtual void bfmeSpareCCD7();
	virtual void bfmeSpareCCD8();
	virtual void bfmeSpareCCD9();
	virtual void bfmeSpareCCD10();
	virtual void bfmeSpareCCD11();
	virtual void bfmeSpareCCD12();
	virtual void bfmeSpareCCD13();
	virtual void bfmeSpareCCD14();
	virtual void bfmeSpareCCD15();
	virtual void bfmeSpareCCD16();
	virtual void bfmeSpareCCD17();
	virtual void bfmeSpareCCD18();
	virtual bool bfmeRunCCD();
};

struct BfmeSubCCD
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerCCD m_bfmeInner;
};

class BfmeOuterCCD
{
public:
	bool bfmeAskCCD();
};

class BfmeThingCCD
{
public:
	int bfmeGoCCD();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubCCD *m_bfmeSub;
};

int BfmeThingCCD::bfmeGoCCD()
{
	if (((BfmeOuterCCD *)((char *)this - 0x10))->bfmeAskCCD())
		return m_bfmeSub->m_bfmeInner.bfmeRunCCD();
	return 0;
}

class BfmeSubCQB
{
public:
	virtual void bfmeSpareCQB0();
	virtual void bfmeTwoCQB();
	virtual void bfmeSpareCQB2();
	virtual void bfmeSpareCQB3();
	virtual void bfmeSpareCQB4();
	virtual void bfmeSpareCQB5();
	virtual void bfmeSpareCQB6();
	virtual void bfmeSpareCQB7();
	virtual void bfmeSpareCQB8();
	virtual void bfmeSpareCQB9();
	virtual void bfmeSpareCQB10();
	virtual void bfmeSpareCQB11();
	virtual void bfmeSpareCQB12();
	virtual void bfmeSpareCQB13();
	virtual void bfmeSpareCQB14();
	virtual void bfmeSpareCQB15();
	virtual void bfmeSpareCQB16();
	virtual void bfmeOneCQB(void *what, int value);
};

struct BfmeMidCQB
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubCQB *m_bfmeSub;
};

struct BfmeOwnerCQB
{
	unsigned char m_bfmeHead[0x214];
	BfmeMidCQB *m_bfmeMid;
};

class BfmeThingCQB
{
public:
	void bfmeGoCQB(void *what);
	unsigned char m_bfmeHead[8];
	BfmeOwnerCQB *m_bfmeOwner;
};

void BfmeThingCQB::bfmeGoCQB(void *what)
{
	BfmeMidCQB *mid = m_bfmeOwner->m_bfmeMid;
	if (mid != 0)
	{
		mid->m_bfmeSub->bfmeOneCQB(what, 0);
		mid->m_bfmeSub->bfmeTwoCQB();
	}
}

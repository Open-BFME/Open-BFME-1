class BfmeInnerBVF
{
public:
	virtual void bfmeSpareBVF0();
	virtual void bfmeSpareBVF1();
	virtual void bfmeSpareBVF2();
	virtual void bfmeSpareBVF3();
	virtual void bfmeSpareBVF4();
	virtual void bfmeSpareBVF5();
	virtual void bfmeSpareBVF6();
	virtual void bfmeSpareBVF7();
	virtual void bfmeSpareBVF8();
	virtual void bfmeSpareBVF9();
	virtual void bfmeSpareBVF10();
	virtual void bfmeSpareBVF11();
	virtual void bfmeSpareBVF12();
	virtual void bfmeSpareBVF13();
	virtual void bfmeSpareBVF14();
	virtual void bfmeSpareBVF15();
	virtual int bfmeRunBVF();
};

struct BfmeSubBVF
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerBVF m_bfmeInner;
};

class BfmeOuterBVF
{
public:
	bool bfmeAskBVF();
};

class BfmeThingBVF
{
public:
	int bfmeGoBVF();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubBVF *m_bfmeSub;
};

int BfmeThingBVF::bfmeGoBVF()
{
	if (((BfmeOuterBVF *)((char *)this - 0x10))->bfmeAskBVF())
		return m_bfmeSub->m_bfmeInner.bfmeRunBVF();
	return -1;
}

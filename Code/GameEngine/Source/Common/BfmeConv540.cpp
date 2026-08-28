class BfmeInnerBVG
{
public:
	virtual void bfmeSpareBVG0();
	virtual void bfmeSpareBVG1();
	virtual void bfmeSpareBVG2();
	virtual void bfmeSpareBVG3();
	virtual void bfmeSpareBVG4();
	virtual void bfmeSpareBVG5();
	virtual void bfmeSpareBVG6();
	virtual void bfmeSpareBVG7();
	virtual void bfmeSpareBVG8();
	virtual void bfmeSpareBVG9();
	virtual void bfmeSpareBVG10();
	virtual void bfmeSpareBVG11();
	virtual void bfmeSpareBVG12();
	virtual void bfmeSpareBVG13();
	virtual void bfmeSpareBVG14();
	virtual void bfmeSpareBVG15();
	virtual void bfmeSpareBVG16();
	virtual int bfmeRunBVG();
};

struct BfmeSubBVG
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerBVG m_bfmeInner;
};

class BfmeOuterBVG
{
public:
	bool bfmeAskBVG();
};

class BfmeThingBVG
{
public:
	int bfmeGoBVG();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubBVG *m_bfmeSub;
};

int BfmeThingBVG::bfmeGoBVG()
{
	if (((BfmeOuterBVG *)((char *)this - 0x10))->bfmeAskBVG())
		return m_bfmeSub->m_bfmeInner.bfmeRunBVG();
	return -1;
}

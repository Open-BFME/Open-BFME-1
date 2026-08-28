class BfmeSubCOA
{
public:
	virtual void bfmeSpareCOA0();
	virtual void bfmeSpareCOA1();
	virtual void bfmeSpareCOA2();
	virtual void bfmeSpareCOA3();
	virtual void bfmeSpareCOA4();
	virtual void bfmeSpareCOA5();
	virtual void bfmeSpareCOA6();
	virtual void bfmeSpareCOA7();
	virtual void bfmeV8COA(int flag);
	virtual void bfmeV9COA();
	virtual void bfmeSpareCOA10();
	virtual void bfmeV11COA();
	virtual void bfmeSpareCOA12();
	virtual void bfmeV13COA();
};

class BfmeThingCOA
{
public:
	void bfmeTailCOA(void *value, int flag);
	void bfmeGoCOA();
	unsigned char m_bfmeHead[8];
	void *m_bfmeVal;
	unsigned char m_bfmeGap[0x14];
	BfmeSubCOA m_bfmeSub;
	unsigned char m_bfmeGap2[0xc];
	bool m_bfmeFlag;
};

void BfmeThingCOA::bfmeGoCOA()
{
	BfmeSubCOA *sub = &m_bfmeSub;
	m_bfmeFlag = false;
	sub->bfmeV11COA();
	sub->bfmeV13COA();
	sub->bfmeV9COA();
	sub->bfmeV8COA(1);
	bfmeTailCOA(m_bfmeVal, 1);
}

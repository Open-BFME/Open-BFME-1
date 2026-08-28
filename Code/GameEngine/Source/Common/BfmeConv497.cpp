class BfmeInnerBNF
{
public:
	virtual void bfmeSpareBNF0();
	virtual void bfmeSpareBNF1();
	virtual void bfmeSpareBNF2();
	virtual void bfmeSpareBNF3();
	virtual void bfmeSpareBNF4();
	virtual void bfmeSpareBNF5();
	virtual void bfmeSpareBNF6();
	virtual void bfmeSpareBNF7();
	virtual void bfmeSpareBNF8();
	virtual void bfmeStepBNF();
};

class BfmeThingBNF
{
public:
	void bfmeTailBNF();
	void bfmeGoBNF();
	unsigned char m_bfmeHead[0x10];
	BfmeInnerBNF m_bfmeInner;
	unsigned char m_bfmeGap[0xc];
	bool m_bfmeFlag;
};

void BfmeThingBNF::bfmeGoBNF()
{
	if (m_bfmeFlag)
		m_bfmeInner.bfmeStepBNF();
	bfmeTailBNF();
}

class BfmeSubBJB
{
public:
	virtual void bfmeSpareBJB0();
	virtual void bfmeSpareBJB1();
	virtual void bfmeSpareBJB2();
	virtual void bfmeSpareBJB3();
	virtual void bfmeSpareBJB4();
	virtual void bfmeSpareBJB5();
	virtual void bfmeSpareBJB6();
	virtual void bfmeSpareBJB7();
	virtual void bfmeRunBJB();
};

class BfmeThingBJB
{
public:
	bool bfmeAskBJB();
	void bfmeGoBJB();
	unsigned char m_bfmeHead[0x4c];
	BfmeSubBJB *m_bfmeSub;
};

void BfmeThingBJB::bfmeGoBJB()
{
	if (bfmeAskBJB())
		m_bfmeSub->bfmeRunBJB();
}

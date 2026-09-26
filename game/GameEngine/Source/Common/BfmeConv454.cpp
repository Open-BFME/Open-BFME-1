struct BfmeSubBFF
{
	void bfmeStepBFF();
	unsigned char m_bfmeHead[4];
};

class BfmeThingBFF
{
public:
	virtual void bfmeSpareBFF0();
	virtual void bfmeSpareBFF1();
	virtual void bfmeSpareBFF2();
	virtual void bfmeSpareBFF3();
	virtual void bfmeTailBFF();
	void bfmeGoBFF();
	BfmeSubBFF m_bfmeSub;
};

void BfmeThingBFF::bfmeGoBFF()
{
	m_bfmeSub.bfmeStepBFF();
	bfmeTailBFF();
}

class BfmeThingBCB
{
public:
	virtual void bfmeSpareBCB0();
	virtual void bfmeSpareBCB1();
	virtual void bfmeSpareBCB2();
	virtual void bfmeSpareBCB3();
	virtual void bfmeTailBCB();
	void bfmeStepBCB();
	void bfmeGoBCB();
};

void BfmeThingBCB::bfmeGoBCB()
{
	bfmeStepBCB();
	bfmeTailBCB();
}

class BfmeSubCGE;
class BfmeThingCGE
{
public:
	virtual void bfmeSpareCGE0();
	virtual void bfmeSpareCGE1();
	virtual void bfmeSpareCGE2();
	virtual void bfmeSpareCGE3();
	virtual void bfmeSpareCGE4();
	virtual void bfmeSpareCGE5();
	virtual void bfmeSpareCGE6();
	virtual void bfmeSpareCGE7();
	virtual void bfmeSpareCGE8();
	virtual void bfmeSpareCGE9();
	virtual bool bfmeAskCGE();
	virtual void bfmeStepCGE();
	int bfmeGoCGE();
	unsigned char m_bfmeGap[0x10];
	BfmeSubCGE *m_bfmeSub;
};

int bfmeMakeCGE(BfmeSubCGE *sub);

int BfmeThingCGE::bfmeGoCGE()
{
	if (!bfmeAskCGE())
		bfmeStepCGE();
	BfmeSubCGE *sub = m_bfmeSub;
	if (sub == 0)
		return 0;
	return bfmeMakeCGE(sub);
}

class BfmeThingCFE;
class BfmeSubCFE
{
public:
	void bfmeAddCFE(void *what, int value);
};

class BfmeThingCFE
{
public:
	virtual void bfmeSpareCFE0();
	virtual void bfmeSpareCFE1();
	virtual void bfmeSpareCFE2();
	virtual void bfmeSpareCFE3();
	virtual void bfmeSpareCFE4();
	virtual void bfmeSpareCFE5();
	virtual void bfmeSpareCFE6();
	virtual void bfmeSpareCFE7();
	virtual void bfmeSpareCFE8();
	virtual void bfmeSpareCFE9();
	virtual void bfmeSpareCFE10();
	virtual void bfmeSpareCFE11();
	virtual void bfmeSpareCFE12();
	virtual void bfmeSpareCFE13();
	virtual void bfmeSpareCFE14();
	virtual void bfmeSpareCFE15();
	virtual void bfmeSpareCFE16();
	virtual void bfmeStepCFE();
	virtual void bfmeSpareCFE18();
	virtual void bfmeSpareCFE19();
	virtual void bfmeSpareCFE20();
	virtual void bfmeSpareCFE21();
	virtual void bfmeSpareCFE22();
	virtual void bfmeSpareCFE23();
	virtual void bfmeSpareCFE24();
	virtual void bfmeSpareCFE25();
	virtual void bfmeSpareCFE26();
	virtual int bfmeAskCFE(void *what);
	void bfmeGoCFE(void *what);
	unsigned char m_bfmeGap[0x1c];
	BfmeSubCFE m_bfmeSub;
};

void BfmeThingCFE::bfmeGoCFE(void *what)
{
	if (bfmeAskCFE(what))
	{
		bfmeStepCFE();
		m_bfmeSub.bfmeAddCFE(what, 0);
	}
}

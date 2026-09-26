class BfmeXCQE;

class BfmeArgCQE
{
public:
	virtual void bfmeSpareCQE0();
	virtual void bfmeSpareCQE1();
	virtual void bfmeSpareCQE2();
	virtual void bfmeSpareCQE3();
	virtual void bfmeSpareCQE4();
	virtual void bfmeSpareCQE5();
	virtual void bfmeSpareCQE6();
	virtual void bfmeSpareCQE7();
	virtual void bfmeSpareCQE8();
	virtual void bfmeSpareCQE9();
	virtual BfmeXCQE *bfmeGetCQE();
};

class BfmeXCQE
{
public:
	char bfmeKindCQE();
	void bfmeRunCQE(int value);
};

class BfmeSubCQE
{
public:
	void bfmeAddCQE(BfmeArgCQE *what);
};

class BfmeThingCQE
{
public:
	void bfmeGoCQE(BfmeArgCQE *what);
	unsigned char m_bfmeHead[0x20];
	BfmeSubCQE m_bfmeSub;
};

void BfmeThingCQE::bfmeGoCQE(BfmeArgCQE *what)
{
	m_bfmeSub.bfmeAddCQE(what);
	BfmeXCQE *x = what->bfmeGetCQE();
	if (x == 0)
		return;
	if (x->bfmeKindCQE() != 1)
		return;
	x->bfmeRunCQE(0);
}

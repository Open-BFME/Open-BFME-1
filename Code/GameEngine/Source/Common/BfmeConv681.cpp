class BfmeSubDEE;
class BfmeGlobalDEE
{
public:
	virtual void bfmeSpareDEE0();
	virtual void bfmeSpareDEE1();
	virtual void bfmeSpareDEE2();
	virtual void bfmeSpareDEE3();
	virtual void bfmeSpareDEE4();
	virtual void bfmeSpareDEE5();
	virtual void bfmeSpareDEE6();
	virtual void bfmeSpareDEE7();
	virtual void bfmeSpareDEE8();
	virtual void bfmeSpareDEE9();
	virtual void bfmeSpareDEE10();
	virtual void bfmeSpareDEE11();
	virtual void bfmeSpareDEE12();
	virtual void bfmeSpareDEE13();
	virtual void bfmeSpareDEE14();
	virtual void bfmeSpareDEE15();
	virtual void bfmeSpareDEE16();
	virtual void bfmeSpareDEE17();
	virtual void bfmeSpareDEE18();
	virtual void bfmeSpareDEE19();
	virtual void bfmeSpareDEE20();
	virtual void bfmeSpareDEE21();
	virtual void bfmeSpareDEE22();
	virtual void bfmeSpareDEE23();
	virtual void bfmeSpareDEE24();
	virtual void bfmeSpareDEE25();
	virtual void bfmeSpareDEE26();
	virtual void bfmeSpareDEE27();
	virtual void bfmeSpareDEE28();
	virtual void bfmeSpareDEE29();
	virtual void bfmeSpareDEE30();
	virtual void bfmeSpareDEE31();
	virtual void bfmeSpareDEE32();
	virtual void bfmeSpareDEE33();
	virtual void bfmeSpareDEE34();
	virtual void bfmeSpareDEE35();
	virtual void bfmeSpareDEE36();
	virtual void bfmeSpareDEE37();
	virtual void bfmeSpareDEE38();
	virtual void bfmeSpareDEE39();
	virtual void bfmeSpareDEE40();
	virtual void bfmeRunDEE(BfmeSubDEE *sub, int flag);
};

extern BfmeGlobalDEE *bfmeTheDEE;

class BfmeSubDEE
{
	unsigned char m_bfmeHead[4];
};

struct BfmeThingDEE
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubDEE m_bfmeSub;
};

void __stdcall bfmeGoDEE(BfmeThingDEE *a)
{
	bfmeTheDEE->bfmeRunDEE(&a->m_bfmeSub, 1);
}

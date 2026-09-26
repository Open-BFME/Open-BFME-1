class BfmeInnerCFC
{
public:
	virtual void bfmeSpareCFC0();
	virtual void bfmeSpareCFC1();
	virtual void bfmeSpareCFC2();
	virtual void bfmeSpareCFC3();
	virtual void bfmeSpareCFC4();
	virtual void bfmeSpareCFC5();
	virtual void bfmeSpareCFC6();
	virtual void bfmeSpareCFC7();
	virtual void bfmeSpareCFC8();
	virtual void bfmeSpareCFC9();
	virtual void bfmeSpareCFC10();
	virtual void bfmeSpareCFC11();
	virtual void bfmeSpareCFC12();
	virtual void bfmeSpareCFC13();
	virtual void bfmeSpareCFC14();
	virtual void bfmeSpareCFC15();
	virtual void bfmeSpareCFC16();
	virtual void bfmeSpareCFC17();
	virtual void bfmeSpareCFC18();
	virtual void bfmeSpareCFC19();
	virtual void bfmeSpareCFC20();
	virtual void bfmeSpareCFC21();
	virtual void bfmeSpareCFC22();
	virtual void bfmeSpareCFC23();
	virtual void bfmeSpareCFC24();
	virtual void bfmeSpareCFC25();
	virtual void bfmeSpareCFC26();
	virtual void bfmeSpareCFC27();
	virtual void bfmeSpareCFC28();
	virtual void bfmeSpareCFC29();
	virtual void bfmeSpareCFC30();
	virtual void bfmeSpareCFC31();
	virtual void bfmeSpareCFC32();
	virtual void bfmeSpareCFC33();
	virtual bool bfmeRunCFC();
};

struct BfmeSubCFC
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerCFC m_bfmeInner;
};

class BfmeOuterCFC
{
public:
	bool bfmeAskCFC();
};

class BfmeThingCFC
{
public:
	int bfmeGoCFC();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubCFC *m_bfmeSub;
};

int BfmeThingCFC::bfmeGoCFC()
{
	if (((BfmeOuterCFC *)((char *)this - 0x10))->bfmeAskCFC())
		return m_bfmeSub->m_bfmeInner.bfmeRunCFC();
	return 0;
}

class BfmeInnerDHA
{
public:
	virtual void bfmeSpareDHA0();
	virtual void bfmeSpareDHA1();
	virtual void bfmeSpareDHA2();
	virtual void bfmeSpareDHA3();
	virtual void bfmeSpareDHA4();
	virtual void bfmeSpareDHA5();
	virtual void bfmeSpareDHA6();
	virtual void bfmeSpareDHA7();
	virtual void bfmeSpareDHA8();
	virtual void bfmeSpareDHA9();
	virtual void bfmeSpareDHA10();
	virtual void bfmeSpareDHA11();
	virtual void bfmeSpareDHA12();
	virtual void bfmeSpareDHA13();
	virtual void bfmeSpareDHA14();
	virtual void bfmeSpareDHA15();
	virtual void bfmeSpareDHA16();
	virtual void bfmeSpareDHA17();
	virtual void bfmeSpareDHA18();
	virtual void bfmeSpareDHA19();
	virtual void bfmeSpareDHA20();
	virtual void bfmeSpareDHA21();
	virtual void bfmeSpareDHA22();
	virtual void bfmeSpareDHA23();
	virtual void bfmeSpareDHA24();
	virtual void bfmeSpareDHA25();
	virtual void bfmeSpareDHA26();
	virtual void bfmeSpareDHA27();
	virtual void bfmeSpareDHA28();
	virtual int bfmeRunDHA();
};

struct BfmeSubDHA
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerDHA m_bfmeInner;
};

class BfmeOuterDHA
{
public:
	bool bfmeAskDHA();
};

class BfmeThingDHA
{
public:
	int bfmeGoDHA();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubDHA *m_bfmeSub;
};

int BfmeThingDHA::bfmeGoDHA()
{
	if (((BfmeOuterDHA *)((char *)this - 0x10))->bfmeAskDHA())
		return m_bfmeSub->m_bfmeInner.bfmeRunDHA();
	return 0;
}

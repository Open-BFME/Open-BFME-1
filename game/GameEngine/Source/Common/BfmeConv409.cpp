class BfmeInnerAKD
{
public:
	void bfmeJoinAKD(void *who, int one, int two);
};

struct BfmeSubAKD
{
	unsigned char m_bfmeHead[0x20];
	BfmeInnerAKD m_bfmeInner;
};

struct BfmeNodeAKD
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubAKD *m_bfmeSub;
};

class BfmeLookAKD
{
public:
	virtual void bfmeSpareAKD0();
	virtual void bfmeSpareAKD1();
	virtual void bfmeSpareAKD2();
	virtual void bfmeSpareAKD3();
	virtual void bfmeSpareAKD4();
	virtual void bfmeSpareAKD5();
	virtual void bfmeSpareAKD6();
	virtual void bfmeSpareAKD7();
	virtual void bfmeSpareAKD8();
	virtual void bfmeSpareAKD9();
	virtual void bfmeSpareAKD10();
	virtual void bfmeSpareAKD11();
	virtual void bfmeSpareAKD12();
	virtual void bfmeSpareAKD13();
	virtual void bfmeSpareAKD14();
	virtual void bfmeSpareAKD15();
	virtual void bfmeSpareAKD16();
	virtual void bfmeSpareAKD17();
	virtual void bfmeSpareAKD18();
	virtual void bfmeSpareAKD19();
	virtual void bfmeSpareAKD20();
	virtual void bfmeSpareAKD21();
	virtual void bfmeSpareAKD22();
	virtual void bfmeSpareAKD23();
	virtual void bfmeSpareAKD24();
	virtual void bfmeSpareAKD25();
	virtual BfmeNodeAKD *bfmeFindAKD(void *key);
};

extern BfmeLookAKD *g_bfmeLookAKD;

void __stdcall bfmeGoAKD(void *one, void *two)
{
	BfmeNodeAKD *first = g_bfmeLookAKD->bfmeFindAKD(two);
	BfmeNodeAKD *second = g_bfmeLookAKD->bfmeFindAKD(one);
	if (second != 0 && second->m_bfmeSub != 0 && first != 0)
		second->m_bfmeSub->m_bfmeInner.bfmeJoinAKD(first, 0, 1);
}

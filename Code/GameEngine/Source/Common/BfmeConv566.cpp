class BfmeSubCAF
{
public:
	virtual void bfmeSpareCAF0();
	virtual void bfmeSpareCAF1();
	virtual void bfmeSpareCAF2();
	virtual void bfmeSpareCAF3();
	virtual void bfmeSpareCAF4();
	virtual void bfmeSpareCAF5();
	virtual void bfmeSpareCAF6();
	virtual void bfmeSpareCAF7();
	virtual void bfmeSpareCAF8();
	virtual void bfmeSpareCAF9();
	virtual void bfmeSpareCAF10();
	virtual void bfmeSpareCAF11();
	virtual void bfmeSpareCAF12();
	virtual void bfmeSpareCAF13();
	virtual void bfmeSpareCAF14();
	virtual void bfmeSpareCAF15();
	virtual void bfmeSpareCAF16();
	virtual void bfmeSpareCAF17();
	virtual void bfmeSpareCAF18();
	virtual void bfmeSpareCAF19();
	virtual void bfmeSpareCAF20();
	virtual void bfmeRunCAF(void *one, void *two, void *three);
};

struct BfmeMidCAF
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubCAF *m_bfmeSub;
};

struct BfmeHolderCAF
{
	unsigned char m_bfmeHead[0x214];
	BfmeMidCAF *m_bfmeMid;
};

struct BfmeOuterCAF
{
	BfmeHolderCAF *m_bfmeHolder;
};

class BfmeThingCAF
{
public:
	void bfmeGoCAF(void *one, void *two, void *three);
};

void BfmeThingCAF::bfmeGoCAF(void *one, void *two, void *three)
{
	BfmeHolderCAF *holder = ((BfmeOuterCAF *)((char *)this - 0x18))->m_bfmeHolder;
	if (holder)
	{
		BfmeMidCAF *mid = holder->m_bfmeMid;
		if (mid)
		{
			BfmeSubCAF *sub = mid->m_bfmeSub;
			if (sub)
				sub->bfmeRunCAF(one, two, three);
		}
	}
}

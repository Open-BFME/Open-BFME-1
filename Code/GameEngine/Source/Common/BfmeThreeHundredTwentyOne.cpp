struct BfmeInnerRQ
{
	void bfmeSetRQ(int one, int two);
};

struct BfmeSubRQ
{
	unsigned char m_bfmeHead[0x20];
	BfmeInnerRQ m_bfmeInner;
};

struct BfmeNodeRQ
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubRQ *m_bfmeSub;
};

class BfmeLookRQ
{
public:
	virtual void bfmeSpareRQ0();
	virtual void bfmeSpareRQ1();
	virtual void bfmeSpareRQ2();
	virtual void bfmeSpareRQ3();
	virtual void bfmeSpareRQ4();
	virtual void bfmeSpareRQ5();
	virtual void bfmeSpareRQ6();
	virtual void bfmeSpareRQ7();
	virtual void bfmeSpareRQ8();
	virtual void bfmeSpareRQ9();
	virtual void bfmeSpareRQ10();
	virtual void bfmeSpareRQ11();
	virtual void bfmeSpareRQ12();
	virtual void bfmeSpareRQ13();
	virtual void bfmeSpareRQ14();
	virtual void bfmeSpareRQ15();
	virtual void bfmeSpareRQ16();
	virtual void bfmeSpareRQ17();
	virtual void bfmeSpareRQ18();
	virtual void bfmeSpareRQ19();
	virtual void bfmeSpareRQ20();
	virtual void bfmeSpareRQ21();
	virtual void bfmeSpareRQ22();
	virtual void bfmeSpareRQ23();
	virtual void bfmeSpareRQ24();
	virtual void bfmeSpareRQ25();
	virtual BfmeNodeRQ *bfmeFindRQ(void *key);
};

extern BfmeLookRQ *g_bfmeLookRQ;

void __stdcall bfmeResetRQ(void *key)
{
	BfmeNodeRQ *node = g_bfmeLookRQ->bfmeFindRQ(key);
	if (node == 0)
		return;
	BfmeSubRQ *sub = node->m_bfmeSub;
	if (sub == 0)
		return;
	sub->m_bfmeInner.bfmeSetRQ(0, 1);
}

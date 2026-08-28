class BfmeFoundRP
{
public:
	void bfmeTellRP(void *what);
};

struct BfmeNodeRP
{
	unsigned char m_bfmeHead[0x204];
	BfmeFoundRP *m_bfmeSub;
};

class BfmeLookRP
{
public:
	virtual void bfmeSpareRP0();
	virtual void bfmeSpareRP1();
	virtual void bfmeSpareRP2();
	virtual void bfmeSpareRP3();
	virtual void bfmeSpareRP4();
	virtual void bfmeSpareRP5();
	virtual void bfmeSpareRP6();
	virtual void bfmeSpareRP7();
	virtual void bfmeSpareRP8();
	virtual void bfmeSpareRP9();
	virtual void bfmeSpareRP10();
	virtual void bfmeSpareRP11();
	virtual void bfmeSpareRP12();
	virtual void bfmeSpareRP13();
	virtual void bfmeSpareRP14();
	virtual void bfmeSpareRP15();
	virtual void bfmeSpareRP16();
	virtual void bfmeSpareRP17();
	virtual void bfmeSpareRP18();
	virtual void bfmeSpareRP19();
	virtual void bfmeSpareRP20();
	virtual void bfmeSpareRP21();
	virtual void bfmeSpareRP22();
	virtual void bfmeSpareRP23();
	virtual void bfmeSpareRP24();
	virtual void bfmeSpareRP25();
	virtual BfmeNodeRP *bfmeFindRP(void *key);
};

extern BfmeLookRP *g_bfmeLookRP;

void __stdcall bfmeSendRP(void *key, void *what)
{
	BfmeNodeRP *node = g_bfmeLookRP->bfmeFindRP(key);
	if (node == 0)
		return;
	BfmeFoundRP *sub = node->m_bfmeSub;
	if (sub == 0)
		return;
	sub->bfmeTellRP(what);
}

// Open-BFME5 conversions.

extern char g_bfmeStr1277[];

struct BfmeOpt1277
{
	char m_bfme00;
	char m_bfme01;
	char m_bfme02;
	char m_bfme03;
};

class BfmeS1277
{
public:
	virtual void bfmeVa1277_00();
	virtual void bfmeVa1277_01();
	virtual void bfmeVa1277_02();
	virtual void bfmeVa1277_03();
	virtual void bfmeVa1277_04();
	virtual void bfmeVa1277_05();
	virtual void bfmeVa1277_06();
	virtual void bfmeVa1277_07();
	virtual void bfmeVa1277_08();
	virtual void bfmeVa1277_09();
	virtual void bfmeSet1277(BfmeOpt1277 *o);
	virtual void bfmeVb1277_00();
	virtual void bfmeVb1277_01();
	virtual void bfmeVb1277_02();
	virtual void bfmeVb1277_03();
	virtual void bfmeVb1277_04();
	virtual void bfmeVb1277_05();
	virtual void bfmeVb1277_06();
	virtual void bfmeVb1277_07();
	virtual void bfmeVb1277_08();
	virtual void bfmeVb1277_09();
	virtual void bfmeVb1277_10();
	virtual void bfmeVb1277_11();
	virtual void bfmeVb1277_12();
	virtual void bfmeVb1277_13();
	virtual void bfmeVb1277_14();
	virtual void bfmeVb1277_15();
	virtual void bfmeVb1277_16();
	virtual void bfmeVb1277_17();
	virtual void bfmeVb1277_18();
	virtual void bfmeVb1277_19();
	virtual void bfmeVb1277_20();
	virtual void bfmeVb1277_21();
	virtual void bfmeVb1277_22();
	virtual void bfmeVb1277_23();
	virtual void bfmeVb1277_24();
	virtual void bfmeEmit1277(char *s, void *p, int n);
};

class BfmeA1277
{
public:
	void bfmeGo1277(BfmeS1277 *a);
	char m_bfmePad00[8];
	int m_bfme08;
};

void BfmeA1277::bfmeGo1277(BfmeS1277 *a)
{
	BfmeOpt1277 o;

	o.m_bfme00 = 1;
	o.m_bfme01 = 1;
	a->bfmeSet1277(&o);
	a->bfmeEmit1277(g_bfmeStr1277, &m_bfme08, 4);
}

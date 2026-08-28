extern "C" unsigned char bfmeTextAOA[];

struct BfmeOneAOA
{
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeValue;
};

class BfmeTwoAOA
{
public:
	void *bfmeLookAOA(void *text);
};

class BfmeThreeAOA
{
public:
	virtual void bfmeSpareAOA0();
	virtual void bfmeSpareAOA1();
	virtual void bfmeSpareAOA2();
	virtual void bfmeSpareAOA3();
	virtual void bfmeSpareAOA4();
	virtual void bfmeSpareAOA5();
	virtual void bfmeSpareAOA6();
	virtual void bfmeSpareAOA7();
	virtual void bfmeSpareAOA8();
	virtual void bfmeSpareAOA9();
	virtual void bfmeSpareAOA10();
	virtual void bfmeSpareAOA11();
	virtual void bfmeSpareAOA12();
	virtual void bfmeSpareAOA13();
	virtual void bfmeSpareAOA14();
	virtual void bfmeSpareAOA15();
	virtual void bfmeSpareAOA16();
	virtual void bfmeSpareAOA17();
	virtual void bfmeSpareAOA18();
	virtual void bfmeSpareAOA19();
	virtual void bfmeSpareAOA20();
	virtual void bfmeSpareAOA21();
	virtual void bfmeSpareAOA22();
	virtual void bfmeSpareAOA23();
	virtual void bfmeSpareAOA24();
	virtual void bfmeSpareAOA25();
	virtual void bfmeSpareAOA26();
	virtual void bfmeSpareAOA27();
	virtual void bfmeSpareAOA28();
	virtual void bfmeSpareAOA29();
	virtual void bfmeSpareAOA30();
	virtual void bfmeSpareAOA31();
	virtual void bfmeSpareAOA32();
	virtual void bfmeSpareAOA33();
	virtual void bfmeSpareAOA34();
	virtual void bfmeSpareAOA35();
	virtual void bfmeSpareAOA36();
	virtual void bfmeSpareAOA37();
	virtual void bfmeSpareAOA38();
	virtual void bfmeSpareAOA39();
	virtual void bfmeSpareAOA40();
	virtual void bfmeSpareAOA41();
	virtual void bfmeSpareAOA42();
	virtual void bfmeSpareAOA43();
	virtual void bfmeSpareAOA44();
	virtual void bfmeSpareAOA45();
	virtual void bfmeSpareAOA46();
	virtual void bfmeSpareAOA47();
	virtual void bfmeSpareAOA48();
	virtual void bfmeSpareAOA49();
	virtual void bfmeSpareAOA50();
	virtual void bfmeSpareAOA51();
	virtual void bfmeSpareAOA52();
	virtual void bfmeSpareAOA53();
	virtual void bfmeSpareAOA54();
	virtual void *bfmeMakeAOA(int flag, void *what);
};

extern BfmeOneAOA *g_bfmeOneAOA;
extern BfmeTwoAOA *g_bfmeTwoAOA;
extern BfmeThreeAOA *g_bfmeThreeAOA;

class BfmeThingAOA
{
public:
	bool bfmeAskAOA();
	void bfmeGoAOA();
	unsigned char m_bfmeHead[0x1438];
	void *m_bfmeWhat;
};

void BfmeThingAOA::bfmeGoAOA()
{
	if (g_bfmeOneAOA != 0 && bfmeAskAOA())
	{
		m_bfmeWhat = g_bfmeOneAOA->m_bfmeValue;
		return;
	}
	void *got = g_bfmeTwoAOA->bfmeLookAOA(bfmeTextAOA);
	m_bfmeWhat = g_bfmeThreeAOA->bfmeMakeAOA(0, got);
}

// Open-BFME5 conversions.

class BfmeG1023
{
public:
	virtual void bfmeVG01023();
	virtual void bfmeVG11023();
	virtual void bfmeVG21023();
	virtual void bfmeVG31023();
	virtual void bfmeVG41023();
	virtual void bfmeVG51023();
	virtual void bfmeVG61023();
	virtual void bfmeVG71023();
	virtual void bfmeVG81023();
	virtual void bfmeVG91023();
	virtual void bfmeVG101023();
	virtual void bfmeVG111023();
	virtual void bfmeVG121023();
	virtual void bfmeVG131023();
	virtual void bfmeVG141023();
	virtual void bfmeVG151023();
	virtual void bfmeVG161023();
	virtual void bfmeVG171023();
	virtual void bfmeVG181023();
	virtual void bfmeKill1023(int v);
};

extern BfmeG1023 *g_bfmeG1023;

class BfmeSub1023
{
public:
	char bfmeAsk1023(void);
};

class BfmeA1023
{
public:
	void bfmeGo1023A(void);

	char m_bfmePad[0x20];
	BfmeSub1023 m_bfmeSub;
	char m_bfmePad2[0xb];
	int m_bfmeVal;
};

void BfmeA1023::bfmeGo1023A(void)
{
	if (m_bfmeSub.bfmeAsk1023() != 0)
		g_bfmeG1023->bfmeKill1023(m_bfmeVal);
}

class BfmeC1023
{
public:
	virtual void bfmeVC01023();
	virtual void bfmeVC11023();
	virtual void bfmeVC21023();
	virtual void bfmeVC31023();
	virtual void bfmeVC41023();
	virtual void bfmeVC51023();
	virtual void bfmeVC61023();
	virtual void bfmeVC71023();
	virtual void bfmeVC81023();
	virtual void bfmeVC91023();
	virtual void bfmeStop1023(int n);
};

extern BfmeC1023 *g_bfmeC1023;

class BfmeB1023
{
public:
	void bfmeGo1023B(int a);
	void bfmeApply1023(int a);
};

void BfmeB1023::bfmeGo1023B(int a)
{
	if (g_bfmeC1023 != 0)
		g_bfmeC1023->bfmeStop1023(0);

	bfmeApply1023(a);
}

class BfmeK1023
{
public:
	virtual void bfmeVK01023();
	virtual void bfmeVK11023();
	virtual void bfmeVK21023();
	virtual void bfmeVK31023();
	virtual void bfmeVK41023();
	virtual void bfmeVK51023();
	virtual void bfmeVK61023();
	virtual void bfmeVK71023();
	virtual void bfmeVK81023();
	virtual void bfmeVK91023();
	virtual void bfmeVK101023();
	virtual void bfmeVK111023();
	virtual void bfmeVK121023();
	virtual void bfmeVK131023();
	virtual void bfmeVK141023();
	virtual void bfmeVK151023();
	virtual void bfmeVK161023();
	virtual void bfmeVK171023();
	virtual void bfmeVK181023();
	virtual void bfmeVK191023();
	virtual void bfmeVK201023();
	virtual void bfmeVK211023();
	virtual void bfmeVK221023();
	virtual void bfmeVK231023();
	virtual void bfmeVK241023();
	virtual void bfmeVK251023();
	virtual void bfmeVK261023();
	virtual void bfmeVK271023();
	virtual void bfmeVK281023();
	virtual void bfmeVK291023();
	virtual void bfmeVK301023();
	virtual void bfmeVK311023();
	virtual void bfmeVK321023();
	virtual void bfmeVK331023();
	virtual void bfmeVK341023();
	virtual void bfmeVK351023();
	virtual void bfmeVK361023();
	virtual void bfmeVK371023();
	virtual void bfmeVK381023();
	virtual void bfmeVK391023();
	virtual void bfmeVK401023();
	virtual void bfmeVK411023();
	virtual void bfmeVK421023();
	virtual void bfmeVK431023();
	virtual void bfmeVK441023();
	virtual void bfmeVK451023();
	virtual void bfmeVK461023();
	virtual void bfmeVK471023();
	virtual void *bfmeName1023();
};

extern BfmeK1023 *g_bfmeK1023;
extern void *g_bfmeA1023;
extern char g_bfmeBuf1023[];
void bfmeEmit1023(void *a, char *b, void *c, int d);

void bfmeGo1023F(void)
{
	if (g_bfmeA1023 != 0)
		bfmeEmit1023(g_bfmeK1023->bfmeName1023(), g_bfmeBuf1023, g_bfmeA1023, 0);
}

class BfmeH1023;

class BfmeJ1023
{
public:
	void bfmeNote1023(BfmeH1023 *o);
};

extern BfmeJ1023 *g_bfmeJ1023;

class BfmeH1023
{
public:
	void bfmeAdd1023(int a, int b);

	char m_bfmePad[8];
	int m_bfmeVal;
	char m_bfmePad2[0x59];
	char m_bfmeFlag;
};

class BfmeS1023
{
public:
	void bfmeGo1023H(void);

	char m_bfmePad[0x45];
	char m_bfmeFlag;
};

void BfmeS1023::bfmeGo1023H(void)
{
	BfmeH1023 *o = (BfmeH1023 *)((char *)this - 0x20);

	if (m_bfmeFlag != 0) {
		g_bfmeJ1023->bfmeNote1023(o);
		o->bfmeAdd1023(o->m_bfmeVal, 0x3fffffff);
		o->m_bfmeFlag = 0;
	}
}

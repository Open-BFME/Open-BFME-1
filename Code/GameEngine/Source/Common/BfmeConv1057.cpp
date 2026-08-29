// Open-BFME5 conversions.

class BfmeT1057
{
public:
	virtual void bfmeVT01057();
	virtual void bfmeVT11057();
	virtual void bfmeVT21057();
	virtual void bfmeVT31057();
	virtual void bfmeVT41057();
	virtual void bfmeVT51057();
	virtual void bfmeVT61057();
	virtual void bfmeVT71057();
	virtual void bfmeVT81057();
	virtual void bfmeVT91057();
	virtual void bfmeVT101057();
	virtual void bfmeVT111057();
	virtual void bfmeVT121057();
	virtual void bfmeVT131057();
	virtual void bfmeVT141057();
	virtual void bfmeVT151057();
	virtual void bfmeVT161057();
	virtual void bfmeVT171057();
	virtual void bfmeVT181057();
	virtual void bfmeVT191057();
	virtual void bfmeVT201057();
	virtual void bfmeVT211057();
	virtual void bfmeVT221057();
	virtual void bfmeVT231057();
	virtual void bfmeVT241057();
	virtual void bfmeVT251057();
	virtual int bfmeNow1057();
};

extern BfmeT1057 *g_bfmeT1057;

class BfmeA1057
{
public:
	void bfmeGo1057A(int a);

	char m_bfmePad[0xb0];
	volatile int m_bfmeb0;
	char m_bfmePad2[0x70];
	volatile int m_bfme124;
	volatile int m_bfme128;
	volatile int m_bfme12c;
	char m_bfmePad3[0x1d8];
	volatile int m_bfme308;
};

void BfmeA1057::bfmeGo1057A(int a)
{
	int z = 0;

	m_bfmeb0 = z;
	m_bfme124 = 1;
	m_bfme12c = a;
	m_bfme128 = z;
	m_bfme308 = g_bfmeT1057->bfmeNow1057();
}

class BfmeLog1057
{
public:
	void bfmeLog1057(int a, char *f, int n, char *t, int p, int q, int r, int s);
};

extern BfmeLog1057 *g_bfmeLog1057;
extern char g_bfmeFmt1057[];
extern char g_bfmeArg1057[];

struct BfmeP1057
{
	char m_bfmePad[0x250];
	int m_bfmeId;
};

class BfmeB1057
{
public:
	void bfmeGo1057B(int unused);

	char m_bfmePad[0x34];
	BfmeP1057 *m_bfmeP;
	char m_bfmePad2[0x150];
	int m_bfmeState;
	char m_bfmePad3[0x28];
	char m_bfmeFlag;
};

void BfmeB1057::bfmeGo1057B(int unused)
{
	g_bfmeLog1057->bfmeLog1057(m_bfmeP->m_bfmeId, g_bfmeFmt1057, 1, g_bfmeArg1057, 0, 0, 0, 0);
	m_bfmeState = 1;
	m_bfmeFlag = 0;
}

struct BfmeVt1057
{
	char m_bfmePad[0x114];
	void (__stdcall *m_bfmeFn)(void *o, int a, int b, int c);
};

struct BfmeE1057
{
	BfmeVt1057 *m_bfmeVt;
};

extern BfmeE1057 *g_bfmeE1057;
extern int g_bfmeA1057;
extern int g_bfmeB1057;

void bfmeGo1057C(int a, int b, int c)
{
	BfmeE1057 *p = g_bfmeE1057;

	p->m_bfmeVt->m_bfmeFn(p, a, b, c);
	g_bfmeA1057++;
	g_bfmeB1057++;
}


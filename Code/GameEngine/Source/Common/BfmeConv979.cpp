// Open-BFME5 conversions.

struct BfmeStateA979
{
	char m_bfmePad[0x10c];
	int m_bfmeMode;
};

class BfmeActA979
{
public:
	void bfmeDo979A(int a);
};

extern BfmeStateA979 *g_bfmeStateA979;
extern int *g_bfmeGateA979;
extern BfmeActA979 *g_bfmeActA979;

char __stdcall bfmeAsk979A(int a);

char bfmeGo979A(void)
{
	if (!g_bfmeStateA979 || !g_bfmeGateA979 || g_bfmeStateA979->m_bfmeMode == 4
			|| !bfmeAsk979A(1))
		return 1;

	g_bfmeActA979->bfmeDo979A(1);
	return 0;
}

class BfmeKey979;

class BfmeSink979
{
public:
	void bfmeSend979B(BfmeKey979 *k);
};

struct BfmeX979
{
	char m_bfmePad[0x22c];
	BfmeSink979 *m_bfmeSink;
};

class BfmeKey979
{
public:
	BfmeX979 *bfmeGet979B();
};

class BfmeB979
{
public:
	virtual void bfmeV0979B();
	virtual void bfmeV1979B();
	virtual char bfmeReady979B();

	void bfmeGo979B();

	char m_bfmePad[0x9c];
	char m_bfmeFlagA;
	char m_bfmeFlagB;
};

void BfmeB979::bfmeGo979B()
{
	if (!bfmeReady979B())
		return;

	BfmeKey979 *k = *(BfmeKey979 **)((char *)this - 0x2c);
	m_bfmeFlagA = 0;

	BfmeX979 *x = k->bfmeGet979B();
	if (!x)
		return;

	BfmeSink979 *s = x->m_bfmeSink;
	if (!s)
		return;

	s->bfmeSend979B(*(BfmeKey979 **)((char *)this - 0x2c));
	m_bfmeFlagB = 1;
}

class BfmeThing979;

class BfmeLook979
{
public:
	void *bfmeFind979C(BfmeThing979 *t);
};

extern BfmeLook979 *g_bfmeLook979;

class BfmeC979
{
public:
	void bfmeGo979C();

	char m_bfmePad[0x338];
	char m_bfmeFlag;
	char m_bfmePad2[0xb];
	BfmeThing979 *m_bfmeA;
	BfmeThing979 *m_bfmeB;
	BfmeThing979 *m_bfmeC;
};

void BfmeC979::bfmeGo979C()
{
	BfmeLook979 *g = g_bfmeLook979;

	if (!g->bfmeFind979C(m_bfmeA) && !g->bfmeFind979C(m_bfmeB)
			&& !g->bfmeFind979C(m_bfmeC))
		m_bfmeFlag = 0;
}

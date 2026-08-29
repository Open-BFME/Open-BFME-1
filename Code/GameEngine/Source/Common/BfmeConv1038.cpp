// Open-BFME5 conversions.

class BfmeB1038
{
public:
	void bfmeDone1038(void);
};

class BfmeA1038
{
public:
	virtual void bfmeVA01038();
	virtual void bfmeVA11038();
	virtual void bfmeVA21038();
	virtual void bfmeVA31038();
	virtual void bfmeVA41038();
	virtual void bfmeVA51038();
	virtual void bfmeVA61038();
	virtual void bfmeVA71038();
	virtual void bfmeVA81038();
	virtual void bfmeVA91038();
	virtual void bfmeVA101038();
	virtual void bfmeVA111038();
	virtual void bfmeVA121038();
	virtual void bfmeVA131038();
	virtual void bfmeVA141038();
	virtual void bfmeVA151038();
	virtual void bfmeVA161038();
	virtual void bfmeVA171038();
	virtual void bfmeVA181038();
	virtual void bfmeVA191038();
	virtual void bfmeVA201038();
	virtual void bfmeVA211038();
	virtual void bfmeVA221038();
	virtual void bfmeVA231038();
	virtual void bfmeVA241038();
	virtual void bfmeVA251038();
	virtual void bfmeVA261038();
	virtual void bfmeVA271038();
	virtual void bfmeVA281038();
	virtual void bfmeVA291038();
	virtual void bfmeVA301038();
	virtual void bfmeVA311038();
	virtual void bfmeVA321038();
	virtual void bfmeVA331038();
	virtual void bfmeVA341038();
	virtual void bfmeVA351038();
	virtual void bfmeVA361038();
	virtual void bfmeVA371038();
	virtual void bfmeVA381038();
	virtual void bfmeVA391038();
	virtual void bfmeVA401038();
	virtual void bfmeVA411038();
	virtual void bfmeVA421038();
	virtual void bfmeVA431038();
	virtual void bfmeVA441038();
	virtual void bfmeVA451038();
	virtual void bfmeVA461038();
	virtual void bfmeVA471038();
	virtual void bfmeVA481038();
	virtual char bfmeAsk1038();
	void bfmeGo1038A(void);
	void bfmeStep1038(void);
};

void BfmeA1038::bfmeGo1038A(void)
{
	bfmeStep1038();

	if (bfmeAsk1038() != 0)
		((BfmeB1038 *)((char *)this - 0x20))->bfmeDone1038();
}

class BfmeLog1038
{
public:
	virtual void bfmeV01038();
	virtual void bfmeSay1038(char *m);
};

__declspec(dllimport) int __stdcall bfmeClose1038(void *h);
BfmeLog1038 *bfmeGetLog1038(void);
extern char g_bfmeMsg1038[];

class BfmeD1038
{
public:
	void bfmeGo1038D(void);

	char m_bfmePad[4];
	void *m_bfmeHandle;
};

void BfmeD1038::bfmeGo1038D(void)
{
	if (bfmeClose1038(m_bfmeHandle) == 0)
		bfmeGetLog1038()->bfmeSay1038(g_bfmeMsg1038);
}

class BfmeY1038
{
public:
	int bfmeVal1038(void);
};

BfmeY1038 * __stdcall bfmeFind1038(int a);

int __stdcall bfmeGo1038E(int a)
{
	BfmeY1038 *y = bfmeFind1038(a);

	if (y == 0)
		return -1;

	return y->bfmeVal1038();
}

class BfmeSubF1038
{
public:
	void bfmeAdd1038(int a, int b);
};

class BfmeAObj1038
{
public:
	void bfmeStop1038F(void);

	char m_bfmePad[0x122c];
	BfmeSubF1038 m_bfmeSub;
};

extern BfmeAObj1038 *g_bfmeA1038;
extern int g_bfmeB1038;
extern int g_bfmeC1038;
void bfmeFlush1038(void);

void bfmeGo1038F(void)
{
	if (g_bfmeA1038 == 0)
		return;

	g_bfmeA1038->bfmeStop1038F();
	bfmeFlush1038();
	g_bfmeA1038->m_bfmeSub.bfmeAdd1038(g_bfmeB1038, 0);
	g_bfmeC1038 -= 0x60;
}

class BfmeI1038
{
public:
	void bfmeGo1038I(void);

	char m_bfmePad[0x508];
	void (__cdecl *m_bfmeFn)(int);
	char m_bfmeFlag;
};

void BfmeI1038::bfmeGo1038I(void)
{
	void (__cdecl *fn)(int) = m_bfmeFn;

	if (fn != 0) {
		fn(m_bfmeFlag != 0);
		m_bfmeFn = 0;
	}
}


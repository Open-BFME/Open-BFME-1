// Open-BFME5 conversions.

__declspec(dllimport) void __stdcall bfmeSet995A(int h, float a, float b);

struct BfmeSub995
{
	char m_bfmePad[0x7c];
	float m_bfmeA;
	float m_bfmeB;
};

struct BfmeMid995
{
	char m_bfmePad[8];
	BfmeSub995 *m_bfmeSub;
};

struct BfmeX995
{
	char m_bfmePad[8];
	int m_bfmeHandle;
	char m_bfmePad2[8];
	BfmeMid995 *m_bfmeMid;
};

struct BfmeArg995
{
	BfmeX995 *m_bfmeX;
};

class BfmeA995
{
public:
	void bfmeGo995A(BfmeArg995 *a);

	char m_bfmePad[0x633];
	char m_bfmeOn;
};

void BfmeA995::bfmeGo995A(BfmeArg995 *a)
{
	if (m_bfmeOn) {
		BfmeX995 *x = a->m_bfmeX;
		BfmeSub995 *s = x->m_bfmeMid->m_bfmeSub;

		bfmeSet995A(x->m_bfmeHandle, s->m_bfmeB, s->m_bfmeA);
		return;
	}

	bfmeSet995A(a->m_bfmeX->m_bfmeHandle, 1.0f, 0.0f);
}

class BfmeLog995
{
public:
	void bfmeLog995(int a, char *fmt, int n, char *s, int p, int q, int r, int t);
};

class BfmeDrop995
{
public:
	virtual void bfmeVD0995();
	virtual void bfmeVD1995();
	virtual void bfmeVD2995();
	virtual void bfmeVD3995();
	virtual void bfmeVD4995();
	virtual void bfmeVD5995();
	virtual void bfmeVD6995();
	virtual void bfmeVD7995();
	virtual void bfmeVD8995();
	virtual void bfmeVD9995();
	virtual void bfmeRelease995(void *p);
};

extern BfmeLog995 *g_bfmeLog995;
extern BfmeDrop995 *g_bfmeDrop995;
extern int g_bfmeVal995B;
extern void *g_bfmeHeld995B;
extern char g_bfmeFmt995B[];

void bfmeGo995B(void)
{
	g_bfmeLog995->bfmeLog995(g_bfmeVal995B, g_bfmeFmt995B, 0, 0, 0, 0, 0, 0);

	if (g_bfmeHeld995B) {
		g_bfmeDrop995->bfmeRelease995(g_bfmeHeld995B);
		g_bfmeHeld995B = 0;
	}
}

extern char g_bfmeFmtA995C[];
extern char g_bfmeFmtB995C[];

struct BfmeOwner995C
{
	char m_bfmePad[0x250];
	int m_bfmeId;
};

class BfmeC995
{
public:
	void bfmeGo995C(int unused);

	char m_bfmePad[0x34];
	BfmeOwner995C *m_bfmeOwner;
	char m_bfmePad2[0x150];
	int m_bfmeState;
	char m_bfmePad3[0x28];
	char m_bfmeFlag;
};

void BfmeC995::bfmeGo995C(int unused)
{
	if (m_bfmeState != 0xa)
		return;

	g_bfmeLog995->bfmeLog995(m_bfmeOwner->m_bfmeId, g_bfmeFmtA995C, 1,
			g_bfmeFmtB995C, 0, 0, 0, 0);

	m_bfmeState = 1;
	m_bfmeFlag = 0;
}

// Open-BFME5 conversions.

class BfmeP1040
{
public:
	virtual void bfmeVP01040();
	virtual void bfmeVP11040();
	virtual void bfmeStop1040();

	char m_bfmePad[0x4c];
	int m_bfme50;
};

extern void (__cdecl *g_bfmeFree1040)(void *p, int n);

class BfmeA1040
{
public:
	void *bfmeGo1040A(unsigned int f);

	BfmeP1040 *m_bfmeP;
};

void *BfmeA1040::bfmeGo1040A(unsigned int f)
{
	m_bfmeP->m_bfme50 = 0;
	m_bfmeP->bfmeStop1040();

	if ((f & 1) != 0)
		g_bfmeFree1040(this, 4);

	return this;
}

struct BfmeS1040
{
	int m_bfmeIdx;
	void *m_bfmeNext;
	char m_bfmePad[0x30];
	void *m_bfmeCur;
	void *m_bfmeTab[1];
};

extern void (__cdecl *g_bfmeHook1040)(BfmeS1040 *s);
void bfmeApply1040(BfmeS1040 *s, int a);

void bfmeGo1040B(BfmeS1040 *s, int a)
{
	if (s->m_bfmeTab[s->m_bfmeIdx] == s->m_bfmeCur)
		return;

	s->m_bfmeCur = s->m_bfmeNext;
	g_bfmeHook1040(s);
	bfmeApply1040(s, a);
}

struct BfmeE1040
{
	char m_bfmePad[8];
	int m_bfmeH;
};

class BfmeD1040
{
public:
	BfmeE1040 *bfmeGet1040(void);
};

void bfmeQuery1040(int h, int *out);

class BfmeC1040
{
public:
	int bfmeGo1040C(void);

	BfmeD1040 *m_bfmeD;
};

int BfmeC1040::bfmeGo1040C(void)
{
	BfmeD1040 *d = m_bfmeD;

	if (d == 0)
		return -1;

	int r = -1;
	int h = d->bfmeGet1040()->m_bfmeH;

	bfmeQuery1040(h, &r);
	return r;
}

struct BfmeCs1040
{
	char m_bfmePad[0x18];
};

__declspec(dllimport) void __stdcall bfmeLock1040(BfmeCs1040 *c);
__declspec(dllimport) void __stdcall bfmeUnlock1040(BfmeCs1040 *c);
void __stdcall bfmeFree1040E(void *p);

class BfmeK1040
{
public:
	void bfmeGo1040K(void);

	void *m_bfmeP;
	BfmeCs1040 m_bfmeCs;
};

void BfmeK1040::bfmeGo1040K(void)
{
	bfmeLock1040(&m_bfmeCs);

	if (m_bfmeP != 0)
		bfmeFree1040E(m_bfmeP);

	m_bfmeP = 0;
	bfmeUnlock1040(&m_bfmeCs);
}

class BfmeG1040
{
public:
	void bfmeStep1040(void);
};

class BfmeH1040
{
public:
	void bfmeAdd1040(void *p);
};

class BfmeF1040
{
public:
	virtual char bfmeAsk1040();
	virtual void bfmeVF11040();
	virtual void bfmeVF21040();
	virtual void bfmeVF31040();
	virtual void bfmeVF41040();
	virtual void bfmeVF51040();
	virtual void bfmeVF61040();
	virtual void bfmeVF71040();
	virtual void bfmeFin1040(int n);
	void bfmeGo1040F(void);
};

void BfmeF1040::bfmeGo1040F(void)
{
	if (bfmeAsk1040() == 0)
		return;

	((BfmeG1040 *)((char *)this - 0x10))->bfmeStep1040();
	(*(BfmeH1040 **)((char *)this - 8))->bfmeAdd1040(*(char **)((char *)this - 0xc) + 0x70);
	bfmeFin1040(0);
}

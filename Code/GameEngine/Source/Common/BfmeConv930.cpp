// Open-BFME5 conversions.

class BfmeSub911E
{
public:
	void bfmePrep911E();
};

struct BfmeB930A
{
	char m_bfmePad[8];
	void *m_bfmeP;
};

struct BfmeA930A
{
	char m_bfmePad[0x14];
	BfmeB930A *m_bfmeB;
};

class BfmeThing930A
{
public:
	void bfmeGo930A();
	BfmeA930A *m_bfmeA;
};

void BfmeThing930A::bfmeGo930A()
{
	BfmeA930A *a = m_bfmeA;
	if (!a)
		return;
	BfmeB930A *b = a->m_bfmeB;
	if (!b)
		return;
	if (!b->m_bfmeP)
		return;
	((BfmeSub911E *)b)->bfmePrep911E();
}

class BfmeGlob930C
{
public:
	virtual void bfmeSlot930C0();
	virtual void bfmeVirt930C(void *a, int f);
};

extern BfmeGlob930C *g_bfme930Glob;
__declspec(dllimport) void __cdecl bfmeImport930C(void *a);

void bfmeGo930C(void *a)
{
	BfmeGlob930C *g = g_bfme930Glob;
	if (g) {
		g->bfmeVirt930C(a, 0);
		return;
	}
	bfmeImport930C(a);
}

void bfmeFreeRC(void *p);

class BfmeOldKB
{
public:
	void bfmeRelKB();
};

class BfmeThing930D
{
public:
	void bfmeGo930D();
	BfmeOldKB *m_bfmeP;
	char m_bfmePad[0x44];
	void *m_bfmeQ;
};

void BfmeThing930D::bfmeGo930D()
{
	bfmeFreeRC(m_bfmeQ);
	BfmeOldKB *s = m_bfmeP;
	if (s)
		s->bfmeRelKB();
}

extern char g_bfme930Vft[];

class BfmeThing930F
{
public:
	void bfmeGo930F();
	void bfmeTail930F();
	char *m_bfmeVft;
	char m_bfmePad[0x18];
	void *m_bfmeP;
};

void BfmeThing930F::bfmeGo930F()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme930Vft;
	bfmeFreeRC(p);
	bfmeTail930F();
}

void bfmeCall930G(int a, int b, int n, void *p, int m, int f);

void bfmeGo930G(void *a, int n)
{
	bfmeCall930G(4, 0, n, a, n * 3, 0);
}

extern "C" unsigned char bfmeVftDXG[];
extern void (__cdecl *g_bfmeFreeDXG)(void *what);

struct BfmeThingDXG
{
	void *bfmeGoDXG(unsigned char flags);
	void bfmeDtorDXG();
};

void *BfmeThingDXG::bfmeGoDXG(unsigned char flags)
{
	bfmeDtorDXG();
	if (flags & 1)
		g_bfmeFreeDXG(this);
	return this;
}

class BfmeSubDXH
{
	unsigned char m_bfmeHead[4];
};

extern void (__cdecl *g_bfmeDropDXH)(BfmeSubDXH *what);
void __cdecl bfmeCallDXH(BfmeSubDXH *a, void *b, BfmeSubDXH *c);

struct BfmeThingDXH
{
	void bfmeGoDXH(void *a);
	unsigned char m_bfmeHead[0x20];
	BfmeSubDXH m_bfmeSub;
};

void BfmeThingDXH::bfmeGoDXH(void *a)
{
	BfmeSubDXH *s = &m_bfmeSub;
	bfmeCallDXH(s, a, s);
	g_bfmeDropDXH(s);
}

extern "C" __declspec(dllimport) int __cdecl bfmeCvtDXI(void *a);

class BfmeGlobDXI
{
public:
	void bfmeUseDXI(int r);
};

class BfmeSubDXJ
{
public:
	void bfmeUseDXJ(int r);
};

extern BfmeGlobDXI *g_bfmeObjDXI;

struct BfmeHeldDXJ
{
	unsigned char m_bfmeHead[0x154];
	BfmeSubDXJ m_bfmeSub;
};

extern BfmeHeldDXJ *g_bfmeObjDXJ;

void bfmeGoDXI(void *a)
{
	g_bfmeObjDXI->bfmeUseDXI(bfmeCvtDXI(a));
}

void bfmeGoDXJ(void *a)
{
	g_bfmeObjDXJ->m_bfmeSub.bfmeUseDXJ(bfmeCvtDXI(a));
}

extern "C" __declspec(dllimport) void __stdcall bfmeCloseDXK(void *h);
void __cdecl bfmeFreeDXK(void *what);

struct BfmeThingDXK
{
	void bfmeGoDXKa();
	void bfmeGoDXKb();
	void *m_bfmeH;
	void *m_bfmeP;
};

void BfmeThingDXK::bfmeGoDXKa()
{
	if (m_bfmeH)
		bfmeCloseDXK(m_bfmeH);
	void *p = m_bfmeP;
	if (p)
		bfmeFreeDXK(p);
}

void BfmeThingDXK::bfmeGoDXKb()
{
	if (m_bfmeH)
		bfmeCloseDXK(m_bfmeH);
	void *p = m_bfmeP;
	if (p)
		bfmeFreeDXK(p);
}

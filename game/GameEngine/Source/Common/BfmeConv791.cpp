extern "C" __declspec(dllimport) void __stdcall bfmeCloseDWE(void *h);

struct BfmeThingDWE
{
	void bfmeGoDWE();
	unsigned char m_bfmeHead[0x48];
	void *m_bfmeH;
};

void BfmeThingDWE::bfmeGoDWE()
{
	if (m_bfmeH)
	{
		bfmeCloseDWE(m_bfmeH);
		m_bfmeH = 0;
	}
}

struct BfmeNodeDWF
{
	unsigned char m_bfmeHead[4];
	BfmeNodeDWF *m_bfmeNext;
};

extern void (__cdecl *g_bfmeFreeDWF)(void *what);

struct BfmeThingDWF
{
	void bfmeGoDWF();
	BfmeNodeDWF *m_bfmeHead;
};

void BfmeThingDWF::bfmeGoDWF()
{
	BfmeNodeDWF *p = m_bfmeHead;
	if (p)
	{
		BfmeNodeDWF *next = p->m_bfmeNext;
		g_bfmeFreeDWF(p);
		m_bfmeHead = next;
	}
}

extern void *g_bfmeBufDWG;

void bfmeGoDWG()
{
	if (g_bfmeBufDWG)
		g_bfmeFreeDWF(g_bfmeBufDWG);
	g_bfmeBufDWG = 0;
}

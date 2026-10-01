extern "C" __declspec(dllimport) void __stdcall DeleteObject(void *h);

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
		DeleteObject(m_bfmeH);
		m_bfmeH = 0;
	}
}

struct BfmeNodeDWF
{
	unsigned char m_bfmeHead[4];
	BfmeNodeDWF *m_bfmeNext;
};

// Native VA 0x0133782C is one zero-filled callback cell. The installer at
// RVA 0x00789440 writes ILT 0x007831F0, which routes to operator delete[].
// Other names pinned to that address are reference views of the same cell.
void (__cdecl *g_bfmeFreeDWF)(void *what) = 0;

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

// Native VA 0x013378D0 is a distinct zero-filled pointer cell. The 30-byte
// body at RVA 0x00897150 frees its value, then clears this same cell.
// The existing g_bfmeArenaStart extern is another view, not another datum.
void *g_bfmeBufDWG = 0;

void bfmeGoDWG()
{
	if (g_bfmeBufDWG)
		g_bfmeFreeDWF(g_bfmeBufDWG);
	g_bfmeBufDWG = 0;
}

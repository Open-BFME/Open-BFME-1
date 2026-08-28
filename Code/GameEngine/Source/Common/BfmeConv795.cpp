extern "C" __declspec(dllimport) int __stdcall bfmeTickDYA();

struct BfmeThingDYA
{
	void bfmeGoDYA(void *a);
	unsigned char m_bfmeHead[0x20];
	unsigned char m_bfmeFlags;
	unsigned char m_bfmePadA[3];
	int m_bfmeX;
	void *m_bfmeA;
	int m_bfmeT;
};

void BfmeThingDYA::bfmeGoDYA(void *a)
{
	m_bfmeFlags |= 4;
	m_bfmeA = a;
	m_bfmeT = bfmeTickDYA();
	m_bfmeX = -1;
}

extern char g_bfmeInitDYB;
extern int g_bfmeT0DYB;
extern int g_bfmeAccDYB;

void bfmeGoDYB()
{
	if (!g_bfmeInitDYB)
	{
		g_bfmeInitDYB = 1;
		g_bfmeT0DYB = bfmeTickDYA();
		g_bfmeAccDYB = 0;
	}
}

extern "C" __declspec(dllimport) void __cdecl bfmeCpyDYC(void *a, void *b);
extern "C" __declspec(dllimport) void __cdecl bfmeFreeDYC(void *a);

struct BfmeThingDYC
{
	void bfmeGoDYC(void *a);
	unsigned char m_bfmeHead[0x18];
	void *m_bfmeP;
};

void BfmeThingDYC::bfmeGoDYC(void *a)
{
	if (m_bfmeP)
	{
		bfmeCpyDYC(a, m_bfmeP);
		bfmeFreeDYC(m_bfmeP);
	}
}

extern "C" __declspec(dllimport) void __stdcall bfmeDoDWH();
extern "C" __declspec(dllimport) void __stdcall bfmeSetDWI(void *h, int flag);
extern "C" __declspec(dllimport) void __stdcall bfmeOnDWJ(int flag);
extern "C" __declspec(dllimport) int __cdecl bfmeCmpDWK(const char *a, const char *b);
extern "C" __declspec(dllimport) void __stdcall bfmeUseDWL(void *a);
extern "C" unsigned char bfmeStrDWK[];
extern "C" unsigned char bfmeVftDWL[];

struct BfmeThingDWH
{
	void bfmeGoDWH();
	char m_bfmeFlag;
};

void BfmeThingDWH::bfmeGoDWH()
{
	if (m_bfmeFlag)
	{
		bfmeDoDWH();
		m_bfmeFlag = 0;
	}
}

extern void *g_bfmeHDWI;

void bfmeGoDWI()
{
	bfmeSetDWI(g_bfmeHDWI, 1);
}

struct BfmeThingDWJ
{
	void bfmeGoDWJ();
	unsigned char m_bfmeHead[0x4e0c];
	char m_bfmeFlag;
};

void BfmeThingDWJ::bfmeGoDWJ()
{
	if (!m_bfmeFlag)
		bfmeOnDWJ(1);
	m_bfmeFlag = 1;
}

char bfmeGoDWK(const char *s)
{
	return bfmeCmpDWK(s, (const char *)bfmeStrDWK) == 0;
}

struct BfmeThingDWL
{
	void *bfmeGoDWL(void *a);
	void *m_bfmeVft;
};

void *BfmeThingDWL::bfmeGoDWL(void *a)
{
	bfmeUseDWL(a);
	m_bfmeVft = bfmeVftDWL;
	return this;
}

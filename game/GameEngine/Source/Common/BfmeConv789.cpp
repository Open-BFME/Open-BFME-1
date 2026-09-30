struct BfmeCsDWA
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall InterlockedIncrement(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(BfmeCsDWA *cs);

struct BfmeThingDWB
{
	void bfmeGoDWB();
	void bfmeOneDWB();
	unsigned char m_bfmeHead[4];
	BfmeCsDWA m_bfmeCs;
};

void BfmeThingDWB::bfmeGoDWB()
{
	bfmeOneDWB();
	DeleteCriticalSection(&m_bfmeCs);
}

extern BfmeCsDWA g_bfmeCsDWC;

struct BfmeThingDWC
{
	bool bfmeGoDWC();
	unsigned char m_bfmeHead[0x9df8];
	BfmeCsDWA m_bfmeCs;
};

bool BfmeThingDWC::bfmeGoDWC()
{
	InterlockedIncrement(&m_bfmeCs);
	EnterCriticalSection(&g_bfmeCsDWC);
	return false;
}

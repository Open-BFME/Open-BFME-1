struct BfmeCsDWA
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall InterlockedIncrement(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(BfmeCsDWA *cs);

// callees.py 0x009F6834 20: the call goes through ILT 0x00017EEF to
// 0x0005BFB0, matched as BfmeK1040::bfmeGo1040K (BfmeConv1040.cpp).
struct BfmeK1040
{
	void bfmeGo1040K();
};

struct BfmeThingDWB
{
	void bfmeGoDWB();
	unsigned char m_bfmeHead[4];
	BfmeCsDWA m_bfmeCs;
};

void BfmeThingDWB::bfmeGoDWB()
{
	((BfmeK1040 *)this)->bfmeGo1040K();
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

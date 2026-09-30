struct BfmeCsDVC
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCsDVC *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(BfmeCsDVC *cs);

struct BfmeThingDVC
{
	void bfmeGoDVC();
	unsigned char m_bfmeHeadA[4];
	BfmeCsDVC m_bfmeCs;
	int m_bfmeCount;
};

void BfmeThingDVC::bfmeGoDVC()
{
	EnterCriticalSection(&m_bfmeCs);
	m_bfmeCount = m_bfmeCount + 1;
	LeaveCriticalSection(&m_bfmeCs);
}

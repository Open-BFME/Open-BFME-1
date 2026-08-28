struct BfmeCsDVC
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall bfmeEnterDVC(BfmeCsDVC *cs);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveDVC(BfmeCsDVC *cs);

struct BfmeThingDVC
{
	void bfmeGoDVC();
	unsigned char m_bfmeHeadA[4];
	BfmeCsDVC m_bfmeCs;
	int m_bfmeCount;
};

void BfmeThingDVC::bfmeGoDVC()
{
	bfmeEnterDVC(&m_bfmeCs);
	m_bfmeCount = m_bfmeCount + 1;
	bfmeLeaveDVC(&m_bfmeCs);
}

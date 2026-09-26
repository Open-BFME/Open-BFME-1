struct BfmeCsDWA
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall bfmeEnterDWA(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall bfmeInitDWA(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall bfmeStartDWB(BfmeCsDWA *cs);

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
	bfmeStartDWB(&m_bfmeCs);
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
	bfmeInitDWA(&m_bfmeCs);
	bfmeEnterDWA(&g_bfmeCsDWC);
	return false;
}

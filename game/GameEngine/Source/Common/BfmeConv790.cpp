// cl: /O1
struct BfmeCsDWD
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall bfmeEnterDWD(BfmeCsDWD *cs);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveDWD(BfmeCsDWD *cs);

struct BfmeThingDWD
{
	int bfmeLockDWD();
	void bfmeUnlockDWD();
	void bfmeReleaseDWD();
	BfmeCsDWD *m_bfmeCs;
	char m_bfmeHeld;
};

int BfmeThingDWD::bfmeLockDWD()
{
	bfmeEnterDWD(m_bfmeCs);
	m_bfmeHeld = 1;
	return 0;
}

void BfmeThingDWD::bfmeUnlockDWD()
{
	bfmeLeaveDWD(m_bfmeCs);
	m_bfmeHeld = 0;
}

void BfmeThingDWD::bfmeReleaseDWD()
{
	if (m_bfmeHeld)
	{
		bfmeLeaveDWD(m_bfmeCs);
		m_bfmeHeld = 0;
	}
}

// Open-BFME5 conversions.

struct BfmeLockTEA
{
	char m_bfmePad[0x18];
};

__declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA *cs);
__declspec(dllimport) void __stdcall bfmeLeaveTEA(BfmeLockTEA *cs);

class BfmeThingTEA
{
public:
	void bfmeGoTEA();
	char m_bfmePad[0x6c];
	volatile int m_bfmeCount;
	BfmeLockTEA m_bfmeLock;
};

void BfmeThingTEA::bfmeGoTEA()
{
	bfmeEnterTEA(&m_bfmeLock);
	++m_bfmeCount;
	bfmeLeaveTEA(&m_bfmeLock);
}

class BfmeThingTED
{
public:
	void bfmeGoTED();
	void bfmeOneTED(int a);
	void bfmeTwoTED();
	void bfmeThreeTED();
	char m_bfmePad[0x618];
	int m_bfmeState;
};

void BfmeThingTED::bfmeGoTED()
{
	bfmeOneTED(7);
	bfmeTwoTED();
	bfmeThreeTED();
	m_bfmeState = 0;
}

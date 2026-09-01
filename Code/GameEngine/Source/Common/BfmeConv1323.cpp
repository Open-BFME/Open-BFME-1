// Open-BFME5 conversions.

__declspec(dllimport) long __stdcall bfmeInitTTD(void *a, int b);

class BfmeThingTTD
{
public:
	BfmeThingTTD();
	int m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfme09;
	char m_bfme0a;
	char m_bfmePad;
	long m_bfmeHr;
	int m_bfme10;
};

BfmeThingTTD::BfmeThingTTD()
{
	m_bfme00 = 0;
	m_bfme04 = 0;
	m_bfme08 = 0;
	m_bfme09 = 0;
	m_bfme0a = 0;
	m_bfmeHr = 0x80004005;
	m_bfme10 = 0;
	m_bfmeHr = bfmeInitTTD(0, 6);
}

__declspec(dllimport) int __cdecl bfmeOpenTTE(void *name);
__declspec(dllimport) void __cdecl bfmeBindTTE(int h, void *name);

class BfmeThingTTE
{
public:
	int bfmeGoTTE();
	char m_bfmePad[0x54];
	void *m_bfmeName;
};

int BfmeThingTTE::bfmeGoTTE()
{
	int h = bfmeOpenTTE(m_bfmeName);
	if (h != -1) {
		bfmeBindTTE(h, m_bfmeName);
		return h;
	}
	return -1;
}

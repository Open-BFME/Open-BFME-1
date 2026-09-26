// Open-BFME5 conversions.

__declspec(dllimport) void __stdcall bfmeClose1012(void *h);
__declspec(dllimport) int __stdcall bfmeWait1012(void *h, int t);

class BfmeA1012
{
public:
	void bfmeGo1012A(void *h, int t);

	void *m_bfmeHandle;
	char m_bfmeOn;
};

void BfmeA1012::bfmeGo1012A(void *h, int t)
{
	if (m_bfmeOn) {
		bfmeClose1012(m_bfmeHandle);
		m_bfmeOn = 0;
	}

	m_bfmeHandle = h;

	if (bfmeWait1012(h, t) != 0x102)
		m_bfmeOn = 1;
}

class BfmeB1012
{
public:
	void bfmeGo1012B(int v);

	char m_bfmePad[0x3c];
	int m_bfmeVal;
	char m_bfmePad2[8];
	void *m_bfmeHandle;
};

void BfmeB1012::bfmeGo1012B(int v)
{
	void *h = m_bfmeHandle;
	char ok = 0;

	if (bfmeWait1012(h, -1) != 0x102)
		ok = 1;

	m_bfmeVal = v;

	if (ok)
		bfmeClose1012(h);
}

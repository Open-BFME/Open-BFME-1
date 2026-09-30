// Open-BFME5 conversions.

extern "C" __declspec(dllimport) void __stdcall ReleaseMutex(void *h);
extern "C" __declspec(dllimport) int __stdcall WaitForSingleObject(void *h, int t);

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
		ReleaseMutex(m_bfmeHandle);
		m_bfmeOn = 0;
	}

	m_bfmeHandle = h;

	if (WaitForSingleObject(h, t) != 0x102)
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

	if (WaitForSingleObject(h, -1) != 0x102)
		ok = 1;

	m_bfmeVal = v;

	if (ok)
		ReleaseMutex(h);
}

// Open-BFME5 conversions.

extern "C" __declspec(dllimport) void __stdcall bfmeEnter1172(void *p);
extern "C" __declspec(dllimport) void __stdcall bfmeLeave1172(void *p);

class BfmeF1172
{
public:
	void bfmeFill1172(int *out);
};

class BfmeQ1172
{
public:
	void bfmeGo1172(int a);
	char m_bfmePad0[0x2c];
	char m_bfme2c;
	char m_bfmePad1[0x17];
	BfmeF1172 m_bfme44;
	char m_bfmePad2[0x13];
	int m_bfme58;
	int m_bfme5c;
	char m_bfmePad3[0x188];
	int m_bfme1e8;
};

void BfmeQ1172::bfmeGo1172(int a)
{
	int t[2];
	void *p = &m_bfme2c;

	bfmeEnter1172(p);
	m_bfme44.bfmeFill1172(t);
	m_bfme58 = t[0];
	m_bfme5c = t[1];
	m_bfme1e8 = a;
	bfmeLeave1172(p);
}

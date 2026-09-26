// ?bfmeSetupJG@BfmeThingJG@@QAEXHHHHH_N@Z
// partial score=0.97 date=2026-09-08
class BfmeSubJG
{
public:
	void bfmeStartJG(int a, int b, float c);

	unsigned char m_bfmeGapJG[8];
};

class BfmeThingJG
{
public:
	void bfmeSetupJG(int p1, int p2, int p3, int p4, int p5, bool p6);

	unsigned char m_bfmeHeadJG[4];
	int m_bfme04JG;
	int m_bfme08JG;
	int m_bfme0cJG;
	BfmeSubJG m_bfmeSubJG;
	int m_bfme18JG;
	int m_bfme1cJG;
	int m_bfme20JG;
	char m_bfme24JG;
	unsigned char m_bfmePad0JG[3];
	int m_bfme28JG;
	unsigned char m_bfmeGap1JG[0xc];
	int m_bfme38JG;
	volatile int m_bfme3cJG;
	volatile int m_bfme40JG;
	char m_bfme44JG;
	volatile char m_bfme45JG;
	char m_bfme46JG;
	unsigned char m_bfmePad1JG[1];
	int m_bfme48JG;
	int m_bfme4cJG;
	int m_bfme50JG;
};

void BfmeThingJG::bfmeSetupJG(int p1, int p2, int p3, int p4, int p5, bool p6)
{
	int n = p2;

	if (n <= 1)
		n = 1;

	m_bfme04JG = n;
	m_bfme08JG = 0;
	m_bfme18JG = 0;
	m_bfme1cJG = 0;
	m_bfme20JG = 0;
	m_bfme28JG = 1;

	m_bfmeSubJG.bfmeStartJG(p3, p4, (float)p2);

	m_bfme0cJG = p5;

	if (p6)
		m_bfme38JG = 0;

	m_bfme3cJG = 0;
	m_bfme40JG = 0;
	m_bfme45JG = 0;
	m_bfme46JG = (p5 != 0);
	m_bfme48JG = 0;
	m_bfme4cJG = 0;
	m_bfme50JG = 0;
	m_bfme24JG = 1;
}

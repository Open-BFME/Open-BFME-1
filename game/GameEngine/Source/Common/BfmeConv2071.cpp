extern int g_bfmeDivGT;

class BfmeSubGT
{
public:
	void bfmeStartGT(int a, int b, float c);

	unsigned char m_bfmeGapGT[8];
};

class BfmeSetupGT
{
public:
	void bfmeInitGT(int p1, int p2, int p3, int p4, int p5, int p6);

	unsigned char m_bfmeHeadGT[0x1ac];
	int m_bfme1acGT;
	int m_bfme1b0GT;
	int m_bfme1b4GT;
	int m_bfme1b8GT;
	int m_bfme1bcGT;
	BfmeSubGT m_bfmeSubGT;
	char m_bfme1c8GT;
	unsigned char m_bfmePad0GT[3];
	int m_bfme1ccGT;
	unsigned char m_bfmeGap1GT[8];
	int m_bfme1d8GT;
	char m_bfme1dcGT;
	unsigned char m_bfmeGap2GT[0x21e7];
	int m_bfme23c4GT;
};

void BfmeSetupGT::bfmeInitGT(int p1, int p2, int p3, int p4, int p5, int p6)
{
	m_bfme1c8GT = 1;

	int a = p3;

	if (a < 1)
		a = 0;

	m_bfme1bcGT = a / g_bfmeDivGT;

	if (m_bfme1bcGT < 1)
		m_bfme1bcGT = 0;

	if (p2 < 1)
		p2 = 1;

	m_bfme1acGT = p2 / g_bfmeDivGT;

	if (m_bfme1acGT < 1)
		m_bfme1acGT = 1;

	m_bfme1dcGT = 1;
	m_bfme1ccGT = p1;
	m_bfme1b0GT = 0;
	m_bfme1b4GT = m_bfme23c4GT;
	m_bfme1b8GT = m_bfme23c4GT;

	m_bfmeSubGT.bfmeStartGT(p4, p5, (float)p2);

	m_bfme1d8GT = p6;
}

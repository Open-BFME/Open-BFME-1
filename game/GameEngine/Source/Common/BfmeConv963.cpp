// cl: /G7

// Open-BFME5 conversions.

extern char g_bfmeVft963[];

class BfmeReg963
{
public:
	BfmeReg963();
	void bfmeBase963();

	char *volatile m_bfmeVft;
	char m_bfmePad[4];
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile float m_bfme1c;
	volatile float m_bfme20;
	volatile float m_bfme24;
};

extern BfmeReg963 *g_bfmeReg963;

BfmeReg963::BfmeReg963()
{
	bfmeBase963();
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfmeVft = g_bfmeVft963;
	m_bfme1c = 3.402823466e+38f;
	m_bfme20 = 3.402823466e+38f;
	m_bfme24 = 3.402823466e+38f;

	if (g_bfmeReg963 == 0)
		g_bfmeReg963 = this;
}

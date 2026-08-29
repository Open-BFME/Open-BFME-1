// Open-BFME5 conversions.

struct BfmeMain1203
{
	char m_bfmePad[0x5c];
	volatile int m_bfme5c;
};

extern "C" BfmeMain1203 *volatile g_bfmeMain1203;

struct BfmeTab1203
{
	volatile int m_bfme00;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	int m_bfme28[7];
	int m_bfme44[8];
	int m_bfme64[8];
	int m_bfme84[8];
	int m_bfmea4[8];
	int m_bfmec4[8];
};

extern "C" BfmeTab1203 g_bfmeTab1203;

void bfmeReset1203(void)
{
	BfmeMain1203 *p = g_bfmeMain1203;
	int i;

	g_bfmeTab1203.m_bfme00 = 0;
	g_bfmeTab1203.m_bfme10 = 0;
	g_bfmeTab1203.m_bfme0c = 0;
	g_bfmeTab1203.m_bfme08 = 0;
	g_bfmeTab1203.m_bfme04 = 0;
	g_bfmeTab1203.m_bfme20 = 0;

	if (p != 0)
		p->m_bfme5c = 0;

	g_bfmeTab1203.m_bfme14 = 0;
	g_bfmeTab1203.m_bfme18 = 0;
	g_bfmeTab1203.m_bfme1c = 0;
	g_bfmeTab1203.m_bfme24 = 0;

	for (i = 0; i < 7; i++) {
		g_bfmeTab1203.m_bfme64[i] = 0;
		g_bfmeTab1203.m_bfme84[i] = 0;
		g_bfmeTab1203.m_bfmea4[i] = 0;
		g_bfmeTab1203.m_bfme44[i] = 0;
		g_bfmeTab1203.m_bfmec4[i] = 0;
		g_bfmeTab1203.m_bfme28[i] = 0;
	}

	g_bfmeTab1203.m_bfme64[7] = 0;
	g_bfmeTab1203.m_bfme84[7] = 0;
	g_bfmeTab1203.m_bfmea4[7] = 0;
	g_bfmeTab1203.m_bfme44[7] = 0;
	g_bfmeTab1203.m_bfmec4[7] = 0;
}

// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1164
{
public:
	BfmeA1164(void);
	char m_bfmePad[0x14];
	int m_bfme14[6];
	int m_bfme2c[6];
};

BfmeA1164::BfmeA1164(void)
{
	memset(m_bfme14, 0, 0x18);
	memset(m_bfme2c, 0, 0x18);
}

class BfmeB1164
{
public:
	BfmeB1164(void);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08[3];
	int m_bfme14[3];
	float m_bfme20;
	float m_bfme24;
	float m_bfme28;
};

BfmeB1164::BfmeB1164(void)
{
	m_bfme00 = -1;
	m_bfme04 = -1;
	memset(m_bfme08, 0, 0xc);
	memset(m_bfme14, 0, 0xc);
	m_bfme20 = -1.0f;
	m_bfme24 = 1.0f;
	m_bfme28 = -1.0f;
}

// cl: /DNDEBUG /MD /EHsc

// Retail 0x00707090. Constructor: zero most fields, +0x14 = -1.

class Gen_00707090
{
public:
	Gen_00707090(void);

private:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	int m_14;
	unsigned char m_18;
	unsigned char m_pad1c[0x1C - 0x19];
	int m_1c;
	int m_20;
};

// ??0Gen_00707090@@QAE@XZ
Gen_00707090::Gen_00707090(void)
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
	m_c = 0;
	m_10 = 0;
	m_14 = -1;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
}

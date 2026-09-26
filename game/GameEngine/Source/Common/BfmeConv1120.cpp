// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1120
{
public:
	BfmeA1120(void);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
};

BfmeA1120::BfmeA1120(void)
{
	memset(this, 0, 0x18);
	m_bfme18 = 0;
}

class BfmeB1120
{
public:
	BfmeB1120(void);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfme18;
};

BfmeB1120::BfmeB1120(void)
{
	memset(this, 0, 0x18);
	m_bfme18 = 0;
}

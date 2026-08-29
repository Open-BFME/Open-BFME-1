// Open-BFME5 conversions.

extern "C" char g_bfmeV1140A[];

class BfmeBase1140A
{
public:
	BfmeBase1140A(void) throw();
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeA1140 : public BfmeBase1140A
{
public:
	BfmeA1140(void);
	char m_bfme08;
	volatile char m_bfme09;
	char m_bfmePad[2];
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
};

BfmeA1140::BfmeA1140(void)
{
	m_bfme00 = g_bfmeV1140A;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme1c = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme28 = 0;
	m_bfme2c = 0;
	m_bfme34 = 0;
	m_bfme0c = 0;
	m_bfme30 = -1;
	m_bfme09 = 1;
	m_bfme04 = 0x16;
}

extern "C" char g_bfmeV1140B[];

class BfmeBase1140B
{
public:
	BfmeBase1140B(void) throw();
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeB1140 : public BfmeBase1140B
{
public:
	BfmeB1140(void);
	char m_bfme08;
	volatile char m_bfme09;
	char m_bfmePad[2];
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
};

BfmeB1140::BfmeB1140(void)
{
	m_bfme10 = 0;
	m_bfme14 = 0x1e;
	m_bfme00 = g_bfmeV1140B;
	m_bfme18 = 0;
	m_bfme1c = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;

	int v = m_bfme14;

	m_bfme28 = 0;
	m_bfme0c = 0;
	m_bfme2c = -1;
	m_bfme04 = v;
	m_bfme09 = 1;
}

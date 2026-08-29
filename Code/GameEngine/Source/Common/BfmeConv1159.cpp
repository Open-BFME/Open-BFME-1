// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);
extern "C" char g_bfmeV1159[];

class BfmeA1159
{
public:
	BfmeA1159(void);
	char *volatile m_bfme00;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile char m_bfme14;
	volatile char m_bfme15;
	char m_bfmePad[2];
	volatile int m_bfme18;
	int m_bfme1c[6];
};

BfmeA1159::BfmeA1159(void)
{
	m_bfme04 = 0;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme00 = g_bfmeV1159;
	m_bfme14 = 0;
	m_bfme15 = 0;
	m_bfme18 = 0;
	memset(m_bfme1c, 0, 0x18);
}

struct BfmeSub1159
{
	char m_bfmePad0[8];
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	char m_bfmePad1[0xc];
	volatile int m_bfme20;
	char m_bfmePad2[4];
	volatile int m_bfme28;
	char m_bfmePad3[0x3c];
	volatile int m_bfme68;
};

class BfmeB1159
{
public:
	void bfmeGo1159(void);
	char m_bfmePad0[4];
	volatile char m_bfme04;
	volatile char m_bfme05;
	char m_bfmePad1[2];
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	char m_bfmePad2[0xc];
	volatile int m_bfme20;
	char m_bfmePad3[0x34];
	BfmeSub1159 *volatile m_bfme58;
	BfmeSub1159 *volatile m_bfme5c;
	volatile int m_bfme60;
};

void BfmeB1159::bfmeGo1159(void)
{
	BfmeSub1159 *p;
	BfmeSub1159 *q;

	m_bfme04 = 1;
	m_bfme05 = 0;
	m_bfme10 = 0;
	m_bfme0c = 0;
	m_bfme08 = 0;

	p = m_bfme58;

	m_bfme20 = 0;
	m_bfme60 = 0;

	p->m_bfme28 = -1;
	p->m_bfme68 = 0;
	p->m_bfme10 = 0;
	p->m_bfme0c = 0;
	p->m_bfme08 = 0;
	p->m_bfme20 = 0;

	q = m_bfme5c;

	q->m_bfme28 = -1;
	q->m_bfme68 = 0;
	q->m_bfme10 = 0;
	q->m_bfme0c = 0;
	q->m_bfme08 = 0;
	q->m_bfme20 = 0;
}

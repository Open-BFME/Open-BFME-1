// Open-BFME5 conversions.

struct BfmeSrc947
{
	char m_bfmePad[0xc];
	int m_bfmeVal;
};

extern char g_bfme947A1[];
extern char g_bfme947A2[];
extern char g_bfme947A3[];
extern char g_bfme947A4[];
extern char g_bfme947A5[];

class BfmeThing947A
{
public:
	BfmeThing947A(void *a, BfmeSrc947 *b);
	char *volatile m_bfme00;
	void *volatile m_bfme04;
	char *volatile m_bfme08;
	char *volatile m_bfme0c;
	volatile int m_bfme10;
};

BfmeThing947A::BfmeThing947A(void *a, BfmeSrc947 *b)
{
	m_bfme04 = a;
	m_bfme08 = g_bfme947A1;
	m_bfme0c = g_bfme947A2;
	m_bfme10 = 0;
	m_bfme00 = g_bfme947A3;
	m_bfme08 = g_bfme947A4;
	m_bfme0c = g_bfme947A5;
	m_bfme10 = b->m_bfmeVal;
}

extern char g_bfme947B1[];
extern char g_bfme947B2[];
extern char g_bfme947B3[];
extern char g_bfme947B4[];
extern char g_bfme947B5[];

class BfmeThing947B
{
public:
	BfmeThing947B(void *a, BfmeSrc947 *b);
	char *volatile m_bfme00;
	void *volatile m_bfme04;
	char *volatile m_bfme08;
	char *volatile m_bfme0c;
	volatile int m_bfme10;
};

BfmeThing947B::BfmeThing947B(void *a, BfmeSrc947 *b)
{
	m_bfme04 = a;
	m_bfme08 = g_bfme947B1;
	m_bfme0c = g_bfme947B2;
	m_bfme10 = 0;
	m_bfme00 = g_bfme947B3;
	m_bfme08 = g_bfme947B4;
	m_bfme0c = g_bfme947B5;
	m_bfme10 = b->m_bfmeVal;
}

struct BfmeObj947C
{
	char m_bfmePad[0x254];
	char m_bfmeFlag;
	char m_bfmePad2[7];
	int m_bfmeVal;
};

struct BfmeAux947C
{
	char m_bfmePad[0x50];
	char m_bfmeFlag;
};

class BfmeGlob947C
{
public:
	void bfmeTailB947C();
};

extern BfmeObj947C *g_bfme947ObjC;
extern BfmeAux947C *g_bfme947AuxC;
extern BfmeGlob947C *g_bfme947GlobC;
void bfmeTailA947C(void);

void bfmeGo947C(void)
{
	BfmeObj947C *p = g_bfme947ObjC;
	if (p) {
		if (p->m_bfmeFlag)
			return;
		p->m_bfmeFlag = 1;
		g_bfme947ObjC->m_bfmeVal = 0;
		g_bfme947AuxC->m_bfmeFlag = 1;
		g_bfme947GlobC->bfmeTailB947C();
	} else {
		bfmeTailA947C();
	}
}

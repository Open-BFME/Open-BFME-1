// Open-BFME5 conversions.

extern "C" void bfmeHookA1054(void);
extern "C" void bfmeHookB1054(void);

struct BfmeA1054
{
	char m_bfmePad[0x50];
	int m_bfmeH;
	void (*volatile m_bfmeFn)(void);
	volatile int m_bfme58;
	volatile int m_bfme5c;
};

struct BfmeB1054
{
	char m_bfmePad[0x20];
	int m_bfmeH;
	void (*volatile m_bfmeFn)(void);
	volatile int m_bfme28;
	volatile int m_bfme2c;
	int m_bfmeH3;
	void (*m_bfmeFn3)(void);
	int m_bfme38;
	int m_bfme3c;
	int m_bfmeH4;
	void (*m_bfmeFn4)(void);
	int m_bfme48;
	int m_bfme4c;
	int m_bfmeH5;
	void (*m_bfmeFn5)(void);
	int m_bfme58;
	int m_bfme5c;
};

int bfmeMake1054(int n);
void __stdcall bfmeTailA1054(BfmeA1054 *p);
void __stdcall bfmeTailB1054(BfmeB1054 *p);
void bfmeTailA1054Cdecl(BfmeA1054 *p);

void __stdcall bfmeGo1054A(BfmeA1054 *p)
{
	int h = bfmeMake1054(5);
	int z = 0;

	p->m_bfmeH = h;
	p->m_bfmeFn = bfmeHookA1054;
	p->m_bfme58 = z;
	p->m_bfme5c = z;
	bfmeTailA1054(p);
}

void __stdcall bfmeGo1054B(BfmeB1054 *p)
{
	int h = bfmeMake1054(2);
	int z = 0;

	p->m_bfmeH = h;
	p->m_bfmeFn = bfmeHookB1054;
	p->m_bfme28 = z;
	p->m_bfme2c = z;
	bfmeTailB1054(p);
}

void bfmeTailB1054Impl(BfmeB1054 *p)
{
	int z = 0;
	p->m_bfmeH3 = bfmeMake1054(3);
	p->m_bfmeFn3 = reinterpret_cast<void (*)(void)>(0x00441de9);
	p->m_bfme38 = z;
	p->m_bfme3c = z;
	p->m_bfmeH4 = bfmeMake1054(4);
	p->m_bfmeFn4 = reinterpret_cast<void (*)(void)>(0x004410dd);
	p->m_bfme48 = z;
	p->m_bfme4c = z;
	p->m_bfmeH5 = bfmeMake1054(5);
	p->m_bfmeFn5 = reinterpret_cast<void (*)(void)>(0x00408b39);
	p->m_bfme58 = z;
	p->m_bfme5c = z;
	bfmeTailA1054Cdecl(reinterpret_cast<BfmeA1054 *>(p));
}

class BfmeSubC1054
{
public:
	char m_bfmePad[4];
};

class BfmeD1054
{
public:
	void bfmeAdd1054(BfmeSubC1054 *s);
};

class BfmeC1054
{
public:
	void bfmeGo1054C(BfmeD1054 *p, int b, int c);
	void bfmeStep1054(BfmeD1054 *p, int b, int c);

	char m_bfmePad[0x64];
	BfmeSubC1054 m_bfmeSub;
};

void BfmeC1054::bfmeGo1054C(BfmeD1054 *p, int b, int c)
{
	bfmeStep1054(p, b, c);
	p->bfmeAdd1054(&m_bfmeSub);
}

struct BfmeVt1054
{
	char m_bfmePad[0xb0];
	void (__stdcall *m_bfmeFn)(void *o, int a, int b);
};

struct BfmeE1054
{
	BfmeVt1054 *m_bfmeVt;
};

extern BfmeE1054 *g_bfmeE1054;
extern int g_bfmeCount1054;
extern int g_bfmeHits1054;

void bfmeGo1054E(int a, int b)
{
	g_bfmeCount1054++;

	BfmeE1054 *p = g_bfmeE1054;

	p->m_bfmeVt->m_bfmeFn(p, a, b);
	g_bfmeHits1054++;
}

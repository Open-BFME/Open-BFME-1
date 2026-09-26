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
	int m_bfmeH6;
	void (*m_bfmeFn6)(void);
	int m_bfme68;
	int m_bfme6c;
	int m_bfmeH7;
	void (*m_bfmeFn7)(void);
	int m_bfme78;
	int m_bfme7c;
	int m_bfmeH8;
	void (*m_bfmeFn8)(void);
	int m_bfme88;
	int m_bfme8c;
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
void bfmeTailB1054Cdecl(BfmeB1054 *p);

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

void bfmeTailA1054Impl(BfmeA1054 *p)
{
	int z = 0;
	p->m_bfmeH6 = bfmeMake1054(6);
	p->m_bfmeFn6 = reinterpret_cast<void (*)(void)>(0x0042ed75);
	p->m_bfme68 = z;
	p->m_bfme6c = z;
	p->m_bfmeH7 = bfmeMake1054(7);
	p->m_bfmeFn7 = reinterpret_cast<void (*)(void)>(0x00441c09);
	p->m_bfme78 = z;
	p->m_bfme7c = z;
	p->m_bfmeH8 = bfmeMake1054(8);
	p->m_bfmeFn8 = reinterpret_cast<void (*)(void)>(0x0043c9cf);
	p->m_bfme88 = z;
	p->m_bfme8c = z;
}

struct BfmeCategoryHead1054
{
	int m_key0;
	void (*m_callback0)(void);
	int m_zero08;
	int m_zero0c;
	int m_key1;
	void (*m_callback1)(void);
	int m_zero18;
	int m_zero1c;
	int m_key2;
	void (*m_callback2)(void);
	int m_zero28;
	int m_zero2c;
};

void bfmeCategoryHead1054(BfmeCategoryHead1054 *p)
{
	int z = 0;
	p->m_key0 = bfmeMake1054(z);
	p->m_callback0 = reinterpret_cast<void (*)(void)>(0x00414556);
	p->m_zero08 = z;
	p->m_zero0c = z;
	p->m_key1 = bfmeMake1054(1);
	p->m_callback1 = reinterpret_cast<void (*)(void)>(0x004391a8);
	p->m_zero18 = z;
	p->m_zero1c = z;
	p->m_key2 = bfmeMake1054(2);
	p->m_callback2 = reinterpret_cast<void (*)(void)>(0x00411897);
	p->m_zero28 = z;
	p->m_zero2c = z;
	bfmeTailB1054Cdecl(reinterpret_cast<BfmeB1054 *>(p));
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

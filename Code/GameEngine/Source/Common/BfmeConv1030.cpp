// Open-BFME5 conversions.

extern "C" void *bfmeVft1030A[];
extern "C" void *bfmeVft1030B[];
extern "C" void *bfmeVft1030C[];

__declspec(dllimport) int __stdcall bfmeMake1030(int a, int b, int c);

class BfmeA1030
{
public:
	BfmeA1030 *bfmeGo1030A(void);
	void bfmeBase1030(void);

	void *m_bfmeVfptr;
	int m_bfmeH;
};

BfmeA1030 *BfmeA1030::bfmeGo1030A(void)
{
	bfmeBase1030();
	m_bfmeVfptr = bfmeVft1030A;
	m_bfmeH = bfmeMake1030(0, 0, 0);
	return this;
}

class BfmeSub1030
{
public:
	void bfmeInit1030(int a, int *p);
};

class BfmeB1030
{
public:
	BfmeB1030 *bfmeGo1030B(int a);

	void *m_bfmeVfptr;
	char m_bfmePad[8];
	BfmeSub1030 m_bfmeSub;
};

BfmeB1030 *BfmeB1030::bfmeGo1030B(int a)
{
	m_bfmeVfptr = bfmeVft1030B;
	m_bfmeSub.bfmeInit1030(a, &a);
	return this;
}

class BfmeC1030
{
public:
	BfmeC1030 *bfmeGo1030C(void);
	void bfmeBase1030C(int n, int m);

	void *m_bfmeVfptr;
	char m_bfmePad[0x1c];
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
};

BfmeC1030 *BfmeC1030::bfmeGo1030C(void)
{
	bfmeBase1030C(0x16, 8);

	int z = 0;

	m_bfme24 = z;
	m_bfme20 = z;
	m_bfme28 = z;
	m_bfmeVfptr = bfmeVft1030C;
	return this;
}

extern "C" void bfmeCtor1030(void);
extern "C" void bfmeDtor1030(void);
void __stdcall bfmeVecCtor1030(void *o, void *s, int sz, int n, void (*c)(void), void (*d)(void));

class BfmeD1030
{
public:
	BfmeD1030 *bfmeGo1030D(void *p);
};

BfmeD1030 *BfmeD1030::bfmeGo1030D(void *p)
{
	bfmeVecCtor1030(this, p, 0x14, 8, bfmeCtor1030, bfmeDtor1030);
	return this;
}

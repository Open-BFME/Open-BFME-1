// Open-BFME5 conversions.

class BfmeErr1043
{
public:
	BfmeErr1043();

	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1043[];
__declspec(noreturn) void __stdcall bfmeFatal1043(BfmeErr1043 *e, char *m);

class BfmeB1043
{
public:
	virtual void bfmeV01043();
	virtual void bfmeDo1043(int a, int b);
};

class BfmeC1043
{
public:
	void bfmeGo1043A(int a, int b);
	void bfmeGo1043B(int a, int b);

	BfmeB1043 *m_bfmeP;
};

void BfmeC1043::bfmeGo1043A(int a, int b)
{
	BfmeB1043 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1043 e;

		bfmeFatal1043(&e, g_bfmeMsg1043);
	}

	p->bfmeDo1043(a, b);
}

void BfmeC1043::bfmeGo1043B(int a, int b)
{
	BfmeB1043 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1043 e;

		bfmeFatal1043(&e, g_bfmeMsg1043);
	}

	p->bfmeDo1043(a, b);
}

class BfmeK1043
{
public:
	virtual void bfmeV01043K();
	virtual void bfmeDo3_1043(int a, int b, int c);
};

class BfmeJ1043
{
public:
	void bfmeGo1043D(int a, int b, int c);
	void bfmeGo1043E(int a, int b, int c);

	BfmeK1043 *m_bfmeP;
};

void BfmeJ1043::bfmeGo1043D(int a, int b, int c)
{
	BfmeK1043 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1043 e;

		bfmeFatal1043(&e, g_bfmeMsg1043);
	}

	p->bfmeDo3_1043(a, b, c);
}

void BfmeJ1043::bfmeGo1043E(int a, int b, int c)
{
	BfmeK1043 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1043 e;

		bfmeFatal1043(&e, g_bfmeMsg1043);
	}

	p->bfmeDo3_1043(a, b, c);
}

class BfmeM1043
{
public:
	virtual void bfmeV01043M();
	virtual void bfmeDo4_1043(int a, int b, int c, int d);
};

class BfmeL1043
{
public:
	void bfmeGo1043F(int a, int b, int c, int d);

	BfmeM1043 *m_bfmeP;
};

void BfmeL1043::bfmeGo1043F(int a, int b, int c, int d)
{
	BfmeM1043 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1043 e;

		bfmeFatal1043(&e, g_bfmeMsg1043);
	}

	p->bfmeDo4_1043(a, b, c, d);
}

class BfmeN1043
{
public:
	int bfmeGo1043H(int a, int b);

	BfmeB1043 *m_bfmeP;
};

int BfmeN1043::bfmeGo1043H(int a, int b)
{
	BfmeB1043 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1043 e;

		bfmeFatal1043(&e, g_bfmeMsg1043);
	}

	p->bfmeDo1043(a, b);
	return a;
}

extern "C" void *bfmeVft1043P[];

class BfmeErr2_1043
{
public:
	BfmeErr2_1043();

	char m_bfmePad[0xc];
};

extern char g_bfmeMsg2_1043[];
__declspec(noreturn) void __stdcall bfmeFatal2_1043(BfmeErr2_1043 *e, char *m);
__declspec(dllimport) void * __stdcall bfmeOpen1043(char *n);

class BfmeP1043
{
public:
	BfmeP1043 *bfmeGo1043P(char *n);

	void *m_bfmeVfptr;
	void *m_bfmeHandle;
};

BfmeP1043 *BfmeP1043::bfmeGo1043P(char *n)
{
	m_bfmeVfptr = bfmeVft1043P;
	m_bfmeHandle = bfmeOpen1043(n);

	if (m_bfmeHandle == 0) {
		BfmeErr2_1043 e;

		bfmeFatal2_1043(&e, g_bfmeMsg2_1043);
	}

	return this;
}

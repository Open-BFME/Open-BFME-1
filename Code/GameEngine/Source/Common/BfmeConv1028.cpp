// Open-BFME5 conversions.

extern "C" void *bfmeVft1028A[];

class BfmeA1028
{
public:
	BfmeA1028 *bfmeGo1028A(int a);
	void bfmeBase1028(int n);

	void *m_bfmeVfptr;
	char m_bfmePad[0x4c];
	int m_bfmeVal;
};

BfmeA1028 *BfmeA1028::bfmeGo1028A(int a)
{
	bfmeBase1028(0);
	m_bfmeVal = a;
	m_bfmeVfptr = bfmeVft1028A;
	return this;
}

extern char g_bfmeTag1028[];
void bfmeReport1028(int a, int b, char *t, int n);

void __stdcall bfmeGo1028B(int a)
{
	bfmeReport1028(0, a - 1, g_bfmeTag1028, 0x2432);
}

class BfmeSub1028
{
public:
	void bfmeFill1028(int *t, int *a);
};

class BfmeD1028
{
public:
	void bfmeGo1028D(int a);

	char m_bfmePad[0x80];
	BfmeSub1028 m_bfmeSub;
};

void BfmeD1028::bfmeGo1028D(int a)
{
	int tmp[2];

	m_bfmeSub.bfmeFill1028(tmp, &a);
}

struct BfmeQ1028
{
	char m_bfmePad[0x14];
	int m_bfmeVal;
};

class BfmeSet1028
{
public:
	void bfmeSet1028(int v);
};

class BfmeE1028
{
public:
	void bfmeGo1028E(BfmeQ1028 *q);

	char m_bfmePad[4];
	BfmeSet1028 m_bfmeSub;
	char m_bfmePad2[0xd7];
	char m_bfmeFlag;
};

void BfmeE1028::bfmeGo1028E(BfmeQ1028 *q)
{
	m_bfmeSub.bfmeSet1028(q->m_bfmeVal);
	m_bfmeFlag = 1;
}

class BfmeSink1028
{
public:
	void bfmeSend1028(int a, int *b, int *c);
};

struct BfmeOwn1028
{
	char m_bfmePad[0x20];
	BfmeSink1028 *m_bfmeSink;
};

class BfmeH1028
{
public:
	void bfmeGo1028H(void);

	char m_bfmePad[4];
	BfmeOwn1028 *m_bfmeOwner;
	int m_bfmeA;
	int m_bfmeB;
	char m_bfmePad2[0x3c];
	int m_bfmeState;
	char m_bfmePad3[0x10];
	int m_bfmeArg;
};

void BfmeH1028::bfmeGo1028H(void)
{
	m_bfmeState = -2;
	m_bfmeOwner->m_bfmeSink->bfmeSend1028(m_bfmeArg, &m_bfmeB, &m_bfmeA);
}

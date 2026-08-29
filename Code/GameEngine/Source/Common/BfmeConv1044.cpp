// Open-BFME5 conversions.

class BfmeB1044
{
public:
	void bfmeGo1044B(void);
	void bfmeTailA1044(void);
	void bfmeTailB1044(void);

	char m_bfmePad[0x18];
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
};

void BfmeB1044::bfmeGo1044B(void)
{
	int z = 0;
	int v = m_bfme1c;

	m_bfme18 = v;
	m_bfme24 = z;
	m_bfme20 = z;
	m_bfme2c = z;
	m_bfme28 = z;
	m_bfme30 = z;
	m_bfme34 = z;
	m_bfme38 = z;
	m_bfme3c = z;
	m_bfme40 = z;

	if (v != 0)
		bfmeTailA1044();
	else
		bfmeTailB1044();
}

class BfmeD1044
{
public:
	void bfmeStep1044(int a);
};

class BfmeE1044
{
public:
	void bfmeAdd1044(BfmeD1044 *p, int n);
};

class BfmeC1044
{
public:
	void bfmeGo1044C(int a);

	char m_bfmePad[4];
	char m_bfmeFlag;
};

void BfmeC1044::bfmeGo1044C(int a)
{
	BfmeD1044 *p = *(BfmeD1044 **)((char *)this - 0xdc);

	if (p != 0) {
		p->bfmeStep1044(a);
		m_bfmeFlag = 1;
		((BfmeE1044 *)((char *)this - 0xe4))->bfmeAdd1044(p, 1);
	}
}

class BfmeSrc1044
{
public:
	void *bfmeGet1044(void);
};

extern BfmeSrc1044 g_bfmeSrc1044;
__declspec(dllimport) void * __stdcall bfmeMap1044(void *h, int k);

class BfmeF1044
{
public:
	void *bfmeGo1044F(void);

	char m_bfmePad[4];
	int m_bfmeKey;
	char m_bfmePad2[0x1c];
	void *m_bfmeH;
	int m_bfmeN;
	void *m_bfmeM;
};

void *BfmeF1044::bfmeGo1044F(void)
{
	m_bfmeN++;

	if (m_bfmeH == 0) {
		m_bfmeH = g_bfmeSrc1044.bfmeGet1044();
		m_bfmeM = bfmeMap1044(m_bfmeH, m_bfmeKey);
	}

	return m_bfmeH;
}

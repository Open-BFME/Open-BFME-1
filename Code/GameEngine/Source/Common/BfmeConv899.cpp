// Open-BFME5 conversions.

class BfmeObjHC
{
public:
	bool bfmeDoHC(void *a, void *b, void *c, int d);
};

struct BfmeSubHC
{
	char m_bfmePad[0x3c];
	BfmeObjHC *m_bfmeObj;
};

class BfmeThingHC
{
public:
	bool bfmeGoHC(void *a, void *b, void *c);
	int m_bfmePad;
	BfmeSubHC *m_bfmeSub;
};

bool BfmeThingHC::bfmeGoHC(void *a, void *b, void *c)
{
	BfmeSubHC *s = m_bfmeSub;
	if (s) {
		BfmeObjHC *o = s->m_bfmeObj;
		if (o)
			return o->bfmeDoHC(a, b, c, 0);
	}
	return false;
}

extern char g_bfmeDefHD[];

class BfmeThingHD
{
public:
	char *bfmeGoHD(int k);
	int m_bfmePad;
	char *m_bfmeP;
};

char *BfmeThingHD::bfmeGoHD(int k)
{
	switch (k) {
		case 1: return m_bfmeP + 0x10;
		case 2: return m_bfmeP + 0xc;
		case 3: return m_bfmeP + 0x14;
	}
	return g_bfmeDefHD;
}

void *bfmeMakeHE(void);

class BfmeThingHE
{
public:
	void bfmeGoHE(int i);
	char m_bfmePad[0x128];
	void *m_bfmeArr[8];
};

void BfmeThingHE::bfmeGoHE(int i)
{
	if (i >= 0 && i < 8)
		m_bfmeArr[i] = bfmeMakeHE();
}

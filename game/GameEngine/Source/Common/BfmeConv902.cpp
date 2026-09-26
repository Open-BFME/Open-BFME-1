// Open-BFME5 conversions.

class BfmeItemKA
{
public:
	void bfmeDoKA();
};

extern BfmeItemKA **g_bfmeBegKA;
extern BfmeItemKA **g_bfmeEndKA;

void bfmeGoKA(void)
{
	BfmeItemKA **p = g_bfmeBegKA;
	BfmeItemKA **e = g_bfmeEndKA;
	while (p != e) {
		(*p)->bfmeDoKA();
		++p;
	}
}

struct BfmeRefKB
{
	void *m_bfmeA;
	unsigned int m_bfmeBits;
};

class BfmeOldKB
{
public:
	void bfmeRelKB();
};

class BfmeThingKB
{
public:
	void bfmeGoKB(BfmeRefKB *r);
	BfmeOldKB *m_bfmeOld;
};

void BfmeThingKB::bfmeGoKB(BfmeRefKB *r)
{
	if (r) {
		++*(unsigned short *)&r->m_bfmeBits;
		if (m_bfmeOld)
			m_bfmeOld->bfmeRelKB();
		m_bfmeOld = (BfmeOldKB *)r;
		r->m_bfmeBits |= 0x1000000;
	}
}

class BfmeObjKD
{
public:
	virtual void bfmeDoKD(int f);
};

char bfmeGoKD(BfmeObjKD **beg, BfmeObjKD **end, char r)
{
	while (beg != end) {
		BfmeObjKD *o = *beg;
		if (o)
			o->bfmeDoKD(1);
		++beg;
	}
	return r;
}

__declspec(dllimport) void *__stdcall bfmeTickKE(int a);
unsigned int __stdcall bfmeQueryKE(void *h, int n);

class BfmeThingKE
{
public:
	void bfmeGoKE();
	char m_bfmePad[0x302c];
	int m_bfmeA;
	char m_bfmePad2[0x14];
	char m_bfmeB;
};

void BfmeThingKE::bfmeGoKE()
{
	void *h = bfmeTickKE(0);
	unsigned int v = bfmeQueryKE(h, 4);
	m_bfmeA = (v >> 0x12) & 1;
	m_bfmeB = (char)((v >> 0x13) & 1);
}

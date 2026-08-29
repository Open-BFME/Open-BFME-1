// Open-BFME5 conversions.

struct BfmeRec1014
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeStore1014
{
public:
	BfmeRec1014 *bfmeFind1014(int id);
};

extern BfmeStore1014 *g_bfmeStore1014;

class BfmeD1014
{
public:
	char bfmeGo1014D();

	char m_bfmePad[0x28];
	int m_bfmeId;
};

char BfmeD1014::bfmeGo1014D()
{
	int id = m_bfmeId;

	if (id != 0) {
		BfmeRec1014 *r = g_bfmeStore1014->bfmeFind1014(id);
		if (r == 0 || (r->m_bfmeFlags & 1) != 0) {
			m_bfmeId = 0;
			return 1;
		}
	}

	return 0;
}

class BfmeE1014
{
public:
	virtual void bfmeVE01014();
	virtual void bfmeKill1014(int f);
	virtual void bfmeVE21014();
	virtual void bfmeVE31014();
	virtual void bfmeVE41014();
	virtual void bfmeVE51014();
	virtual void bfmeVE61014();
	virtual void bfmeVE71014();
	virtual void bfmeStop1014();
};

extern BfmeE1014 *g_bfmeE1014;

void bfmeGo1014E(void)
{
	BfmeE1014 *p = g_bfmeE1014;

	if (p != 0) {
		p->bfmeStop1014();
		if (g_bfmeE1014 != 0)
			g_bfmeE1014->bfmeKill1014(1);
		g_bfmeE1014 = 0;
	}
}

class BfmeF1014A
{
public:
	void bfmeDo1014F(int a);
};

class BfmeF1014B
{
public:
	void bfmeDo1014G(int a);
};

class BfmeF1014
{
public:
	void bfmeGo1014F(int a);

	char m_bfmePad[0x3094];
	BfmeF1014A *m_bfmeA;
	BfmeF1014B *m_bfmeB;
};

void BfmeF1014::bfmeGo1014F(int a)
{
	if (m_bfmeA != 0)
		m_bfmeA->bfmeDo1014F(a);

	if (m_bfmeB != 0)
		m_bfmeB->bfmeDo1014G(a);
}

class BfmeLink1014
{
public:
	virtual void bfmeDel1014(int f);

	BfmeLink1014 *m_bfmeNext;
};

class BfmeG1014
{
public:
	virtual void bfmeVG01014();
	virtual void bfmeVG11014();
	virtual void bfmeVG21014();
	virtual void bfmeVG31014();
	virtual void bfmeVG41014();
	virtual void bfmeVG51014();
	virtual void bfmeVG61014();
	virtual void bfmeVG71014();
	virtual void bfmeVG81014();
	virtual void bfmeVG91014();
	virtual void bfmeVG101014();
	virtual void bfmeVG111014();
	virtual void bfmeVG121014();
	virtual void bfmeVG131014();
	virtual void bfmeVG141014();
	virtual void bfmeVG151014();
	virtual void bfmeVG161014();
	virtual void bfmeVG171014();
	virtual void bfmeVG181014();
	virtual void bfmeVG191014();
	virtual void bfmeVG201014();
	virtual void bfmeVG211014();
	virtual void bfmeVG221014();
	virtual void bfmeVG231014();
	virtual void bfmeVG241014();
	virtual void bfmeVG251014();
	virtual void bfmeVG261014();
	virtual void bfmeVG271014();
	virtual void bfmeVG281014();
	virtual void bfmeVG291014();
	virtual void bfmeVG301014();
	virtual void bfmeVG311014();
	virtual void bfmeVG321014();
	virtual void bfmeVG331014();
	virtual void bfmeVG341014();
	virtual void bfmeVG351014();
	virtual void bfmeVG361014();
	virtual BfmeLink1014 *bfmeHead1014();
	void bfmeGo1014G(void);

	char m_bfmePad[0x30];
	int m_bfmeCur;
};

void BfmeG1014::bfmeGo1014G(void)
{
	BfmeLink1014 *p = bfmeHead1014();

	while (p != 0) {
		BfmeLink1014 **slot = &p->m_bfmeNext;
		BfmeLink1014 *next = *slot;
		*slot = 0;
		p->bfmeDel1014(1);
		p = next;
	}

	m_bfmeCur = 0;
}

class BfmeH1014
{
public:
	virtual void bfmeVH01014();
	virtual void bfmeVH11014();
	virtual void bfmeVH21014();
	virtual void bfmeVH31014();
	virtual void bfmeNotify1014();
	void bfmeGo1014H(char v, int n);

	char m_bfmePad[0xbd];
	char m_bfmeFlag;
	char m_bfmePad2[0xf2];
	char m_bfmeV;
	char m_bfmePad3[0xb];
	int m_bfmeN;
};

void BfmeH1014::bfmeGo1014H(char v, int n)
{
	if (v == m_bfmeV && n == m_bfmeN)
		return;

	m_bfmeV = v;
	m_bfmeFlag = v;
	m_bfmeN = n;
	bfmeNotify1014();
}

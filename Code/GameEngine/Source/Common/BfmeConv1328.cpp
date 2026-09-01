// Open-BFME5 conversions.

extern void *g_bfmeVftTZA[];
extern void *g_bfmeVftTZB[];

class BfmeElemTZA
{
public:
	~BfmeElemTZA();
	char m_bfmePad[4];
};

class BfmeElemTZB
{
public:
	~BfmeElemTZB();
	char m_bfmePad[0x24];
};

void bfmeFreeTZA(void *p);
void bfmeFreeTZB(void *p);

class BfmeThingTZA
{
public:
	void *bfmeDelTZA(unsigned char flags);
	void *m_bfmeVft;
	BfmeElemTZA *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void *BfmeThingTZA::bfmeDelTZA(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftTZA;
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
	if (flags & 1)
		bfmeFreeTZA(this);
	return this;
}

class BfmeThingTZB
{
public:
	void *bfmeDelTZB(unsigned char flags);
	void *m_bfmeVft;
	BfmeElemTZB *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void *BfmeThingTZB::bfmeDelTZB(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftTZB;
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
	if (flags & 1)
		bfmeFreeTZB(this);
	return this;
}

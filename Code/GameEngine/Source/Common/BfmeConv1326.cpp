// Open-BFME5 conversions.

extern void *g_bfmeVftTXA[];

void __stdcall bfmeReleaseATXA(void *p);
void __stdcall bfmeReleaseBTXA(void *p);
void bfmeFreeArrayTXA(void *p);
void bfmeFreeTXA(void *p);

class BfmeThingTXA
{
public:
	void *bfmeDelTXA(unsigned char flags);
	void bfmeDtorTXA();
	void *m_bfmeVft;
	char m_bfmePad[8];
	void *m_bfmeBuf;
	char m_bfmePad2[8];
	void *m_bfmeB;
	void *m_bfmeA;
};

void *BfmeThingTXA::bfmeDelTXA(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftTXA;
	bfmeDtorTXA();
	if (m_bfmeA)
		bfmeReleaseATXA(m_bfmeA);
	if (m_bfmeB)
		bfmeReleaseBTXA(m_bfmeB);
	if (m_bfmeBuf)
		bfmeFreeArrayTXA(m_bfmeBuf);
	if (flags & 1)
		bfmeFreeTXA(this);
	return this;
}

extern void *g_bfmeVftTXB[];

class BfmeResTXB
{
public:
	virtual void bfmeReleaseTXB(int f) = 0;
};

extern BfmeResTXB *g_bfmeOneTXB;
extern BfmeResTXB *g_bfmeTwoTXB;

void bfmeFreeTXB(void *p);

class BfmeThingTXB
{
public:
	void *bfmeDelTXB(unsigned char flags);
	void *m_bfmeVft;
};

void *BfmeThingTXB::bfmeDelTXB(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftTXB;
	if (g_bfmeOneTXB)
		g_bfmeOneTXB->bfmeReleaseTXB(1);
	g_bfmeOneTXB = 0;
	if (g_bfmeTwoTXB)
		g_bfmeTwoTXB->bfmeReleaseTXB(1);
	g_bfmeTwoTXB = 0;
	if (flags & 1)
		bfmeFreeTXB(this);
	return this;
}

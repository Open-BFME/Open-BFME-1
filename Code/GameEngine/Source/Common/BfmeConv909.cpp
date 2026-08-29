// Open-BFME5 conversions.

int bfmeTestSB(void);

struct BfmeThingSB
{
	char m_bfmePad[0x10c];
	int m_bfmeOn;
	char m_bfmePad2[0x218];
	int m_bfmeSlot;
};

void *bfmeGoSB(BfmeThingSB *t)
{
	int ok = 0;
	if (t->m_bfmeOn)
		ok = bfmeTestSB();
	if (!ok)
		return 0;
	return &t->m_bfmeSlot;
}

class BfmeSrcSG
{
public:
	int bfmeQuerySG();
};

class BfmeThingSG
{
public:
	void bfmeGoSG();
	BfmeSrcSG *m_bfmeSrc;
	char m_bfmeA;
	char m_bfmeB;
	char m_bfmeDone;
};

void BfmeThingSG::bfmeGoSG()
{
	if (m_bfmeDone)
		return;
	int r = m_bfmeSrc->bfmeQuerySG();
	m_bfmeA = (char)r;
	m_bfmeB = (r == -1);
	m_bfmeDone = 1;
}

class Gen_00832090
{
public:
	void m();
};

extern char g_bfmeVftTA[];
void bfmeFreeTA(void *p);

class BfmeThingTA
{
public:
	void bfmeGoTA();
	char *m_bfmeVft;
	char m_bfmePad[8];
	void *m_bfmeP;
	char m_bfmeFlag;
};

void BfmeThingTA::bfmeGoTA()
{
	m_bfmeVft = g_bfmeVftTA;
	if (m_bfmeFlag)
		bfmeFreeTA(m_bfmeP);
	((Gen_00832090 *)this)->m();
}

extern int g_bfmeCountTB;
extern void *g_bfmePtrTB;
void bfmeOneTB(void);
void *bfmeTwoTB(void);

class BfmeThingTB
{
public:
	BfmeThingTB *bfmeGoTB();
};

BfmeThingTB *BfmeThingTB::bfmeGoTB()
{
	if (!g_bfmeCountTB) {
		bfmeOneTB();
		g_bfmePtrTB = bfmeTwoTB();
		++g_bfmeCountTB;
	}
	return this;
}


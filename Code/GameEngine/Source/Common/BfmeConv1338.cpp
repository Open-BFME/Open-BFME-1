// Open-BFME5 conversions.

extern void *g_bfmeVftAUNA[];
extern void *g_bfmeVftBUNA[];

void bfmeFreeRecUNA(void *p);
void bfmeFreeUNA(void *p, int n);

class BfmeThingUNA
{
public:
	void *bfmeDelUNA(unsigned char flags);
	void *m_bfmeVft;
	int m_bfme04;
	void *m_bfmeRec;
};

void *BfmeThingUNA::bfmeDelUNA(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftAUNA;
	bfmeFreeRecUNA(m_bfmeRec);
	m_bfmeRec = 0;
	m_bfme04 = 0;
	m_bfmeVft = g_bfmeVftBUNA;
	if (flags & 1)
		bfmeFreeUNA(this, 0x14);
	return this;
}

extern void *g_bfmeVftUNB[];

void *bfmeAllocUNB(unsigned n);
void *bfmeMakeRecUNB(int n);

class BfmeThingUNB
{
public:
	void *m_bfmeVft;
	int m_bfme04;
	void *m_bfmeRec;
	int m_bfme0c;
	char m_bfme10;
};

BfmeThingUNB *bfmeNewUNB(void)
{
	BfmeThingUNB *p = (BfmeThingUNB *)bfmeAllocUNB(0x14);
	if (p) {
		p->m_bfmeVft = g_bfmeVftUNB;
		p->m_bfmeRec = bfmeMakeRecUNB(0x1000);
		p->m_bfme04 = 0;
		p->m_bfme0c = 0;
		p->m_bfme10 = 0;
		return p;
	}
	return 0;
}

extern void *g_bfmeVftUNC[];

class BfmeThingUNC;

class BfmeSinkUNC
{
public:
	virtual void bfmeV0UNC() = 0;
	virtual void bfmeRegisterUNC(BfmeThingUNC *p) = 0;
};

struct BfmeMidUNC
{
	char m_bfmePad[0x2a0];
	BfmeSinkUNC *m_bfmeSink;
};

struct BfmeOwnerUNC
{
	char m_bfmePad[0xc];
	BfmeMidUNC *m_bfmeMid;
};

int bfmeNextIdUNC(void);

class BfmeThingUNC
{
public:
	BfmeThingUNC(int a, BfmeOwnerUNC *o);
	void bfmeBaseUNC();
	void *m_bfmeVft;
	int m_bfmeA;
	BfmeOwnerUNC *m_bfmeOwner;
	int m_bfmeId;
	BfmeSinkUNC *m_bfmeSink;
};

BfmeThingUNC::BfmeThingUNC(int a, BfmeOwnerUNC *o)
{
	m_bfmeVft = g_bfmeVftUNC;
	bfmeBaseUNC();
	m_bfmeOwner = o;
	m_bfmeA = a;
	m_bfmeId = bfmeNextIdUNC();
	m_bfmeSink = o->m_bfmeMid->m_bfmeSink;
	m_bfmeSink->bfmeRegisterUNC(this);
}

extern char g_bfmeEmptyUND[];

class BfmeStrUND
{
public:
	void bfmeSetUND(const char *s);
	char m_bfmePad[4];
};

void bfmeFreeArrayUND(void *p);

class BfmeThingUND
{
public:
	void bfmeClearUND();
	char m_bfmePad[0xc];
	BfmeStrUND m_bfmeStr[6];
	char m_bfmePad2[0x30];
	void *m_bfmeBuf;
	int m_bfme58;
	char m_bfmePad3[8];
	char m_bfme64;
};

void BfmeThingUND::bfmeClearUND()
{
	if (m_bfmeBuf) {
		bfmeFreeArrayUND(m_bfmeBuf);
		m_bfmeBuf = 0;
	}
	m_bfme58 = 0;
	m_bfme64 = 0;
	for (int i = 0; i < 6; ++i)
		m_bfmeStr[i].bfmeSetUND(g_bfmeEmptyUND);
}

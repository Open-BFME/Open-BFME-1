// Open-BFME5 conversions.

extern void *g_bfmeVftTUA[];

class BfmeSubTUA
{
public:
	void bfmeInitTUA();
	void *m_bfmeVft;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeThingTUA
{
public:
	BfmeThingTUA();
	int m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfmePad[3];
	int m_bfme0c;
	BfmeSubTUA m_bfmeSub;
	int m_bfme20;
};

BfmeThingTUA::BfmeThingTUA()
{
	BfmeSubTUA *s = &m_bfmeSub;
	s->bfmeInitTUA();
	s->m_bfme08 = 0;
	s->m_bfme0c = 0;
	s->m_bfme04 = 0;
	s->m_bfmeVft = g_bfmeVftTUA;
	m_bfme00 = 0;
	m_bfme04 = 0;
	m_bfme0c = 0;
	m_bfme20 = 0;
	m_bfme08 = 0;
}

extern void *g_bfmeVftTVA[];

__declspec(dllimport) void __stdcall bfmeReleaseTVA(void *h);
void bfmeFreeTVA(void *p);

class BfmeThingTVA
{
public:
	void *bfmeDelTVA(unsigned char flags);
	void bfmeDtorTVA();
	void *m_bfmeVft;
	void *m_bfmeHandle;
};

void *BfmeThingTVA::bfmeDelTVA(unsigned char flags)
{
	void *h = m_bfmeHandle;
	m_bfmeVft = g_bfmeVftTVA;
	if (h)
		bfmeReleaseTVA(h);
	bfmeDtorTVA();
	if (flags & 1)
		bfmeFreeTVA(this);
	return this;
}

__declspec(dllimport) void __stdcall bfmeReleaseTVB(void *h);
void bfmeFreeArrayTVB(void *p);
void bfmeFreeTVB(void *p);

class BfmeThingTVB
{
public:
	void *bfmeDelTVB(unsigned char flags);
	void *m_bfmeObj;
	void *m_bfmeBuf;
};

void *BfmeThingTVB::bfmeDelTVB(unsigned char flags)
{
	if (m_bfmeObj)
		bfmeReleaseTVB(m_bfmeObj);
	if (m_bfmeBuf)
		bfmeFreeArrayTVB(m_bfmeBuf);
	if (flags & 1)
		bfmeFreeTVB(this);
	return this;
}

class BfmeSinkTVC
{
public:
	virtual void bfmeV0TVC() = 0;
	virtual void bfmeV1TVC() = 0;
	virtual void bfmeV2TVC() = 0;
	virtual void bfmeDropTVC(void *p, int f) = 0;
};

BfmeSinkTVC *bfmeGetTVC(void);
void bfmeFreeTVC(void *p, int n);

class BfmeThingTVC
{
public:
	void *bfmeDelTVC(unsigned char flags);
	int m_bfme00;
	int m_bfme04;
	void *m_bfmeItem;
};

void *BfmeThingTVC::bfmeDelTVC(unsigned char flags)
{
	bfmeGetTVC()->bfmeDropTVC(m_bfmeItem, 1);
	m_bfme04 = 0;
	m_bfme00 = 0;
	m_bfmeItem = 0;
	if (flags & 1)
		bfmeFreeTVC(this, 0xc);
	return this;
}

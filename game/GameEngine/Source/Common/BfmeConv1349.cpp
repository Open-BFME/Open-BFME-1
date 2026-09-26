// Open-BFME5 conversions.

struct BfmeSrcVCB
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmeTextA[0x80];
	char m_bfmeTextB[4];
};

class BfmeBufVCB
{
public:
	void bfmeAppendVCB(const char *s);
	char m_bfmePad[8];
};

class BfmeThingVCB
{
public:
	void bfmeInitVCB(BfmeSrcVCB *s, int a);
	char m_bfmePad[4];
	int m_bfme04;
	int m_bfme08;
	BfmeBufVCB m_bfmeBufA;
	BfmeBufVCB m_bfmeBufB;
	char m_bfmePad2[0x10];
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
};

void BfmeThingVCB::bfmeInitVCB(BfmeSrcVCB *s, int a)
{
	m_bfme04 = a;
	m_bfmeBufA.bfmeAppendVCB(s->m_bfmeTextA);
	m_bfmeBufB.bfmeAppendVCB(s->m_bfmeTextB);
	m_bfme08 = s->m_bfme00;
	m_bfme2c = s->m_bfme04;
	m_bfme30 = s->m_bfme08;
	m_bfme34 = s->m_bfme0c;
	m_bfme38 = s->m_bfme10;
	m_bfme3c = s->m_bfme14;
}

class BfmeSinkVCC
{
public:
	virtual void bfmeV0VCC() = 0;
	virtual void bfmeV1VCC() = 0;
	virtual void bfmeV2VCC() = 0;
	virtual void bfmeDropVCC(void *p, int f) = 0;
};

BfmeSinkVCC *bfmeGetVCC(void);
void bfmeFreeVCC(void *p, int n);

struct BfmeNodeVCC
{
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
};

struct BfmeThingVCC
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeNodeVCC *m_bfme18;
};

void __stdcall bfmeGoVCC(BfmeThingVCC *p)
{
	BfmeNodeVCC *n = p->m_bfme18;
	if (n) {
		bfmeGetVCC()->bfmeDropVCC(n->m_bfme08, 1);
		n->m_bfme04 = 0;
		n->m_bfme00 = 0;
		n->m_bfme08 = 0;
		bfmeFreeVCC(n, 0xc);
	}
	p->m_bfme04 = 0;
	p->m_bfme00 = 0;
	p->m_bfme08 = 0;
	p->m_bfme0c = 0;
	p->m_bfme10 = 0;
	p->m_bfme14 = 0;
	p->m_bfme18 = 0;
}

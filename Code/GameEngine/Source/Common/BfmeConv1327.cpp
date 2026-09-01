// Open-BFME5 conversions.

extern void *g_bfmeVftATYA[];
extern void *g_bfmeVftBTYA[];

class BfmeSlotTYA
{
public:
	void bfmeDtorBTYA();
	char m_bfmePad[8];
};

class BfmeHeadTYA
{
public:
	void bfmeDtorATYA();
	char m_bfmePad[8];
};

void bfmeFreeTYA(void *p, int n);

class BfmeThingTYA
{
public:
	void *bfmeDelTYA(unsigned char flags);
	void *m_bfmeVft;
	int m_bfme04;
	char m_bfmePad[8];
	BfmeSlotTYA m_bfmeC;
	BfmeSlotTYA m_bfmeB;
	BfmeHeadTYA m_bfmeA;
	int m_bfme28;
	int m_bfme2c;
	char m_bfme30;
	char m_bfmePad2[0x24];
	char m_bfme55;
};

void *BfmeThingTYA::bfmeDelTYA(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftATYA;
	m_bfme04 = 0;
	m_bfme28 = 0;
	m_bfme30 = 0;
	m_bfme55 = 0;
	m_bfme2c = 0;
	m_bfmeA.bfmeDtorATYA();
	m_bfmeB.bfmeDtorBTYA();
	m_bfmeC.bfmeDtorBTYA();
	m_bfmeVft = g_bfmeVftBTYA;
	if (flags & 1)
		bfmeFreeTYA(this, 0xd8);
	return this;
}

extern void *g_bfmeVftTYB[];

class BfmeNodeTYB
{
public:
	virtual void bfmeReleaseTYB(int f) = 0;
	BfmeNodeTYB *m_bfmeNext;
};

class BfmeThingTYB;

class BfmeOwnerTYB
{
public:
	virtual void bfmeV0TYB() = 0;
	virtual void bfmeV1TYB() = 0;
	virtual void bfmeV2TYB() = 0;
	virtual void bfmeV3TYB() = 0;
	virtual void bfmeV4TYB() = 0;
	virtual void bfmeV5TYB() = 0;
	virtual void bfmeV6TYB() = 0;
	virtual void bfmeV7TYB() = 0;
	virtual void bfmeV8TYB() = 0;
	virtual void bfmeV9TYB() = 0;
	virtual void bfmeV10TYB() = 0;
	virtual void bfmeDetachTYB(BfmeThingTYB *p) = 0;
};

void bfmeFreeTYB(void *p);

class BfmeThingTYB
{
public:
	void *bfmeDelTYB(unsigned char flags);
	void *m_bfmeVft;
	char m_bfmePad[8];
	BfmeOwnerTYB *m_bfmeOwner;
	char m_bfmePad2[0xc];
	BfmeNodeTYB *m_bfmeHead;
};

void *BfmeThingTYB::bfmeDelTYB(unsigned char flags)
{
	BfmeNodeTYB *n = m_bfmeHead;
	m_bfmeVft = g_bfmeVftTYB;
	while (n) {
		BfmeNodeTYB *next = n->m_bfmeNext;
		n->bfmeReleaseTYB(1);
		n = next;
	}
	m_bfmeHead = 0;
	if (m_bfmeOwner)
		m_bfmeOwner->bfmeDetachTYB(this);
	if (flags & 1)
		bfmeFreeTYB(this);
	return this;
}

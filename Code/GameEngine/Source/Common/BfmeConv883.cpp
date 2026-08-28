extern "C" unsigned char bfmeStrERA[];
extern "C" unsigned char bfmeVftERA[];

class BfmeOtherERA
{
public:
	void bfmeStrERA(const char *s);
};

struct BfmeThingERA
{
	BfmeThingERA *bfmeCtorERA();
	void *m_bfmeVft;
	BfmeOtherERA m_bfmeSub;
	unsigned char m_bfmePad[3];
	char volatile m_bfmeFlag;
};

BfmeThingERA *BfmeThingERA::bfmeCtorERA()
{
	m_bfmeVft = bfmeVftERA;
	m_bfmeSub.bfmeStrERA((const char *)bfmeStrERA);
	m_bfmeFlag = 0;
	return this;
}

class BfmeSubERB
{
public:
	void bfmeValERB(BfmeOtherERA *o, int v);
};

struct BfmeHeldERB
{
	unsigned char m_bfmeHead[8];
	int m_bfmeX;
};

struct BfmeThingERB
{
	BfmeOtherERA *bfmeGoERB(BfmeOtherERA *other);
	unsigned char m_bfmeHeadA[4];
	BfmeSubERB m_bfmeSub;
	unsigned char m_bfmeHeadB[0x17];
	BfmeHeldERB *m_bfmeP;
};

BfmeOtherERA *BfmeThingERB::bfmeGoERB(BfmeOtherERA *other)
{
	volatile int tmp = 0;
	BfmeHeldERB *p = m_bfmeP;
	if (!p)
	{
		other->bfmeStrERA((const char *)bfmeStrERA);
		return other;
	}
	m_bfmeSub.bfmeValERB(other, p->m_bfmeX);
	return other;
}

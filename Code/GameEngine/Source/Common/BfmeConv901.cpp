// Open-BFME5 conversions.

struct BfmeHeadJA
{
	char m_bfmePad[0x108];
	int m_bfmeVal;
};

struct BfmeSlotJA;

class BfmeHookJA
{
public:
	BfmeSlotJA *bfmeCallJA();
};

struct BfmeSlotJA
{
	int m_bfmePad;
	BfmeHookJA *m_bfmeHook;
};

class BfmeThingJA
{
public:
	int bfmeGoJA();
	int m_bfmePad;
	BfmeSlotJA *m_bfmeSlot;
	char m_bfmePad2[0xf4];
	BfmeHeadJA *m_bfmeHead;
};

int BfmeThingJA::bfmeGoJA()
{
	BfmeHeadJA *h = m_bfmeHead;
	if (h)
		return h->m_bfmeVal;
	BfmeSlotJA *s = m_bfmeSlot;
	if (!s)
		return 0x60;
	BfmeSlotJA *r = s;
	if (s->m_bfmeHook)
		r = s->m_bfmeHook->bfmeCallJA();
	return (int)r + 0x60;
}

class BfmeTargetJB
{
public:
	bool bfmeTailJB();
};

struct BfmeItemJB
{
	char m_bfmePad[0xfc];
	BfmeTargetJB *m_bfmeTarget;
};

struct BfmeListJB
{
	BfmeListJB *m_bfmeHead;
	char m_bfmePad[4];
	BfmeItemJB *m_bfmeItem;
};

struct BfmeHolderJB
{
	BfmeListJB *m_bfmeList;
};

class BfmeGlobJB
{
public:
	virtual void bfmeSlotJB00();
	virtual void bfmeSlotJB01();
	virtual void bfmeSlotJB02();
	virtual void bfmeSlotJB03();
	virtual void bfmeSlotJB04();
	virtual void bfmeSlotJB05();
	virtual void bfmeSlotJB06();
	virtual void bfmeSlotJB07();
	virtual void bfmeSlotJB08();
	virtual void bfmeSlotJB09();
	virtual void bfmeSlotJB10();
	virtual void bfmeSlotJB11();
	virtual void bfmeSlotJB12();
	virtual void bfmeSlotJB13();
	virtual void bfmeSlotJB14();
	virtual void bfmeSlotJB15();
	virtual void bfmeSlotJB16();
	virtual void bfmeSlotJB17();
	virtual void bfmeSlotJB18();
	virtual void bfmeSlotJB19();
	virtual void bfmeSlotJB20();
	virtual void bfmeSlotJB21();
	virtual void bfmeSlotJB22();
	virtual void bfmeSlotJB23();
	virtual void bfmeSlotJB24();
	virtual void bfmeSlotJB25();
	virtual void bfmeSlotJB26();
	virtual void bfmeSlotJB27();
	virtual void bfmeSlotJB28();
	virtual void bfmeSlotJB29();
	virtual void bfmeSlotJB30();
	virtual void bfmeSlotJB31();
	virtual void bfmeSlotJB32();
	virtual void bfmeSlotJB33();
	virtual void bfmeSlotJB34();
	virtual void bfmeSlotJB35();
	virtual void bfmeSlotJB36();
	virtual void bfmeSlotJB37();
	virtual void bfmeSlotJB38();
	virtual void bfmeSlotJB39();
	virtual void bfmeSlotJB40();
	virtual void bfmeSlotJB41();
	virtual void bfmeSlotJB42();
	virtual void bfmeSlotJB43();
	virtual void bfmeSlotJB44();
	virtual void bfmeSlotJB45();
	virtual void bfmeSlotJB46();
	virtual void bfmeSlotJB47();
	virtual void bfmeSlotJB48();
	virtual void bfmeSlotJB49();
	virtual void bfmeSlotJB50();
	virtual void bfmeSlotJB51();
	virtual void bfmeSlotJB52();
	virtual void bfmeSlotJB53();
	virtual void bfmeSlotJB54();
	virtual void bfmeSlotJB55();
	virtual void bfmeSlotJB56();
	virtual void bfmeSlotJB57();
	virtual void bfmeSlotJB58();
	virtual void bfmeSlotJB59();
	virtual void bfmeSlotJB60();
	virtual void bfmeSlotJB61();
	virtual void bfmeSlotJB62();
	virtual BfmeHolderJB *bfmeGetJB();
};

extern BfmeGlobJB *g_bfmeGlobJB;

bool bfmeGoJB(void)
{
	BfmeListJB *l = g_bfmeGlobJB->bfmeGetJB()->m_bfmeList;
	if (l->m_bfmeHead != l)
		return l->m_bfmeHead->m_bfmeItem->m_bfmeTarget->bfmeTailJB();
	return false;
}

class BfmeBaseJC
{
public:
	BfmeBaseJC(void *a);
	virtual ~BfmeBaseJC();
	char m_bfmePad[0x2c];
	int m_bfme30;
	char m_bfmePad2[4];
	int m_bfme38;
};

class BfmeThingJC : public BfmeBaseJC
{
public:
	BfmeThingJC(void *a);
	virtual ~BfmeThingJC();
};

BfmeThingJC::BfmeThingJC(void *a) : BfmeBaseJC(a)
{
	m_bfme30 = 1;
	m_bfme38 = 1;
}


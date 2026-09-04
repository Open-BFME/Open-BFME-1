// Open-BFME5 conversions.

class BfmeThingNA
{
public:
	void bfmeGoNA();
	void bfmeOneNA();
	void bfmeTwoNA();
	char m_bfmePad[0x18];
	char m_bfmeBits;
	char m_bfmePad2[0x17];
	char m_bfmeC;
	char m_bfmeB;
	char m_bfmeD;
};

void BfmeThingNA::bfmeGoNA()
{
	m_bfmeD = 1;
	if (m_bfmeB) {
		if (!(m_bfmeBits & 0x10) || !m_bfmeC)
			bfmeOneNA();
	} else if (!(m_bfmeBits & 0x20)) {
		bfmeTwoNA();
	}
}

class BfmeSubNB
{
public:
	virtual void bfmeSlotNB00();
	virtual void bfmeSlotNB01();
	virtual void bfmeSlotNB02();
	virtual void bfmeSlotNB03();
	virtual void bfmeSlotNB04();
	virtual void bfmeSlotNB05();
	virtual void bfmeSlotNB06();
	virtual void bfmeSlotNB07();
	virtual void bfmeSlotNB08();
	virtual void bfmeSlotNB09();
	virtual void bfmeSlotNB10();
	virtual void bfmeSlotNB11();
	virtual void bfmeSlotNB12();
	virtual void bfmeSlotNB13();
	virtual void bfmeSlotNB14();
	virtual void bfmeSlotNB15();
	virtual void bfmeSlotNB16();
	virtual void bfmeSlotNB17();
	virtual void bfmeSlotNB18();
	virtual void bfmeSlotNB19();
	virtual void bfmeSlotNB20();
	virtual void bfmeSlotNB21();
	virtual void bfmeSlotNB22();
	virtual void bfmeSlotNB23();
	virtual void bfmeSlotNB24();
	virtual void bfmeSlotNB25();
	virtual void bfmeSlotNB26();
	virtual void bfmeSlotNB27();
	virtual void bfmeSlotNB28();
	virtual void bfmeSlotNB29();
	virtual void bfmeSlotNB30();
	virtual void bfmeSlotNB31();
	virtual void bfmeSlotNB32();
	virtual void bfmeSlotNB33();
	virtual void bfmeSlotNB34();
	virtual void bfmeSlotNB35();
	virtual void bfmeSlotNB36();
	virtual void bfmeSlotNB37();
	virtual void bfmeSlotNB38();
	virtual void bfmeSlotNB39();
	virtual void bfmeSlotNB40();
	virtual void bfmeSlotNB41();
	virtual void bfmeSlotNB42();
	virtual void bfmeSlotNB43();
	virtual void bfmeSlotNB44();
	virtual void bfmeSlotNB45();
	virtual void bfmeSlotNB46();
	virtual void bfmeSlotNB47();
	virtual void bfmeSlotNB48();
	virtual void bfmeSlotNB49();
	virtual void bfmeSlotNB50();
	virtual void bfmeSlotNB51();
	virtual void bfmeSlotNB52();
	virtual void bfmeSlotNB53();
	virtual void bfmeSlotNB54();
	virtual void bfmeSlotNB55();
	virtual void bfmeSlotNB56();
	virtual void bfmeSlotNB57();
	virtual void bfmeSlotNB58();
	virtual void bfmeSlotNB59();
	virtual void bfmeSlotNB60();
	virtual void bfmeSlotNB61();
	virtual void bfmeSlotNB62();
	virtual void bfmeSlotNB63();
	virtual void bfmeSlotNB64();
	virtual void bfmeSlotNB65();
	virtual void bfmeSlotNB66();
	virtual void bfmeSlotNB67();
	virtual void bfmeSlotNB68();
	virtual void bfmeSlotNB69();
	virtual void bfmeSlotNB70();
	virtual void bfmeSlotNB71();
	virtual void bfmeSlotNB72();
	virtual void bfmeSlotNB73();
	virtual void bfmeSlotNB74();
	virtual void bfmeSlotNB75();
	virtual void bfmeSlotNB76();
	virtual void bfmeSlotNB77();
	virtual void bfmeSlotNB78();
	virtual void bfmeSlotNB79();
	virtual void bfmeSlotNB80();
	virtual void bfmeSlotNB81();
	virtual void bfmeSlotNB82();
	virtual void bfmeSlotNB83();
	virtual void bfmeSlotNB84();
	virtual void bfmeSlotNB85();
	virtual void bfmeSlotNB86();
	virtual void bfmeSlotNB87();
	virtual void bfmeSlotNB88();
	virtual void bfmeSlotNB89();
	virtual void bfmeSlotNB90();
	virtual void bfmeSlotNB91();
	virtual void bfmeSlotNB92();
	virtual void bfmeSlotNB93();
	virtual void bfmeSlotNB94();
	virtual void bfmeSlotNB95();
	virtual void bfmeSlotNB96();
	virtual void bfmeSlotNB97();
	virtual void bfmeSlotNB98();
	virtual void bfmeSlotNB99();
	virtual void bfmeVirtNB(int f);
};

class BfmeThingNB
{
public:
	void bfmeGoNB(char a);
	char m_bfmePad[8];
	BfmeSubNB *m_bfmeSub;
};

void BfmeThingNB::bfmeGoNB(char a)
{
	BfmeSubNB *s = m_bfmeSub;
	if (s)
		s->bfmeVirtNB(a == 0);
}

struct BfmeArgNC
{
	char m_bfmePad[0xc];
	void *m_bfmeKey;
};

class BfmeGlobNC
{
public:
	void bfmeTailNC(int r);
};

extern BfmeGlobNC *g_bfmeGlobNC;
int __stdcall bfmeFindNC(void *k);

void __stdcall bfmeGoNC(BfmeArgNC *a)
{
	void *k = a->m_bfmeKey;
	int r = bfmeFindNC(k);
	if (r != -1)
		g_bfmeGlobNC->bfmeTailNC(r);
}

struct BfmeObjND
{
	char m_bfmePad[0x270];
	unsigned char m_bfmeByte;
};

struct BfmeSubND
{
	char m_bfmePad[0x120e0];
	BfmeObjND *m_bfmeObj;
};

class BfmeThingND
{
public:
	int bfmeGoND();
	char m_bfmePad[8];
	BfmeSubND *m_bfmeSub;
};

int BfmeThingND::bfmeGoND()
{
	BfmeSubND *s = m_bfmeSub;
	if (s) {
		BfmeObjND *o = s->m_bfmeObj;
		unsigned int v;
		if (o)
			v = o->m_bfmeByte;
		else
			v = 0;
		return (unsigned char)v;
	}
	return 0;
}

class BfmeSubNF
{
public:
	void bfmeOneNF(void *a);
};

class BfmeGlobNF
{
public:
	void bfmeTwoNF(void *a, int f);
};

extern BfmeGlobNF *g_bfmeGlobNF;

class BfmeThingNF
{
public:
	void bfmeGoNF(void *a);
	char m_bfmePad[8];
	BfmeSubNF *m_bfmeSub;
};

void BfmeThingNF::bfmeGoNF(void *a)
{
	BfmeSubNF *s = m_bfmeSub;
	if (s) {
		s->bfmeOneNF(a);
		g_bfmeGlobNF->bfmeTwoNF(a, 2);
	}
}

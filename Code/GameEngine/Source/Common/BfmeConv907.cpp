// Open-BFME5 conversions.

extern char g_bfmeVftAQB[];
extern char g_bfmeVftBQB[];
extern int g_bfmeCountQB;

struct BfmeSubQB
{
	int m_bfmeFirst;
};

class BfmeThingQB
{
public:
	void bfmeGoQB();
	void bfmeTailQB();
	char *m_bfmeVfA;
	char m_bfmePad[8];
	char *m_bfmeVfB;
	char m_bfmePad2[0x26c];
	BfmeSubQB *m_bfmeSub;
};

void BfmeThingQB::bfmeGoQB()
{
	m_bfmeVfA = g_bfmeVftAQB;
	m_bfmeVfB = g_bfmeVftBQB;
	--g_bfmeCountQB;
	BfmeSubQB *s = m_bfmeSub;
	if (s)
		s->m_bfmeFirst = 0;
	bfmeTailQB();
}

class BfmeGlobQC
{
public:
	virtual void bfmeSlotQC00();
	virtual void bfmeSlotQC01();
	virtual void bfmeSlotQC02();
	virtual void bfmeSlotQC03();
	virtual void bfmeSlotQC04();
	virtual void bfmeSlotQC05();
	virtual void bfmeSlotQC06();
	virtual void bfmeSlotQC07();
	virtual void bfmeSlotQC08();
	virtual void bfmeSlotQC09();
	virtual void bfmeSlotQC10();
	virtual void bfmeSlotQC11();
	virtual void bfmeSlotQC12();
	virtual void bfmeSlotQC13();
	virtual void bfmeSlotQC14();
	virtual void bfmeSlotQC15();
	virtual void bfmeSlotQC16();
	virtual void bfmeSlotQC17();
	virtual void bfmeOneQC(void *a);
	virtual void bfmeTwoQC(int f);
};

extern BfmeGlobQC *g_bfmeGlobQC;

void __stdcall bfmeGoQC(void *a)
{
	g_bfmeGlobQC->bfmeOneQC(a);
	g_bfmeGlobQC->bfmeTwoQC(8);
}

class BfmeSubQE
{
public:
	void bfmeTwoQE();
};

class BfmeGlobQE
{
public:
	void bfmeThreeQE();
};

extern BfmeGlobQE *g_bfmeGlobQE;

class BfmeThingQE
{
public:
	void bfmeGoQE();
	void bfmeOneQE();
	char m_bfmePad[0x10];
	BfmeSubQE *m_bfmeSub;
};

void BfmeThingQE::bfmeGoQE()
{
	bfmeOneQE();
	if (m_bfmeSub)
		m_bfmeSub->bfmeTwoQE();
	if (g_bfmeGlobQE)
		g_bfmeGlobQE->bfmeThreeQE();
}

class BfmeObjQF
{
public:
	virtual void bfmeSlotQF00();
	virtual void bfmeSlotQF01();
	virtual void bfmeSlotQF02();
	virtual void bfmeSlotQF03();
	virtual void bfmeSlotQF04();
	virtual void bfmeSlotQF05();
	virtual void bfmeSlotQF06();
	virtual void bfmeSlotQF07();
	virtual void bfmeSlotQF08();
	virtual void bfmeSlotQF09();
	virtual void bfmeSlotQF10();
	virtual void bfmeSlotQF11();
	virtual void bfmeSlotQF12();
	virtual void bfmeSlotQF13();
	virtual void bfmeSlotQF14();
	virtual void bfmeSlotQF15();
	virtual void bfmeSlotQF16();
	virtual void bfmeSlotQF17();
	virtual void bfmeSlotQF18();
	virtual void bfmeSlotQF19();
	virtual void bfmeSlotQF20();
	virtual void bfmeSlotQF21();
	virtual void bfmeSlotQF22();
	virtual void bfmeSlotQF23();
	virtual void bfmeSlotQF24();
	virtual void bfmeSlotQF25();
	virtual void bfmeSlotQF26();
	virtual void bfmeSlotQF27();
	virtual void bfmeSlotQF28();
	virtual void bfmeSlotQF29();
	virtual void bfmeSlotQF30();
	virtual void bfmeSlotQF31();
	virtual void bfmeSlotQF32();
	virtual void bfmeSlotQF33();
	virtual void bfmeSlotQF34();
	virtual void bfmeSlotQF35();
	virtual void bfmeSlotQF36();
	virtual void bfmeSlotQF37();
	virtual void bfmeSlotQF38();
	virtual void bfmeSlotQF39();
	virtual void bfmeSlotQF40();
	virtual void bfmeSlotQF41();
	virtual void bfmeSlotQF42();
	virtual void bfmeSlotQF43();
	virtual void bfmeVirtQF(int a, int b, int c);
};

class BfmeThingQF
{
public:
	void bfmeGoQF(BfmeObjQF *a);
	char m_bfmePad[0xdc];
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeThingQF::bfmeGoQF(BfmeObjQF *a)
{
	if (a)
		a->bfmeVirtQF(m_bfmeA, m_bfmeB, 0);
}


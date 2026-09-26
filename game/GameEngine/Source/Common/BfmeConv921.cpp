// Open-BFME5 conversions.

class BfmeTail921A
{
public:
	void bfmeTail921A(void *a, void *b);
};

struct BfmeSub921A
{
	char m_bfmePad[0x20];
	BfmeTail921A m_bfmeTail;
};

struct BfmeObj921A
{
	char m_bfmePad[0x204];
	BfmeSub921A *m_bfmeSub;
};

class BfmeThing921A
{
public:
	void bfmeGo921A(void *a, void *b);
};

void BfmeThing921A::bfmeGo921A(void *a, void *b)
{
	BfmeObj921A *o = *(BfmeObj921A **)((char *)this - 0xdc);
	BfmeSub921A *s = o->m_bfmeSub;
	if (s)
		s->m_bfmeTail.bfmeTail921A(a, b);
}

class BfmeC921D
{
public:
	virtual void bfmeSlot921D00();
	virtual void bfmeSlot921D01();
	virtual void bfmeSlot921D02();
	virtual void bfmeSlot921D03();
	virtual void bfmeSlot921D04();
	virtual void bfmeSlot921D05();
	virtual void bfmeSlot921D06();
	virtual void bfmeSlot921D07();
	virtual void bfmeSlot921D08();
	virtual char bfmeVirt921D();
};

struct BfmeB921D
{
	char m_bfmePad[0x1fc];
	BfmeC921D *m_bfmeC;
};

struct BfmeA921D
{
	char m_bfmePad[0x214];
	BfmeB921D *m_bfmeB;
};

class BfmeThing921D
{
public:
	char bfmeGo921D();
};

char BfmeThing921D::bfmeGo921D()
{
	BfmeA921D *a = *(BfmeA921D **)((char *)this - 0x18);
	BfmeB921D *b = a->m_bfmeB;
	if (b) {
		BfmeC921D *c = b->m_bfmeC;
		if (c)
			return c->bfmeVirt921D();
	}
	return 1;
}

class BfmeGlob921E
{
public:
	virtual void bfmeSlot921E00();
	virtual void bfmeSlot921E01();
	virtual void bfmeSlot921E02();
	virtual void bfmeSlot921E03();
	virtual void bfmeSlot921E04();
	virtual void bfmeSlot921E05();
	virtual void bfmeSlot921E06();
	virtual void bfmeSlot921E07();
	virtual void bfmeSlot921E08();
	virtual void bfmeSlot921E09();
	virtual void bfmeSlot921E10();
	virtual void bfmeSlot921E11();
	virtual void bfmeSlot921E12();
	virtual void bfmeSlot921E13();
	virtual void bfmeSlot921E14();
	virtual void bfmeSlot921E15();
	virtual void bfmeSlot921E16();
	virtual void bfmeSlot921E17();
	virtual void bfmeSlot921E18();
	virtual void bfmeSlot921E19();
	virtual void bfmeSlot921E20();
	virtual void bfmeSlot921E21();
	virtual void bfmeSlot921E22();
	virtual void bfmeSlot921E23();
	virtual void bfmeSlot921E24();
	virtual void bfmeSlot921E25();
	virtual void bfmeSlot921E26();
	virtual void bfmeSlot921E27();
	virtual void bfmeSlot921E28();
	virtual void bfmeSlot921E29();
	virtual void bfmeSlot921E30();
	virtual void bfmeSlot921E31();
	virtual void bfmeSlot921E32();
	virtual void bfmeSlot921E33();
	virtual void bfmeSlot921E34();
	virtual void bfmeSlot921E35();
	virtual void bfmeSlot921E36();
	virtual void bfmeVirt921E(void *a);
};

extern BfmeGlob921E *g_bfme921GlobE;

void __stdcall bfmeGo921E(void *a)
{
	BfmeGlob921E *g = g_bfme921GlobE;
	if (!g)
		return;
	if (!a)
		return;
	g->bfmeVirt921E(a);
}

struct BfmeA921G
{
	char m_bfmePad[0x270];
	char m_bfmeFlag;
};

class BfmeThing921G
{
public:
	void bfmeGo921G();
	void bfmeOne921G();
	char m_bfmePad[0x1ed];
	char m_bfmeOut;
};

void BfmeThing921G::bfmeGo921G()
{
	bfmeOne921G();
	BfmeA921G *a = *(BfmeA921G **)((char *)this - 0x30);
	m_bfmeOut = (a->m_bfmeFlag == 0);
}

// Open-BFME5 conversions.

struct BfmeSub923A
{
	int m_bfmeVal;
};

class BfmeGlob923A
{
public:
	void bfmeTail923A(BfmeSub923A *s, void *a);
};

extern BfmeGlob923A *g_bfme923GlobA;

class BfmeThing923A
{
public:
	void bfmeGo923A(void *a, void *b);
	char m_bfmePad[0xb4];
	BfmeSub923A m_bfmeSub;
};

void BfmeThing923A::bfmeGo923A(void *a, void *b)
{
	g_bfme923GlobA->bfmeTail923A(&m_bfmeSub, a);
}

class BfmeSub923B
{
public:
	void bfmeTail923B(char v);
};

class BfmeThing923B
{
public:
	void bfmeGo923B(char v);
	char m_bfmePad[0x3b1];
	char m_bfmeFlag;
	char m_bfmePad2[0xa];
	BfmeSub923B *m_bfmeSub;
};

void BfmeThing923B::bfmeGo923B(char v)
{
	m_bfmeFlag = v;
	BfmeSub923B *s = m_bfmeSub;
	if (s)
		s->bfmeTail923B(v);
}

class BfmeObj923D
{
public:
	virtual void bfmeSlot923D00();
	virtual void bfmeSlot923D01();
	virtual void bfmeSlot923D02();
	virtual void bfmeSlot923D03();
	virtual void bfmeSlot923D04();
	virtual void bfmeSlot923D05();
	virtual void bfmeSlot923D06();
	virtual void bfmeSlot923D07();
	virtual void bfmeSlot923D08();
	virtual void bfmeSlot923D09();
	virtual void bfmeSlot923D10();
	virtual void bfmeSlot923D11();
	virtual void bfmeSlot923D12();
	virtual void bfmeSlot923D13();
	virtual void bfmeSlot923D14();
	virtual void bfmeSlot923D15();
	virtual void bfmeSlot923D16();
	virtual void bfmeSlot923D17();
	virtual void bfmeSlot923D18();
	virtual void bfmeSlot923D19();
	virtual void bfmeSlot923D20();
	virtual void bfmeSlot923D21();
	virtual void bfmeSlot923D22();
	virtual void bfmeSlot923D23();
	virtual void bfmeSlot923D24();
	virtual void bfmeSlot923D25();
	virtual void bfmeSlot923D26();
	virtual void bfmeSlot923D27();
	virtual void bfmeSlot923D28();
	virtual void bfmeSlot923D29();
	virtual void bfmeSlot923D30();
	virtual void bfmeSlot923D31();
	virtual void bfmeSlot923D32();
	virtual void bfmeSlot923D33();
	virtual void bfmeSlot923D34();
	virtual void bfmeSlot923D35();
	virtual void bfmeSlot923D36();
	virtual void bfmeSlot923D37();
	virtual void bfmeSlot923D38();
	virtual void bfmeSlot923D39();
	virtual void bfmeSlot923D40();
	virtual void bfmeSlot923D41();
	virtual void bfmeSlot923D42();
	virtual void bfmeSlot923D43();
	virtual void bfmeVirt923D(void *b, int f, int g);
};

void __stdcall bfmeGo923D(BfmeObj923D *a, void *b)
{
	if (a && b)
		a->bfmeVirt923D(b, 0, 2);
}

class BfmeElem923E
{
public:
	void bfmeTail923E(void *t, void *b);
	char m_bfmePad[0x18];
};

class BfmeThing923E
{
public:
	void bfmeGo923E(int i, void *b);
	char m_bfmePad[0x64];
	BfmeElem923E m_bfmeArr[3];
};

void BfmeThing923E::bfmeGo923E(int i, void *b)
{
	if (i < 3)
		m_bfmeArr[i].bfmeTail923E(this, b);
}

void __stdcall bfmeFree923F(void *p, int f);

class BfmeThing923F
{
public:
	void bfmeGo923F();
	char m_bfmePad[8];
	void *m_bfmeP;
};

void BfmeThing923F::bfmeGo923F()
{
	void *p = m_bfmeP;
	if (p) {
		bfmeFree923F(p, 0);
		m_bfmeP = 0;
	}
}

struct BfmeObj923G
{
	char m_bfmePad[0xa8];
	char m_bfmeFlag;
};

BfmeObj923G *__stdcall bfmeFind923G(void *a);

char __stdcall bfmeGo923G(void *a, void *b)
{
	BfmeObj923G *o = bfmeFind923G(a);
	if (!o)
		return 0;
	o->m_bfmeFlag = 1;
	return 1;
}

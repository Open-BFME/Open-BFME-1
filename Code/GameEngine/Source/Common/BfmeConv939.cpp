// Open-BFME5 conversions.

class BfmeGlob939A
{
public:
	virtual void bfmeSlot939A00();
	virtual void bfmeSlot939A01();
	virtual void bfmeSlot939A02();
	virtual void bfmeSlot939A03();
	virtual void bfmeTail939A();
};

extern BfmeGlob939A *g_bfme939GlobA;
void bfmeCall939A(void);

void bfmeGo939A(void)
{
	bfmeCall939A();
	g_bfme939GlobA->bfmeTail939A();
}

struct BfmeElem939B
{
	int m_bfmeA;
	int m_bfmeB;
};

class BfmeThing939B
{
public:
	void bfmeGo939B(int i);
	void bfmeTail939B(BfmeElem939B *e);
	char m_bfmePad[0x10];
	BfmeElem939B m_bfmeArr[1];
};

void BfmeThing939B::bfmeGo939B(int i)
{
	bfmeTail939B(&m_bfmeArr[i]);
}

class BfmeGlob939C
{
public:
	virtual void bfmeSlot939C00();
	virtual void bfmeSlot939C01();
	virtual void bfmeSlot939C02();
	virtual void bfmeSlot939C03();
	virtual void bfmeSlot939C04();
	virtual void bfmeSlot939C05();
	virtual void bfmeSlot939C06();
	virtual void bfmeSlot939C07();
	virtual void bfmeSlot939C08();
	virtual void bfmeSlot939C09();
	virtual void bfmeSlot939C10();
	virtual void bfmeSlot939C11();
	virtual void bfmeSlot939C12();
	virtual void bfmeSlot939C13();
	virtual void bfmeSlot939C14();
	virtual void bfmeSlot939C15();
	virtual void bfmeSlot939C16();
	virtual void bfmeSlot939C17();
	virtual void bfmeSlot939C18();
	virtual void bfmeSlot939C19();
	virtual void bfmeSlot939C20();
	virtual void bfmeSlot939C21();
	virtual void bfmeSlot939C22();
	virtual void bfmeSlot939C23();
	virtual void bfmeSlot939C24();
	virtual void bfmeSlot939C25();
	virtual void bfmeSlot939C26();
	virtual void bfmeSlot939C27();
	virtual void bfmeSlot939C28();
	virtual void bfmeSlot939C29();
	virtual void bfmeSlot939C30();
	virtual int bfmeVirt939C(int f);
};

extern BfmeGlob939C *g_bfme939GlobC;

int bfmeGo939C(void)
{
	int r = g_bfme939GlobC->bfmeVirt939C(0);
	return r == 0;
}

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

extern BfmeGlob939D *g_bfme939GlobD;

int __stdcall bfmeGo939D(char v)
{
	char r = g_bfme939GlobD->bfmeCall939D();
	return (char)(r - v) == 0;
}

extern char g_bfme939Str[];

class BfmeSub939E
{
public:
	void bfmeCall939E(int *out, char *s);
};

void bfmeGo939E(BfmeSub939E *a)
{
	int tmp;
	a->bfmeCall939E(&tmp, g_bfme939Str);
}

class BfmeSub939G
{
public:
	void bfmeCall939G();
	void *m_bfmeP;
};

class BfmeThing939G
{
public:
	void bfmeGo939G(void *a);
	char m_bfmePad[8];
	BfmeSub939G m_bfmeSub;
};

void BfmeThing939G::bfmeGo939G(void *a)
{
	BfmeSub939G *s = &m_bfmeSub;
	if (!a && s->m_bfmeP)
		s->bfmeCall939G();
}


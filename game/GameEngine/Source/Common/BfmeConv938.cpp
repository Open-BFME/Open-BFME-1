// Open-BFME5 conversions.

class BfmeGlob938A
{
public:
	void bfmeTail938A(int f);
};

extern BfmeGlob938A *g_bfme938GlobA;

void __stdcall bfmeGo938A(void *a)
{
	g_bfme938GlobA->bfmeTail938A(0);
}

void bfmeCall938C(int a, int b, int c);

void __stdcall bfmeGo938C(void *a)
{
	bfmeCall938C(3, 4, 0);
}

extern char g_bfme938StrD[];
extern char g_bfme938FnD[];
void bfmeCall938D(char *a, char *b);

void bfmeGo938D(void)
{
	bfmeCall938D(g_bfme938StrD, g_bfme938FnD);
}

class BfmeThing938F
{
public:
	virtual void bfmeSlot938F00();
	virtual void bfmeSlot938F01();
	virtual void bfmeVirt938F(int v);
	void bfmeGo938F(void *a);
	char m_bfmePad[4];
	char m_bfmeA;
	char m_bfmeB;
	char m_bfmePad2[6];
	int m_bfmeVal;
	char m_bfmePad3[0x10];
	char m_bfmeC;
};

void BfmeThing938F::bfmeGo938F(void *a)
{
	int v = m_bfmeVal;
	m_bfmeA = 0;
	m_bfmeC = 0;
	m_bfmeB = 1;
	bfmeVirt938F(v);
}

class BfmeThing938H
{
public:
	virtual void bfmeVirt938H(int f);
	void bfmeCall938H();
};

void __fastcall bfmeGo938H(BfmeThing938H *t)
{
	t->bfmeCall938H();
	if (t)
		t->bfmeVirt938H(1);
}

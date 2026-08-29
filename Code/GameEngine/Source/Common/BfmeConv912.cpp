// Open-BFME5 conversions.

extern void *g_bfme912Glob;

__declspec(dllimport) void __stdcall bfmeFree912B(void *p);

class Gen_007f0300
{
public:
	void m();
};

extern char g_bfme912Str[];
extern void *g_bfme912A;
extern Gen_007f0300 g_bfme912B;

void bfmeGo912B(void)
{
	void *p = g_bfme912A;
	*(char **)&g_bfme912B = g_bfme912Str;
	if (p)
		bfmeFree912B(p);
	g_bfme912B.m();
}

struct BfmeNode912C
{
	char m_bfmePad[0xc];
	BfmeNode912C *m_bfmeNext;
};

class BfmeThing912C
{
public:
	void bfmeGo912C();
	void bfmeDo912C(BfmeNode912C *n);
	char m_bfmePad[0xe4];
	BfmeNode912C *m_bfmeHead;
};

void BfmeThing912C::bfmeGo912C()
{
	BfmeNode912C *n = m_bfmeHead;
	while (n) {
		bfmeDo912C(n);
		n = n->m_bfmeNext;
	}
}

void *__cdecl operator new[](unsigned int n);

class BfmeThing912F
{
public:
	virtual void bfmeSlot912F0();
	virtual void bfmeSlot912F1();
	virtual void bfmeDone912F();
	void *bfmeGo912F();
	char m_bfmePad[0x10];
	void *m_bfmeP;
};

void *BfmeThing912F::bfmeGo912F()
{
	void *s = m_bfmeP;
	if (!s)
		return operator new[](1);
	m_bfmeP = 0;
	bfmeDone912F();
	return s;
}

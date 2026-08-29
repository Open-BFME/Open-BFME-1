// Open-BFME5 conversions.

extern "C" void bfmeFnA1033(void);
extern "C" void bfmeFnB1033(void);
void bfmeReg1033(void (*a)(void), void (*b)(void));

class BfmeB1033
{
public:
	void bfmeGo1033B(int unused);

	char m_bfmePad[0x400];
	int m_bfmeKind;
};

void BfmeB1033::bfmeGo1033B(int unused)
{
	if (m_bfmeKind == 0xb)
		bfmeReg1033(bfmeFnA1033, bfmeFnB1033);
}

extern "C" void *bfmeVft1033D[];
__declspec(dllimport) void __stdcall bfmeClose1033(int h);

class BfmeD1033
{
public:
	void bfmeGo1033D(void);
	void bfmeBaseDtor1033(void);

	void *m_bfmeVfptr;
	int m_bfmeH;
};

void BfmeD1033::bfmeGo1033D(void)
{
	m_bfmeVfptr = bfmeVft1033D;

	if (m_bfmeH != 0)
		bfmeClose1033(m_bfmeH);

	bfmeBaseDtor1033();
}

class BfmeF1033;

class BfmeSub1033
{
public:
	int bfmeTry1033(BfmeF1033 *o);
	void bfmeFail1033(void);
};

struct BfmeG1033
{
	char m_bfmePad[0x2c];
	BfmeSub1033 m_bfmeSub;
};

class BfmeF1033
{
public:
	void bfmeGo1033F(BfmeG1033 *g);
};

void BfmeF1033::bfmeGo1033F(BfmeG1033 *g)
{
	if (g->m_bfmeSub.bfmeTry1033(this) == 0)
		g->m_bfmeSub.bfmeFail1033();
}

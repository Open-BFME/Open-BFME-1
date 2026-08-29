// Open-BFME5 conversions.

class BfmeQ1026
{
public:
	char bfmeCheck1026(int k, int a, int b);
};

extern BfmeQ1026 *g_bfmeQ1026;

class BfmeLst1026
{
public:
	void bfmeAdd1026(int a, int b);
};

class BfmeA1026
{
public:
	void bfmeGo1026A(int a, int b);

	char m_bfmePad[8];
	int m_bfmeKey;
	char m_bfmePad2[0x14];
	BfmeLst1026 m_bfmeList;
};

void BfmeA1026::bfmeGo1026A(int a, int b)
{
	if (g_bfmeQ1026->bfmeCheck1026(m_bfmeKey, a, b) != 0)
		m_bfmeList.bfmeAdd1026(a, b);
}

class BfmeX1026
{
public:
	void bfmeSet1026(int k, char on);
};

class BfmeU1026
{
public:
	virtual void bfmeVU01026();
	virtual void bfmeVU11026();
	virtual void bfmeVU21026();
	virtual void bfmeVU31026();
	virtual void bfmeVU41026();
	virtual void bfmeVU51026();
	virtual void bfmeVU61026();
	virtual void bfmeVU71026();
	virtual void bfmeVU81026();
	virtual void bfmeVU91026();
	virtual void bfmeVU101026();
	virtual void bfmeVU111026();
	virtual void bfmeVU121026();
	virtual void bfmeVU131026();
	virtual void bfmeVU141026();
	virtual void bfmeVU151026();
	virtual void bfmeVU161026();
	virtual void bfmeVU171026();
	virtual void bfmeVU181026();
	virtual void bfmeVU191026();
	virtual void bfmeVU201026();
	virtual void bfmeVU211026();
	virtual void bfmeVU221026();
	virtual void bfmeVU231026();
	virtual void bfmeVU241026();
	virtual void bfmeVU251026();
	virtual BfmeX1026 *bfmeFind1026(int a);
};

extern BfmeU1026 *g_bfmeU1026;

void __stdcall bfmeGo1026B(int a, char b)
{
	BfmeX1026 *x = g_bfmeU1026->bfmeFind1026(a);

	if (x != 0)
		x->bfmeSet1026(8, (char)(b == 0));
}

class BfmeW1026
{
public:
	void bfmeUse1026(int n);

	char m_bfmePad[0x508];
	void (__cdecl *m_bfmeFn)(int);
	char m_bfmeFlag;
};

extern BfmeW1026 *g_bfmeW1026;

class BfmeReg1026
{
public:
	virtual void bfmeVR01026();
	virtual void bfmeVR11026();
	virtual void bfmeVR21026();
	virtual void bfmeVR31026();
	virtual void bfmeVR41026();
	virtual void bfmeVR51026();
	virtual void bfmeVR61026();
	virtual void bfmeVR71026();
	virtual void bfmeVR81026();
	virtual void bfmeVR91026();
	virtual void bfmeDrop1026(int h);
};

extern BfmeReg1026 *g_bfmeReg1026;
void bfmeFree1026(void *p);

class BfmeD1026
{
public:
	void *bfmeGo1026D(unsigned int f);

	char m_bfmePad[4];
	int m_bfmeH;
};

void *BfmeD1026::bfmeGo1026D(unsigned int f)
{
	if (m_bfmeH != 0) {
		g_bfmeReg1026->bfmeDrop1026(m_bfmeH);
		m_bfmeH = 0;
	}

	if ((f & 1) != 0)
		bfmeFree1026(this);

	return this;
}

extern char g_bfmeKey1026[];
__declspec(dllimport) int __cdecl bfmeCmp1026(char *a, char *b, int n);

void bfmeGo1026E(char *s)
{
	if (s == 0)
		return;

	if (bfmeCmp1026(s, g_bfmeKey1026, 7) != 0)
		return;

	g_bfmeW1026->bfmeUse1026(s[7] - 0x31);
}

class BfmeSrc1026
{
public:
	int bfmeGet1026(void);
};

class BfmeTab1026
{
public:
	char bfmeHas1026(int h, int v);
};

struct BfmeOwner1026
{
	char m_bfmePad[8];
	BfmeTab1026 m_bfmeTab;
};

class BfmeStore1026
{
public:
	void bfmeDo1026(int h);
};

extern BfmeStore1026 *g_bfmeStore1026;

class BfmeF1026
{
public:
	void bfmeGo1026F(int h, int u1, int u2);
};

void BfmeF1026::bfmeGo1026F(int h, int u1, int u2)
{
	if (h == 0)
		return;

	BfmeOwner1026 *o = *(BfmeOwner1026 **)((char *)this - 0xc);
	BfmeSrc1026 *p = *(BfmeSrc1026 **)((char *)this - 8);

	if (o->m_bfmeTab.bfmeHas1026(h, p->bfmeGet1026()) != 0)
		g_bfmeStore1026->bfmeDo1026(h);
}

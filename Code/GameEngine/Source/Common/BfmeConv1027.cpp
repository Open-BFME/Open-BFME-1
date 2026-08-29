// Open-BFME5 conversions.

class BfmeQ1027
{
public:
	void bfmeSet1027(int a, int b);
	void bfmeMark1027(int a);
};

class BfmeY1027
{
public:
	char m_bfmePad[0x20];
	BfmeQ1027 m_bfmeQ;
};

class BfmeX1027
{
public:
	void bfmeStop1027(void);
	void bfmePause1027(int n);

	char m_bfmePad[0x204];
	BfmeY1027 *m_bfmeOwner;
};

class BfmeU1027
{
public:
	virtual void bfmeVU01027();
	virtual void bfmeVU11027();
	virtual void bfmeVU21027();
	virtual void bfmeVU31027();
	virtual void bfmeVU41027();
	virtual void bfmeVU51027();
	virtual void bfmeVU61027();
	virtual void bfmeVU71027();
	virtual void bfmeVU81027();
	virtual void bfmeVU91027();
	virtual void bfmeVU101027();
	virtual void bfmeVU111027();
	virtual void bfmeVU121027();
	virtual void bfmeVU131027();
	virtual void bfmeVU141027();
	virtual void bfmeVU151027();
	virtual void bfmeVU161027();
	virtual void bfmeVU171027();
	virtual void bfmeVU181027();
	virtual void bfmeVU191027();
	virtual void bfmeVU201027();
	virtual void bfmeVU211027();
	virtual void bfmeVU221027();
	virtual void bfmeVU231027();
	virtual void bfmeVU241027();
	virtual void bfmeVU251027();
	virtual BfmeX1027 *bfmeFind1027(int a);
};

extern BfmeU1027 *g_bfmeU1027;

void __stdcall bfmeGo1027A(int a)
{
	BfmeX1027 *x = g_bfmeU1027->bfmeFind1027(a);

	if (x == 0)
		return;

	BfmeY1027 *y = x->m_bfmeOwner;

	if (y == 0)
		return;

	x->bfmeStop1027();
	y->m_bfmeQ.bfmeSet1027(0, 1);
}

void __stdcall bfmeGo1027B(int a)
{
	BfmeX1027 *x = g_bfmeU1027->bfmeFind1027(a);

	if (x == 0)
		return;

	BfmeY1027 *y = x->m_bfmeOwner;

	if (y == 0)
		return;

	x->bfmePause1027(1);
	y->m_bfmeQ.bfmeMark1027(1);
}

class BfmeVal1027
{
public:
	float bfmeVal1027(void);
};

struct BfmeZ1027
{
	char m_bfmePad[4];
	BfmeVal1027 m_bfmeSub;
	char m_bfmePad2[0x17];
	char m_bfmeFlag;
};

struct BfmeS1027
{
	char m_bfmePad[0x3c];
	int m_bfmeBase;
};

extern BfmeS1027 *g_bfmeS1027;

void __stdcall bfmeGo1027D(BfmeZ1027 *p, int *out)
{
	if (p->m_bfmeFlag != 0) {
		*out = -1;
		return;
	}

	int base = g_bfmeS1027->m_bfmeBase;

	*out = base + (int)p->m_bfmeSub.bfmeVal1027();
}

class BfmeW1027
{
public:
	void bfmeSel1027(int n);
};

extern BfmeW1027 *g_bfmeW1027;
extern char g_bfmeKey1027[];
__declspec(dllimport) int __cdecl bfmeCmp1027(char *a, char *b, int n);
__declspec(dllimport) int __cdecl bfmeAtoi1027(char *s);

void bfmeGo1027E(char *s)
{
	if (bfmeCmp1027(s, g_bfmeKey1027, 4) != 0)
		return;

	g_bfmeW1027->bfmeSel1027(bfmeAtoi1027(s + 4) - 1);
}


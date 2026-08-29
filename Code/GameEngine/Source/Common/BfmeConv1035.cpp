// Open-BFME5 conversions.

class BfmeA1035
{
public:
	void bfmeGo1035A(char f);
	void bfmeStep1035(char f);
	void bfmeMore1035(void);
};

void BfmeA1035::bfmeGo1035A(char f)
{
	bfmeStep1035(f);

	if (f != 0)
		bfmeMore1035();
}

class BfmeSubB1035
{
public:
	void bfmeClear1035(void);
};

class BfmeRef1035
{
public:
	virtual void bfmeV01035();
	virtual void bfmeRelease1035();
};

class BfmeB1035
{
public:
	void bfmeGo1035B(void);

	char m_bfmePad[8];
	BfmeSubB1035 m_bfmeSub;
	char m_bfmePad2[0xc];
	BfmeRef1035 *m_bfmeP;
};

void BfmeB1035::bfmeGo1035B(void)
{
	m_bfmeSub.bfmeClear1035();

	if (m_bfmeP != 0)
		m_bfmeP->bfmeRelease1035();

	m_bfmeP = 0;
}

class BfmeX1035;

struct BfmeT1035
{
	void bfmeUse1035(BfmeX1035 *p, int b);

	int m_bfmeV;
};

void __stdcall bfmeGo1035C(BfmeX1035 *p, int b)
{
	if (p == 0)
		return;

	BfmeT1035 t;

	t.m_bfmeV = 0;
	t.bfmeUse1035(p, b);
}

class BfmeSubE1035
{
public:
	int bfmeSize1035(void);
};

class BfmeE1035
{
public:
	int bfmeGo1035E(void);

	char m_bfmePad[8];
	BfmeSubE1035 m_bfmeSub;
	char m_bfmePad2[0x13];
	int m_bfme1c;
	int m_bfme20;
	char m_bfmePad3[4];
	int m_bfme28;
};

int BfmeE1035::bfmeGo1035E(void)
{
	int n = m_bfmeSub.bfmeSize1035() + (m_bfme1c & 0xff);

	if (m_bfme20 != 0)
		n += m_bfme28;

	return n;
}

__declspec(dllimport) void __cdecl bfmeFree1035(void *p);

class BfmeF1035
{
public:
	void bfmeGo1035F(void);

	char m_bfmePad[0x20];
	void *m_bfmeP;
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeF1035::bfmeGo1035F(void)
{
	int z = 0;

	if (m_bfmeP != 0) {
		bfmeFree1035(m_bfmeP);
		m_bfmeP = (void *)z;
	}

	m_bfmeA = z;
	m_bfmeB = z;
}

class BfmeG1035;

extern char g_bfmeCh1035;
extern char g_bfmeLit1035[];
void bfmeFix1035(char **slot, char *lit, BfmeG1035 *o);

class BfmeG1035
{
public:
	char *bfmeGo1035G(void);

	char m_bfmePad[0x18];
	char *m_bfmeName;
};

char *BfmeG1035::bfmeGo1035G(void)
{
	if (*m_bfmeName == g_bfmeCh1035)
		bfmeFix1035(&m_bfmeName, g_bfmeLit1035, this);

	return m_bfmeName;
}

// Open-BFME5 conversions.

class BfmeErr1042
{
public:
	BfmeErr1042();

	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1042[];
__declspec(noreturn) void __stdcall bfmeFatal1042(BfmeErr1042 *e, char *m);

class BfmeB1042
{
public:
	virtual void bfmeV01042();
	virtual void bfmeDo1042(int a);
	virtual void bfmeRun1042();
};

class BfmeB1042N
{
public:
	virtual void bfmeV01042N();
	virtual void bfmeDoN1042();
};

class BfmeA1042N
{
public:
	void bfmeGo1042D(void);

	BfmeB1042N *m_bfmeP;
};

void BfmeA1042N::bfmeGo1042D(void)
{
	BfmeB1042N *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1042 e;

		bfmeFatal1042(&e, g_bfmeMsg1042);
	}

	p->bfmeDoN1042();
}

class BfmeA1042
{
public:
	void bfmeGo1042A(int a);
	void bfmeGo1042B(int a);
	void bfmeGo1042C(int a);

	BfmeB1042 *m_bfmeP;
};

void BfmeA1042::bfmeGo1042A(int a)
{
	BfmeB1042 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1042 e;

		bfmeFatal1042(&e, g_bfmeMsg1042);
	}

	p->bfmeDo1042(a);
}

void BfmeA1042::bfmeGo1042B(int a)
{
	BfmeB1042 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1042 e;

		bfmeFatal1042(&e, g_bfmeMsg1042);
	}

	p->bfmeDo1042(a);
}

void BfmeA1042::bfmeGo1042C(int a)
{
	BfmeB1042 *p = m_bfmeP;

	if (p == 0) {
		BfmeErr1042 e;

		bfmeFatal1042(&e, g_bfmeMsg1042);
	}

	p->bfmeDo1042(a);
}

struct BfmeR1042
{
	char *m_bfmeName;
};

class BfmeSub1042
{
public:
	void bfmeSet1042(char *t, int a, int b);
};

extern char g_bfmeLit1042[];

class BfmeC1042
{
public:
	void bfmeGo1042E(BfmeR1042 *p);

	char m_bfmePad[4];
	BfmeSub1042 m_bfmeSub;
	char m_bfmePad2[0xd7];
	char m_bfmeFlag;
};

void BfmeC1042::bfmeGo1042E(BfmeR1042 *p)
{
	char *t;

	if (p->m_bfmeName != 0)
		t = p->m_bfmeName + 8;
	else
		t = g_bfmeLit1042;

	m_bfmeSub.bfmeSet1042(t, 0, 0);
	m_bfmeFlag = 1;
}


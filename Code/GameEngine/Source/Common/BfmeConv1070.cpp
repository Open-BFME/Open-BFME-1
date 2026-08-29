// Open-BFME5 conversions.

class BfmeX1070;

class BfmeR1070
{
public:
	void bfmeRun1070(BfmeX1070 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1070 *g_bfmeR1070;
extern BfmeX1070 *g_bfmeX1070;
extern char g_bfmeFmtA1070[];
extern char g_bfmeFmtB1070[];
extern char g_bfmeFmtD1070[];

class BfmeSub1070
{
public:
	virtual void bfmeSlot1070S_0(void);
	virtual void bfmeSlot1070S_1(void);
};

class BfmeG1070
{
public:
	virtual void bfmeSlot1070G_0(void);
	virtual void bfmeSlot1070G_1(void);
	virtual void bfmeSlot1070G_2(void);
	virtual void bfmeSlot1070G_3(void);
	virtual void bfmeSlot1070G_4(void);
	virtual void bfmeSlot1070G_5(void);
	virtual void bfmeSlot1070G_6(void);
	virtual void bfmeSlot1070G_7(void);
	virtual void bfmeSlot1070G_8(void);
	virtual void bfmeSlot1070G_9(void);
	virtual void bfmeSlot1070G_10(void);
	virtual void bfmeSlot1070G_11(void);
	virtual void bfmeSlot1070G_12(void);
	virtual void bfmeSlot1070G_13(void);
};

extern BfmeG1070 *g_bfmeG1070;

class BfmeT1070
{
public:
	void bfmeTail1070(void);
};

extern BfmeT1070 *g_bfmeT1070;

class BfmeQ1070
{
public:
	void bfmeGo1070A(void);
	char m_bfmePad[0x250];
	BfmeX1070 *m_bfme250;
	char m_bfmePad1[8];
	BfmeSub1070 m_bfmeSub;
	char m_bfmePad2[0x148];
	int m_bfme3a8;
};

void BfmeQ1070::bfmeGo1070A(void)
{
	if (!g_bfmeR1070 || !m_bfme3a8)
		return;
	m_bfme3a8 = 0;
	m_bfmeSub.bfmeSlot1070S_1();
	if (g_bfmeG1070)
		g_bfmeG1070->bfmeSlot1070G_13();
	g_bfmeT1070->bfmeTail1070();
	g_bfmeR1070->bfmeRun1070(m_bfme250, g_bfmeFmtA1070, 0, 0, 0, 0, 0, 0);
}

__declspec(dllimport) int __cdecl bfmeSpf1070(char *b, char *f, int a);



void bfmeGo1070B(float a)
{
	char buf[0x10];
	int n = 1 - (int)(a * -100.0f);

	if (n < 1)
		n = 1;
	else if (n > 100)
		n = 100;
	bfmeSpf1070(buf, g_bfmeFmtD1070, n);
	g_bfmeR1070->bfmeRun1070(g_bfmeX1070, g_bfmeFmtB1070, 1, buf, 0, 0, 0, 0);
}

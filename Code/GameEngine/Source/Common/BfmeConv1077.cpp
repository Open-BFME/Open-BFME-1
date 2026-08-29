// Open-BFME5 conversions.

class BfmeX1077;

struct BfmeFl1077
{
	float m_bfme00;
	float m_bfme04;
};

class BfmeR1077
{
public:
	virtual void bfmeSlot1077R_0(void);
	virtual void bfmeSlot1077R_1(void);
	virtual void bfmeSlot1077R_2(void);
	virtual void bfmeSlot1077R_3(void);
	virtual void bfmeSlot1077R_4(void);
	virtual void bfmeSlot1077R_5(void);
	virtual void bfmeSlot1077R_6(void);
	virtual void bfmeSlot1077R_7(void);
	virtual void bfmeSlot1077R_8(void);
	virtual void bfmeSlot1077R_9(void);
	virtual void bfmeSlot1077R_10(void);
	virtual BfmeFl1077 * bfmeSlot1077R_11(void);
	void bfmeRun1077(BfmeX1077 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1077 *g_bfmeR1077;
extern BfmeX1077 *g_bfmeX1077;
extern char g_bfmeFmtD1077[];
extern char g_bfmeFmtF1077[];
extern char g_bfmeFmtL1077[];

__declspec(dllimport) int __cdecl bfmeFmt1077(char *b, unsigned int n, char *f, ...);
BfmeX1077 *__cdecl bfmeMk1077(BfmeX1077 *a, BfmeX1077 *b);

extern BfmeX1077 *g_bfmeV1077;
extern char g_bfmeFmtM1077[];
extern char g_bfmeFmtN1077[];

void bfmeGo1077A(int a, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];
	BfmeFl1077 *p = g_bfmeR1077->bfmeSlot1077R_11();

	bfmeFmt1077(buf1, 0x10, g_bfmeFmtD1077, a);
	bfmeFmt1077(buf2, 0x10, g_bfmeFmtF1077, b * p->m_bfme00);
	bfmeFmt1077(buf3, 0x10, g_bfmeFmtF1077, c * p->m_bfme04);
	g_bfmeR1077->bfmeRun1077(g_bfmeX1077, g_bfmeFmtL1077, 3, buf1, buf2, buf3, 0, 0);
}

void bfmeGo1077B(int a, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];
	BfmeFl1077 *p;

	bfmeFmt1077(buf1, 0x10, g_bfmeFmtD1077, a);
	p = g_bfmeR1077->bfmeSlot1077R_11();
	bfmeFmt1077(buf2, 0x10, g_bfmeFmtF1077, b * p->m_bfme00);
	bfmeFmt1077(buf3, 0x10, g_bfmeFmtF1077, c * p->m_bfme04);
	g_bfmeR1077->bfmeRun1077(bfmeMk1077(g_bfmeV1077, g_bfmeV1077), g_bfmeFmtM1077, 3,
		buf1, buf2, buf3, 0, 0);
}

void bfmeGo1077C(int a, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];
	BfmeFl1077 *p;

	bfmeFmt1077(buf1, 0x10, g_bfmeFmtD1077, a);
	p = g_bfmeR1077->bfmeSlot1077R_11();
	bfmeFmt1077(buf2, 0x10, g_bfmeFmtF1077, b * p->m_bfme00);
	bfmeFmt1077(buf3, 0x10, g_bfmeFmtF1077, c * p->m_bfme04);
	g_bfmeR1077->bfmeRun1077(bfmeMk1077(g_bfmeV1077, g_bfmeV1077), g_bfmeFmtN1077, 3,
		buf1, buf2, buf3, 0, 0);
}

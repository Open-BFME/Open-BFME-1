// Open-BFME5 conversions.

class BfmeX1074;

struct BfmeFl1074
{
	float m_bfme00;
	float m_bfme04;
};

class BfmeR1074
{
public:
	virtual void bfmeSlot1074R_0(void);
	virtual void bfmeSlot1074R_1(void);
	virtual void bfmeSlot1074R_2(void);
	virtual void bfmeSlot1074R_3(void);
	virtual void bfmeSlot1074R_4(void);
	virtual void bfmeSlot1074R_5(void);
	virtual void bfmeSlot1074R_6(void);
	virtual void bfmeSlot1074R_7(void);
	virtual void bfmeSlot1074R_8(void);
	virtual void bfmeSlot1074R_9(void);
	virtual void bfmeSlot1074R_10(void);
	virtual BfmeFl1074 * bfmeSlot1074R_11(void);
	void bfmeRun1074(BfmeX1074 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1074 *g_bfmeR1074;
extern BfmeX1074 *g_bfmeY1074;
extern BfmeX1074 *g_bfmeV1074;
extern char g_bfmeFmtF1074[];
extern char g_bfmeFmtH1074[];
extern char g_bfmeFmtD1074[];
extern char g_bfmeFmtJ1074[];
extern char g_bfmeFmtK1074[];

__declspec(dllimport) int __cdecl bfmeFmtFl1074(char *b, unsigned int n, char *f, double d);
__declspec(dllimport) int __cdecl bfmeFmtIn1074(char *b, unsigned int n, char *f, int a);
BfmeX1074 *__cdecl bfmeMk1074(BfmeX1074 *a, BfmeX1074 *b);

void bfmeGo1074A(float a, float b)
{
	char buf1[0x10];
	char buf2[0x10];
	BfmeFl1074 *p = g_bfmeR1074->bfmeSlot1074R_11();

	bfmeFmtFl1074(buf1, 0x10, g_bfmeFmtF1074, a * p->m_bfme00);
	bfmeFmtFl1074(buf2, 0x10, g_bfmeFmtF1074, b * p->m_bfme04);
	g_bfmeR1074->bfmeRun1074(g_bfmeY1074, g_bfmeFmtH1074, 2, buf1, buf2, 0, 0, 0);
}

void bfmeGo1074B(int a, int b, int c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];

	bfmeFmtIn1074(buf1, 0x10, g_bfmeFmtD1074, a);
	bfmeFmtIn1074(buf2, 0x10, g_bfmeFmtJ1074, b);
	bfmeFmtIn1074(buf3, 0x10, g_bfmeFmtJ1074, c);
	g_bfmeR1074->bfmeRun1074(bfmeMk1074(g_bfmeV1074, g_bfmeV1074), g_bfmeFmtK1074, 3,
		buf1, buf2, buf3, 0, 0);
}

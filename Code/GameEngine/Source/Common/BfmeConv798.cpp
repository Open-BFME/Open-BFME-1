class BfmeUiDZE
{
public:
	void bfmeShowDZE(void *a, const char *msg, int b, void *p, int c, int d, int e, int f);
};

extern BfmeUiDZE *g_bfmeUiDZE;
extern void *g_bfmeArgDZE;

extern "C" __declspec(dllimport) int __cdecl bfmeFmtDZE(char *buf, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrDZE[];

extern "C" unsigned char bfmeMsgDZEa[];
extern "C" unsigned char bfmeMsgDZEb[];
extern "C" unsigned char bfmeMsgDZEc[];
extern "C" unsigned char bfmeMsgDZEd[];

void bfmeGoDZEa(int a)
{
	bfmeFmtDZE((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	g_bfmeUiDZE->bfmeShowDZE(g_bfmeArgDZE, (const char *)bfmeMsgDZEa, 1, &a, 0, 0, 0, 0);
}

void bfmeGoDZEb(int a)
{
	bfmeFmtDZE((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	g_bfmeUiDZE->bfmeShowDZE(g_bfmeArgDZE, (const char *)bfmeMsgDZEb, 1, &a, 0, 0, 0, 0);
}

void bfmeGoDZEc(int a)
{
	bfmeFmtDZE((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	g_bfmeUiDZE->bfmeShowDZE(g_bfmeArgDZE, (const char *)bfmeMsgDZEc, 1, &a, 0, 0, 0, 0);
}

void bfmeGoDZEd(int a)
{
	bfmeFmtDZE((char *)&a, (const char *)bfmeFmtStrDZE, a + 1);
	g_bfmeUiDZE->bfmeShowDZE(g_bfmeArgDZE, (const char *)bfmeMsgDZEd, 1, &a, 0, 0, 0, 0);
}


class BfmeUiEAA
{
public:
	void bfmeShowEAA(void *a, const char *msg, int n, void *p, const char *s, int c, int d, int e);
};

extern BfmeUiEAA *g_bfmeUiEAA;
extern void *g_bfmeArgEAA;

extern "C" __declspec(dllimport) int __cdecl bfmeFmtEAA(char *buf, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrEAA[];
extern "C" unsigned char bfmeOnEAA[];
extern "C" unsigned char bfmeOffEAA[];
extern "C" unsigned char bfmeOnEAB[];
extern "C" unsigned char bfmeOffEAB[];

extern "C" unsigned char bfmeMsgEAAa[];
extern "C" unsigned char bfmeMsgEAAb[];
extern "C" unsigned char bfmeMsgEAAc[];
extern "C" unsigned char bfmeMsgEAAd[];

void bfmeGoEAAa(int a, bool flag)
{
	bfmeFmtEAA((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	g_bfmeUiEAA->bfmeShowEAA(g_bfmeArgEAA, (const char *)bfmeMsgEAAa, 2, &a,
		flag ? (const char *)bfmeOnEAA : (const char *)bfmeOffEAA, 0, 0, 0);
}

void bfmeGoEAAb(int a, bool flag)
{
	bfmeFmtEAA((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	g_bfmeUiEAA->bfmeShowEAA(g_bfmeArgEAA, (const char *)bfmeMsgEAAb, 2, &a,
		flag ? (const char *)bfmeOnEAB : (const char *)bfmeOffEAB, 0, 0, 0);
}

void bfmeGoEAAc(int a, bool flag)
{
	bfmeFmtEAA((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	g_bfmeUiEAA->bfmeShowEAA(g_bfmeArgEAA, (const char *)bfmeMsgEAAc, 2, &a,
		flag ? (const char *)bfmeOnEAA : (const char *)bfmeOffEAA, 0, 0, 0);
}

void bfmeGoEAAd(int a, bool flag)
{
	bfmeFmtEAA((char *)&a, (const char *)bfmeFmtStrEAA, a + 1);
	g_bfmeUiEAA->bfmeShowEAA(g_bfmeArgEAA, (const char *)bfmeMsgEAAd, 2, &a,
		flag ? (const char *)bfmeOnEAA : (const char *)bfmeOffEAA, 0, 0, 0);
}


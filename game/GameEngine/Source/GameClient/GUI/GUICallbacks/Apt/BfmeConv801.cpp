class BfmeUiEAC
{
public:
	void bfmeShowEAC(void *a, const char *msg, int n, void *p, int c, int d, int e, int f);
	void bfmeListEAC(void *a, const char *msg, int n, void *p, void *q, int c, int d, int e);
};

extern BfmeUiEAC *g_bfmeUiEAC;
extern void *g_bfmeArgEAC;

extern "C" __declspec(dllimport) int __cdecl bfmeFmtEAC(char *buf, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrEAC[];
extern "C" unsigned char bfmeMsgEACa[];
extern "C" void *bfmeTabEAC[];
extern "C" unsigned char bfmeMsgEACb[];

void bfmeGoEACa(int a)
{
	if (a >= 1 || a <= 100)
	{
		bfmeFmtEAC((char *)&a, (const char *)bfmeFmtStrEAC, a);
		g_bfmeUiEAC->bfmeShowEAC(g_bfmeArgEAC, (const char *)bfmeMsgEACa, 1, &a, 0, 0, 0, 0);
	}
}

void bfmeGoEACb(int a, int i)
{
	bfmeFmtEAC((char *)&a, (const char *)bfmeFmtStrEAC, a + 1);
	g_bfmeUiEAC->bfmeListEAC(g_bfmeArgEAC, (const char *)bfmeMsgEACb, 2, &a, bfmeTabEAC[i], 0, 0, 0);
}

class BfmeUiDZF
{
public:
	void bfmeShowDZF(void *a, const char *msg, int b, void *p, int c, int d, int e, int f);
};

extern BfmeUiDZF *g_bfmeUiDZF;
extern void *g_bfmeArgDZF;

extern "C" __declspec(dllimport) int __cdecl bfmeSnpDZF(char *buf, unsigned int n, const char *fmt, int v);
extern "C" unsigned char bfmeFmtStrDZF[];

extern "C" unsigned char bfmeMsgDZFa[];
extern "C" unsigned char bfmeMsgDZFb[];
extern "C" unsigned char bfmeMsgDZFc[];
extern "C" unsigned char bfmeMsgDZFd[];

void bfmeGoDZFa(int a)
{
	char buf[16];
	bfmeSnpDZF(buf, 16, (const char *)bfmeFmtStrDZF, a);
	g_bfmeUiDZF->bfmeShowDZF(g_bfmeArgDZF, (const char *)bfmeMsgDZFa, 1, buf, 0, 0, 0, 0);
}

void bfmeGoDZFb(int a)
{
	char buf[16];
	bfmeSnpDZF(buf, 16, (const char *)bfmeFmtStrDZF, a);
	g_bfmeUiDZF->bfmeShowDZF(g_bfmeArgDZF, (const char *)bfmeMsgDZFb, 1, buf, 0, 0, 0, 0);
}

void bfmeGoDZFc(int a)
{
	char buf[16];
	bfmeSnpDZF(buf, 16, (const char *)bfmeFmtStrDZF, a);
	g_bfmeUiDZF->bfmeShowDZF(g_bfmeArgDZF, (const char *)bfmeMsgDZFc, 1, buf, 0, 0, 0, 0);
}

void bfmeGoDZFd(int a)
{
	char buf[16];
	bfmeSnpDZF(buf, 16, (const char *)bfmeFmtStrDZF, a);
	g_bfmeUiDZF->bfmeShowDZF(g_bfmeArgDZF, (const char *)bfmeMsgDZFd, 1, buf, 0, 0, 0, 0);
}


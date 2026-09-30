// Open-BFME5 conversions.

class BfmeX1068;

class BfmeR1068
{
public:
	void bfmeRun1068(BfmeX1068 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1068 *g_bfmeR1068;
extern BfmeX1068 *g_bfmeX1068;
extern char g_bfmeFmtD1068[];
extern char g_bfmeFmtA1068[];
extern char g_bfmeFmtB1068[];

extern "C" __declspec(dllimport) int __cdecl sprintf(char *b, char *f, int a);

void bfmeGo1068A(int a, int b)
{
	int v = b;

	if (!v)
		v = 1;
	sprintf((char *)&b, g_bfmeFmtD1068, a + 1);
	sprintf((char *)&a, g_bfmeFmtD1068, v);
	g_bfmeR1068->bfmeRun1068(g_bfmeX1068, g_bfmeFmtA1068, 2, (char *)&b, (char *)&a, 0, 0, 0);
}

void bfmeGo1068B(int a, int b)
{
	int v = b;

	if (!v)
		v = 1;
	sprintf((char *)&b, g_bfmeFmtD1068, a + 1);
	sprintf((char *)&a, g_bfmeFmtD1068, v);
	g_bfmeR1068->bfmeRun1068(g_bfmeX1068, g_bfmeFmtB1068, 2, (char *)&b, (char *)&a, 0, 0, 0);
}

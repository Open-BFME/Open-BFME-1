// Open-BFME5 conversions.

extern int *g_bfmeA986B;
extern int *g_bfmeB986B;
extern int g_bfmeZero986B;
extern char *g_bfmePtr986B;
extern char g_bfmeTarget986B[];

int bfmeCheck986B(void);

int bfmeGo986B(void)
{
	g_bfmeZero986B = 0;

	if (g_bfmeA986B && g_bfmeB986B && bfmeCheck986B()) {
		g_bfmePtr986B = g_bfmeTarget986B;
		return 1;
	}

	return 0;
}

class BfmeC986
{
public:
	void bfmeGo986C(int a, int b, int c, int d);
	char bfmeReady986C();
	void bfmePrep986C();
	void bfmeSend986C(int a, int b, int c, int d, int e);
};

void BfmeC986::bfmeGo986C(int a, int b, int c, int d)
{
	if (!bfmeReady986C())
		return;

	bfmePrep986C();
	bfmeSend986C(a, b, 0, c, d);
}

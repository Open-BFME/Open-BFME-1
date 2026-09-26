// Open-BFME5 conversions.

class BfmeJ1017
{
public:
	void bfmeSendX1017(int a, int b);
	void bfmeSendY1017(int a, int b, int c);
};

extern char g_bfme1017G;
extern int g_bfme1017H;
extern int g_bfme1017I;
extern BfmeJ1017 *g_bfmeJ1017;

void bfmeGo1017X(int a, int b)
{
	if (g_bfme1017G != 0 && g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeJ1017 != 0)
		g_bfmeJ1017->bfmeSendX1017(a, b);
}

void bfmeGo1017Y(int a, int b, int c)
{
	if (g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeJ1017 != 0)
		g_bfmeJ1017->bfmeSendY1017(a, b, c);
}

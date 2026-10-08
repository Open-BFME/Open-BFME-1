// Open-BFME5 conversions.

class BfmeJ1017
{
public:
	void bfmeSendX1017(int a, int b);
	void bfmeSendY1017(int a, int b, int c);
};

extern unsigned char g_bfmeDispatchEnabled1281;
// retail VA 0x01337800 (dir32 of the matched bfmeGo1017X/Y reads).
int g_bfme1017H;
extern int g_bfme1017I;

// retail 0x013377D8; defining spelling (BfmePicker1284.cpp), declared
// incomplete here because this TU only needs the two calls below.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;

void bfmeGo1017X(int a, int b)
{
	if (g_bfmeDispatchEnabled1281 != 0 && g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeHolderBU != 0)
		((BfmeJ1017 *)g_bfmeHolderBU)->bfmeSendX1017(a, b);
}

void bfmeGo1017Y(int a, int b, int c)
{
	if (g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeHolderBU != 0)
		((BfmeJ1017 *)g_bfmeHolderBU)->bfmeSendY1017(a, b, c);
}

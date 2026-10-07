// Open-BFME5 conversions.

class BfmeJ1017
{
public:
	void bfmeSendX1017(int a, int b);
	void bfmeSendY1017(int a, int b, int c);
	void rva008A1BB0(int a, int b, unsigned char c, int type);
};

// Retail 0x00892100 reserves 16 outgoing bytes and copies its four incoming
// dwords into them (sub esp,16 / mov [eax+N]), the shape MSVC gives a 16-byte
// aggregate forwarded by value; its fields are the four slots
// BfmeJ1017::rva008A1BB0 (0x008A1BB0, ret 16) reads.
struct Rva00892100Event
{
	int a;
	int b;
	unsigned char c;
	int type;
};

extern char g_bfme1017G;
extern int g_bfme1017H;
extern int g_bfme1017I;

// retail 0x013377D8; defining spelling (BfmePicker1284.cpp), declared
// incomplete here because this TU only needs the two calls below.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;

void bfmeGo1017X(int a, int b)
{
	if (g_bfme1017G != 0 && g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeHolderBU != 0)
		((BfmeJ1017 *)g_bfmeHolderBU)->bfmeSendX1017(a, b);
}

void bfmeGo1017Y(int a, int b, int c)
{
	if (g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeHolderBU != 0)
		((BfmeJ1017 *)g_bfmeHolderBU)->bfmeSendY1017(a, b, c);
}

void bfmeGo1017Event00892100(Rva00892100Event event)
{
	typedef void (BfmeJ1017::*Send)(Rva00892100Event);
	union { void (BfmeJ1017::*scalar)(int, int, unsigned char, int); Send send; } u =
		{ &BfmeJ1017::rva008A1BB0 };
	if (g_bfme1017H != 0 && g_bfme1017I == 0 && g_bfmeHolderBU != 0)
		(((BfmeJ1017 *)g_bfmeHolderBU)->*u.send)(event);
}

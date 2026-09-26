// Open-BFME5 conversions.

class BfmeSub1097
{
public:
	int bfmeCmp1097(BfmeSub1097 *o);
	char m_bfmePad[4];
};

class BfmeU1097
{
public:
	char m_bfmePad[0x28];
	BfmeSub1097 m_bfme28;
	char m_bfmePad1[0x9c];
	char m_bfmec8;
	char m_bfmePad2[0x2c3];
	BfmeU1097 *m_bfme38c;
};

class BfmeR1097
{
public:
	void bfmeClr1097(void);
	void bfmeOff1097(BfmeU1097 *u);
	char m_bfmePad[0x28];
	BfmeSub1097 m_bfme28;
};

struct BfmeS1097
{
	char m_bfmePad[8];
	BfmeU1097 *m_bfme08;
};

class BfmeD1097
{
public:
	BfmeR1097 *bfmeGet1097(int h);
};

class BfmeP1097
{
public:
	int bfmeFirst1097(int a, int b);
};

extern BfmeD1097 *g_bfmeD1097;
extern BfmeP1097 *g_bfmeP1097;
extern BfmeS1097 *g_bfmeS1097;

void __stdcall bfmeGo1097A(int a, char b)
{
	int h = g_bfmeP1097->bfmeFirst1097(a + 0x10, 0);
	BfmeR1097 *r;
	BfmeU1097 *u;

	if (!(short)h)
		return;
	r = g_bfmeD1097->bfmeGet1097(h);
	if (!r)
		return;
	if (b) {
		r->bfmeClr1097();
		return;
	}
	u = g_bfmeS1097->m_bfme08;
	r->bfmeClr1097();
	while (u) {
		if ((u->m_bfmec8 & 0x80) && !u->m_bfme28.bfmeCmp1097(&r->m_bfme28))
			r->bfmeOff1097(u);
		u = u->m_bfme38c;
	}
}

// ?d_00233ec0@@YAXXZ
// partial score=0.85 date=2026-09-06
// Open-BFME5 conversions.

struct BfmeSub233EC0
{
	unsigned char m_bfmeHead[4];
};

struct BfmeHeld233EC0
{
	unsigned char m_bfmeHead[0x248];
	BfmeSub233EC0 m_bfmeSub;
};

class BfmeGlob233EC0
{
public:
	void *bfmeLook233EC0(int s);
};

extern BfmeGlob233EC0 *g_bfmeObj233EC0;

class BfmeThing233EC0
{
public:
	void bfmeGo233EC0();
};

void BfmeThing233EC0::bfmeGo233EC0()
{
	BfmeGlob233EC0 *g = g_bfmeObj233EC0;
	int s = (int)&(*(BfmeHeld233EC0 **)((char *)this - 0xe0))->m_bfmeSub;
	g->bfmeLook233EC0(s);
}

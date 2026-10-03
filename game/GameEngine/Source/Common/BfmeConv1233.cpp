// Open-BFME5 conversions.

struct BfmeBuf1233
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
};

struct BfmeStr1233
{
	BfmeBuf1233 *m_bfme00;
};

struct BfmeAlloc1233
{
	void *m_bfme00;
	void (__cdecl *m_bfme04)(BfmeBuf1233 *a);
};

class BfmeE1233
{
public:
	void bfmeName1233(BfmeStr1233 *a);
};

class BfmeN1233
{
public:
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x20 - 0x08];
	void *m_bfme20;
	char m_bfmePad24[4];
	void *m_bfme28;
};

extern BfmeStr1233 g_bfmeStr1233;
// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU keeps its own local view of the block and casts at each use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;
extern BfmeAlloc1233 *g_bfmeAlloc1233;
struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	BfmeE1233** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
// 0x013379BC is the fallback value database pointer, defined as AptValue *
// by Bfme5AppendFallback8CAFF0.cpp (?g_bfmeFallbackDB@@3PAVAptValue@@A).
class AptValue;
extern AptValue *g_bfmeFallbackDB;

extern "C" void bfmeHandler1233(void);
extern "C" void bfmeReport1233(void *a, void *b, int c, void (*d)(void));

void *bfmeVisit1233(BfmeN1233 *a, int n)
{
	BfmeE1233 *e;
	BfmeBuf1233 *buf;

	if ((a->m_bfme04 & 0x3f) == 0x16 && !((unsigned char)(~(a->m_bfme04 >> 15)) & 1) && n > 0) {
		Rva008AE770Stack& stk = Rva008AE770TheStack;
		BfmeE1233** args = stk.m_rva01338750;
		e = args[stk.field00 - 1];
		e->bfmeName1233(&g_bfmeStr1233);
		bfmeReport1233(a->m_bfme20, a->m_bfme28, 4, bfmeHandler1233);
		buf = g_bfmeStr1233.m_bfme00;
		--buf->m_bfme00;
		if (buf->m_bfme00 == 0)
			g_bfmeAlloc1233->m_bfme04(buf);
		++((BfmeBuf1233 *)&g_rva012D5298Empty)->m_bfme00;
		g_bfmeStr1233.m_bfme00 = (BfmeBuf1233 *)&g_rva012D5298Empty;
	}
	return g_bfmeFallbackDB;
}

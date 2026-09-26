// ?Rva008B4DA0@Rva01136AB8Owner@@QAEPAXPAXPBUBfmeCandidateDX@@@Z
// partial score=0.82 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008B4DA0: vtable 0x01136AB8 slot 0; looks a string handle up among four
// globals and lazily builds one cached object per match. Identity unrecovered.

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
void Gen00897300(void *block);
int __cdecl bfmeCompareVSC(const char *a, const char *b);
extern "C" void *bfmeVft1029A[];

// upstream layout: Code/GameEngine/Source/Common/BfmeConv1029.cpp
class BfmeA1029
{
public:
	BfmeA1029 *bfmeGo1029A(int a);
	void bfmeBase1029(int n, int m);

	void	*m_bfmeVfptr;
	char	m_bfmePad[0x1c];
	int		m_bfmeVal;
};

// upstream layout: Code/GameEngine/Source/Common/BfmeConv1082.cpp
class BfmeS1082
{
public:
	virtual void bfmeSlot1082S_0(void);
	virtual void bfmeSlot1082S_1(void);
};

extern BfmeS1082 *g_bfmeS1082_4;	// retail 0x01338388
extern BfmeS1082 *g_bfmeS1082_5;	// retail 0x0133838C
extern BfmeS1082 *g_bfmeS1082_6;	// retail 0x01338390
extern BfmeS1082 *g_bfmeS1082_7;	// retail 0x01338394

// Refcounted string payload; the text starts after an 8-byte header.
struct BfmeCandidateDataDX
{
	const void	*m_head;	// +0x00
	const void	*m_reserved;	// +0x04
	char		m_name[1];	// +0x08
};

// A string handle: one pointer to its shared payload.
struct BfmeCandidateDX
{
	const BfmeCandidateDataDX *m_tag;	// +0x00
};

extern BfmeCandidateDX g_bfmeCandidate0;	// retail 0x013386A0
extern BfmeCandidateDX g_bfmeCandidate1;	// retail 0x01338594
extern BfmeCandidateDX g_bfmeCandidate2;	// retail 0x013385A4
extern BfmeCandidateDX g_bfmeCandidate3;	// retail 0x013386AC

static void bfmeSetRegisteredFlag(BfmeS1082 *obj)
{
	unsigned int *bits = (unsigned int *)((char *)obj + 4);
	*bits = (*bits & 0xffffc07f) | 0x40;
}

// Same payload, or equal text.
inline bool bfmeSameCandidate(const BfmeCandidateDataDX *x, const BfmeCandidateDataDX *y)
{
	return x == y || bfmeCompareVSC(x->m_name, y->m_name) == 0;
}

// One class for all four matches: MSVC inlines new and ctor for the first two and calls
// the out-of-line copies (0x00897640, 0x00899FC0) for the rest; unwind uses 0x00897670.
class BfmeCandidateSingleton0 : public BfmeA1029
{
public:
	static void *operator new(unsigned int n)
	{
		char *raw = (char *)Rva008C5D70Alloc(n + 8);
		char *block = raw + 8;
		Gen00897300(block);
		return block;
	}
	static void operator delete(void *block, unsigned int n);

	BfmeCandidateSingleton0(int value)
	{
		bfmeBase1029(9, 8);
		m_bfmeVfptr = bfmeVft1029A;
		m_bfmeVal = value;
	}
};

class Rva01136AB8Owner
{
public:
	void *Rva008B4DA0(void *unused, const BfmeCandidateDX *desc);
};

// ?Rva008B4DA0@Rva01136AB8Owner@@QAEPAXPAXPBUBfmeCandidateDX@@@Z
void *Rva01136AB8Owner::Rva008B4DA0(void *unused, const BfmeCandidateDX *desc)
{
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate0.m_tag))
	{
		if (g_bfmeS1082_4 == 0)
		{
			g_bfmeS1082_4 = (BfmeS1082 *)new BfmeCandidateSingleton0(0xcb4370);
			bfmeSetRegisteredFlag(g_bfmeS1082_4);
			g_bfmeS1082_4->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_4;
	}
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate1.m_tag))
	{
		if (g_bfmeS1082_5 == 0)
		{
			g_bfmeS1082_5 = (BfmeS1082 *)new BfmeCandidateSingleton0(0xcb4420);
			bfmeSetRegisteredFlag(g_bfmeS1082_5);
			g_bfmeS1082_5->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_5;
	}
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate2.m_tag))
	{
		if (g_bfmeS1082_6 == 0)
		{
			g_bfmeS1082_6 = (BfmeS1082 *)new BfmeCandidateSingleton0(0xcb4700);
			bfmeSetRegisteredFlag(g_bfmeS1082_6);
			g_bfmeS1082_6->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_6;
	}
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate3.m_tag))
	{
		if (g_bfmeS1082_7 == 0)
		{
			g_bfmeS1082_7 = (BfmeS1082 *)new BfmeCandidateSingleton0(0xcb4480);
			bfmeSetRegisteredFlag(g_bfmeS1082_7);
			g_bfmeS1082_7->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_7;
	}
	return 0;
}

// Open-BFME5: retail RVA 0x00618890, 182 bytes.
//
// The vtable at 0x01116D64 and the matched methods at 0x00618740 and
// 0x006187D0 identify Rva00618600Poly as the owner.  The constructor stores
// the lookup result and fills the default state used by both methods.
//
// The local support types describe only the fields and calls this constructor
// reads.  Their address-derived names avoid claiming a public class spelling
// that the retail binary does not expose.

// cl: /DNDEBUG /MD /EHsc

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufXB;

private:
	void releaseBuffer();
};

struct BfmeSlotJA
{
	unsigned char m_bfmeHeadJA[0xc];
	int m_bfme0CJA;
};

class BfmeSubBIA
{
public:
	int ask();
};

class BfmeEntryXB
{
public:
	void *m_bfme00XB;
	BfmeSubBIA *m_bfme04XB;
	unsigned char m_bfme08XB[4];
	int m_bfme0CXB;
};

class BfmeGameXB
{
public:
	BfmeEntryXB *bfmeLookupXB(const BFMERetailAsciiString *name);
};

extern "C" BfmeGameXB *g_bfmeGameCW;
extern "C" unsigned char rva00618600Vft[];
extern "C" const char *rva00618600Names[];

static __forceinline const char *rva00618600Name(int which)
{
	return rva00618600Names[which];
}

static __forceinline BfmeSlotJA *rva00618600Resolve(BfmeEntryXB *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04XB == 0)
		return (BfmeSlotJA *)p;

	return (BfmeSlotJA *)p->m_bfme04XB->ask();
}

class Rva00618600Poly
{
public:
	Rva00618600Poly(int which, int first, int second);

	void *volatile m_bfmeVfXB;
	BfmeEntryXB *volatile m_bfme04XB;
	int m_bfme08XB;
	volatile int m_bfme0CXB;
	char m_bfme10XB;
	unsigned char m_bfme11XB[3];
	int m_bfme14XB;
	int m_bfme18XB;
	int m_bfme1CXB;
	int m_bfme20XB;
};

Rva00618600Poly::Rva00618600Poly(int which, int first, int second)
{
	m_bfmeVfXB = rva00618600Vft;
	m_bfme04XB = 0;
	m_bfme08XB = second;
	m_bfme0CXB = first;
	m_bfme10XB = 0;
	m_bfme14XB = 0;
	m_bfme18XB = 0;
	m_bfme1CXB = 0;
	m_bfme20XB = 0;

	{
		const BFMERetailAsciiString name(rva00618600Name(which));

		BfmeGameXB *g = g_bfmeGameCW;

		register const BFMERetailAsciiString *np = &name;

		BfmeEntryXB *lookup = g->bfmeLookupXB(np);
		*(BfmeEntryXB **)&m_bfme04XB = lookup;
	}

	if (rva00618600Resolve(m_bfme04XB)->m_bfme0CJA == 0)
		m_bfme20XB = 5;
}

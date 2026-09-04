// Open-BFME5: the larger credited default constructor at retail 0x00471390,
// 160 bytes -- the sibling of 0x00471EC0 with two more destructible groups.
//
// The unwind state runs 0 then 2: state 0 is the empty guard base, and the two
// zeroed groups at +0x24 and +0x34 are destructible sub-objects whose inline
// constructors fold to displacement stores.  The two trailing 20-byte runs go
// through materialised pointers instead, so those are memsets over plain
// structs.

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);

#pragma intrinsic(memset)

extern int g_bfmeVtableWB[];					// retail 0x010F756C

class BfmeStrWB
{
public:
	BfmeStrWB(const char *text);
	~BfmeStrWB(void);

private:
	char *m_bfmeData;
};

class BfmeGuardWB
{
public:
	~BfmeGuardWB(void);
};

class BfmeQuadWB
{
public:
	__forceinline BfmeQuadWB(void)
	{
		m_bfmeA = 0;
		m_bfmeB = 0;
		m_bfmeC = 0;
	}

	~BfmeQuadWB(void);

	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
};

class BfmeOneWB
{
public:
	__forceinline BfmeOneWB(void)
	{
		m_bfmeA = 0;
	}

	~BfmeOneWB(void);

	int m_bfmeA;						// +0x00
};

class BfmePairWB
{
public:
	__forceinline BfmePairWB(void) : m_bfmeA(0), m_bfmeB(0)
	{
	}

	~BfmePairWB(void);

	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

struct BfmeFiveWB
{
	int m_bfmeSlot[5];
};

class Gen_00471390;

__forceinline int bfmeInstallWB(Gen_00471390 *self, int value);

class Gen_00471390 : public BfmeGuardWB
{
public:
	Gen_00471390(void);

	int *m_bfmeVtable;					// +0x00
	char m_bfmePad04[0x18];					// +0x04
	int m_bfmeX;						// +0x1C
	int m_bfmeY;						// +0x20
	BfmeQuadWB m_bfmeQuad;					// +0x24
	BfmeOneWB m_bfmeOne;					// +0x30
	int m_bfmeZ;						// +0x34
	int m_bfmeW;						// +0x38
	BfmeStrWB m_bfmeName;					// +0x3C
	int m_bfmeCode;						// +0x40
	int m_bfmeCount;					// +0x44
	int m_bfmeLimit;					// +0x48
	BfmeFiveWB m_bfmeFirst;					// +0x4C
	BfmeFiveWB m_bfmeSecond;				// +0x60
};

__forceinline int bfmeInstallWB(Gen_00471390 *self, int value)
{
	self->m_bfmeVtable = g_bfmeVtableWB;

	return value;
}

// ??0Gen_00471390@@QAE@XZ
Gen_00471390::Gen_00471390(void)
	: m_bfmeX(bfmeInstallWB(this, 0)), m_bfmeY(0),
	  m_bfmeZ(0), m_bfmeW(0),
	  m_bfmeName("SachaWynter"),
	  m_bfmeCode(0x00DCF0FA), m_bfmeCount(8), m_bfmeLimit(0xE)
{
	memset(&m_bfmeFirst, 0, sizeof(m_bfmeFirst));

	memset(&m_bfmeSecond, 0, sizeof(m_bfmeSecond));
}

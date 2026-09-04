// Open-BFME5: the credited default constructor at retail 0x00471EC0, 125 bytes.
//
// Only the table store, two zeroed words, the name and the trailing constants
// are written; +0x04..+0x1B is left alone.  The table store sits after the
// name's argument setup, so it is issued from the name's own initializer, and
// the unwind frame comes from an empty base with a declared destructor.

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);

#pragma intrinsic(memset)

extern int g_bfmeVtableWA[];					// retail 0x010F760C

class BfmeStrWA
{
public:
	BfmeStrWA(const char *text);
	~BfmeStrWA(void);

private:
	char *m_bfmeData;
};

class BfmeGuardWA
{
public:
	~BfmeGuardWA(void);
};

struct BfmeTripleWA
{
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
};

class Gen_00471EC0;

__forceinline int bfmeInstallWA(Gen_00471EC0 *self, int value);

class Gen_00471EC0 : public BfmeGuardWA
{
public:
	Gen_00471EC0(void);

	int *m_bfmeVtable;					// +0x00
	char m_bfmePad04[0x18];					// +0x04
	int m_bfmeX;						// +0x1C
	int m_bfmeY;						// +0x20
	BfmeStrWA m_bfmeName;					// +0x24
	int m_bfmeCode;						// +0x28
	int m_bfmeCount;					// +0x2C
	int m_bfmeLimit;					// +0x30
	BfmeTripleWA m_bfmeFirst;				// +0x34
	BfmeTripleWA m_bfmeSecond;				// +0x40
};

__forceinline int bfmeInstallWA(Gen_00471EC0 *self, int value)
{
	self->m_bfmeVtable = g_bfmeVtableWA;

	return value;
}

// ??0Gen_00471EC0@@QAE@XZ
Gen_00471EC0::Gen_00471EC0(void)
	: m_bfmeX(bfmeInstallWA(this, 0)), m_bfmeY(0),
	  m_bfmeName("SachaWynter"),
	  m_bfmeCode(0x00DCF0FA), m_bfmeCount(8), m_bfmeLimit(0xE)
{
	memset(&m_bfmeFirst, 0, sizeof(m_bfmeFirst));

	memset(&m_bfmeSecond, 0, sizeof(m_bfmeSecond));
}

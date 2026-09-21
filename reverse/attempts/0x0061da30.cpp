// ?bfmeBaseInitBG@BfmeNamedBG@@QAEXVAsciiStringBG@@@Z
// partial score=0.5 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a named object constructor at retail 0x0060AAE0, 67 bytes.  The
// caller's name is copied into the by-value argument the base initialiser
// takes, and the vftable lands between two of the field stores.

class StringBaseNarrowBG
{
protected:
	StringBaseNarrowBG(const StringBaseNarrowBG &other);

	~StringBaseNarrowBG(void);

	char *m_bfmeNarrowBG;
};

class AsciiStringBG : public StringBaseNarrowBG
{
public:
	AsciiStringBG(const AsciiStringBG &other) : StringBaseNarrowBG(other)
	{
	}

	~AsciiStringBG(void)
	{
	}
};

extern "C" void *bfmeVftableBG[];

// The temporary vtable bfmeBaseInitBG installs before the caller overwrites
// it with its own (bfmeVftableBG here, rva0060bbd0Vftable in the sibling
// Rva0060BBD0Ctor.cpp) -- same two-step GenBase-style install as the shared
// texture-base ctor at 0x0090CF90.
extern "C" void *bfmeBaseInitVftableBG[];

inline void * __cdecl operator new(unsigned int, void *where) { return where; }

// Non-throw() duplicates for bfmeBaseInitBG's own call site: its retail body
// carries an SEH frame around the copy, so the callee it reaches there must
// not be declared throw() the way the already-matched 67-byte outer
// constructor's callee is.
class StringBaseNarrowBGInit
{
protected:
	StringBaseNarrowBGInit(const StringBaseNarrowBGInit &other);
	~StringBaseNarrowBGInit(void);
	char *m_bfmeNarrowBG;
};

class AsciiStringBGInit : public StringBaseNarrowBGInit
{
public:
	AsciiStringBGInit(const AsciiStringBGInit &other) : StringBaseNarrowBGInit(other)
	{
	}

	~AsciiStringBGInit(void)
	{
	}
};

class BfmeNamedBG
{
public:
	BfmeNamedBG(const AsciiStringBG &name);

	void bfmeBaseInitBG(AsciiStringBG name);

	void *volatile m_bfmeVfptrBG;
	int m_bfme04;					// +0x04 (AsciiStringBG placement-constructed here)
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
	volatile int m_bfme38;
	volatile int m_bfme3c;
	volatile int m_bfme40;
	volatile int m_bfme44;
	volatile int m_bfme48;
	volatile char m_bfme4c;
	volatile int m_bfme50;
	volatile int m_bfme54;
	volatile int m_bfme58;
	volatile int m_bfme5c;
	volatile int m_bfme60;
	volatile int m_bfme64;
	volatile int m_bfme68;
	volatile char m_bfme6c;
	volatile int m_bfme70;
	volatile int m_bfme74;
	volatile int m_bfme78;
	volatile char m_bfme7c;
	volatile int m_bfme80;
	volatile int m_bfme84;
	volatile int m_bfme88;
	volatile int m_bfme8c;
	volatile int m_bfme90;
	volatile int m_bfme94;
	volatile int m_bfme98;
	volatile int m_bfme9c;
	volatile char m_bfmeFlagBG;
	char m_bfmePadBBG[3];
	volatile int m_bfmeABG;
	volatile int m_bfmeBBG;
	volatile int m_bfmeCBG;
};

// ?bfmeBaseInitBG@BfmeNamedBG@@QAEXVAsciiStringBG@@@Z
void BfmeNamedBG::bfmeBaseInitBG(AsciiStringBG name)
{
	((AsciiStringBG *)&m_bfme04)->AsciiStringBG::AsciiStringBG(name);
	m_bfmeVfptrBG = bfmeBaseInitVftableBG;

	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme1c = 0;
	m_bfme18 = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme28 = 0;
	m_bfme30 = 0;
	m_bfme34 = 0;
	m_bfme3c = 0;
	m_bfme44 = 0;
	m_bfme48 = 0;
	m_bfme4c = 0;

	{
	int one = 1;
	m_bfme2c = one;
	m_bfme38 = one;
	m_bfme40 = one;
	}

	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;

	m_bfme68 = 0x3dcccccd;
	m_bfme6c = 0;

	{
	int oneF = 0x3f800000;
	m_bfme70 = oneF;
	m_bfme74 = oneF;
	m_bfme78 = 0x3a83126f;
	m_bfme7c = 0;

	m_bfme80 = 0;
	m_bfme84 = 0x40c8a3d7;
	m_bfme88 = 0x3e99999a;
	m_bfme8c = oneF;
	m_bfme90 = oneF;
	m_bfme94 = oneF;
	m_bfme98 = oneF;
	m_bfme9c = oneF;
	}
}

BfmeNamedBG::BfmeNamedBG(const AsciiStringBG &name)
{
	bfmeBaseInitBG(name);

	m_bfmeFlagBG = 0;

	m_bfmeABG = 0;

	m_bfmeBBG = 0;

	m_bfmeVfptrBG = bfmeVftableBG;

	m_bfmeCBG = 0;
}

// BfmeNamedBG's own destructor (BfmeNamedDtorBG.cpp, retail 0x0060AB40) calls
// this base sibling's dtor last; it lives here, in the same TU as the
// constructor, purely so the file keeps a matched row (check_orphans) while
// staying out-of-line (undefined at the call site, so it cannot be elided).
class BfmeNamedBaseBG
{
public:
	virtual ~BfmeNamedBaseBG();
};

// ??1BfmeNamedBaseBG@@UAE@XZ present-unmatched
BfmeNamedBaseBG::~BfmeNamedBaseBG()
{
}

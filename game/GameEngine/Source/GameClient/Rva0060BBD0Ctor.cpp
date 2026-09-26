// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME: constructor at retail 0x0060BBD0 (100B).  Address-derived name:
// the ZH identity is not proven.  Same field shape as BfmeNamedCtorBG.cpp
// (0x0060AAE0) -- a by-value AsciiStringBG name forwarded to bfmeBaseInitBG --
// but this ctor calls bfmeBaseInitBG directly and installs its OWN vtable
// afterward, instead of chaining through BfmeNamedBG's full constructor
// (no stores to the flag/A/B/C fields are present in the retail body).

class StringBaseNarrowBG_Rva0060BBD0
{
protected:
	StringBaseNarrowBG_Rva0060BBD0(const StringBaseNarrowBG_Rva0060BBD0 &other);
	~StringBaseNarrowBG_Rva0060BBD0(void);
	char *m_bfmeNarrowBG;
};

class AsciiStringBG_Rva0060BBD0 : public StringBaseNarrowBG_Rva0060BBD0
{
public:
	AsciiStringBG_Rva0060BBD0(const AsciiStringBG_Rva0060BBD0 &other) : StringBaseNarrowBG_Rva0060BBD0(other)
	{
	}

	~AsciiStringBG_Rva0060BBD0(void)
	{
	}
};

class BfmeNamedBG_Rva0060BBD0
{
public:
	void bfmeBaseInitBG(AsciiStringBG_Rva0060BBD0 name);

	void *volatile m_bfmeVfptrBG;
	char m_bfmePadBG[0x9c];
	volatile char m_bfmeFlagBG;
	char m_bfmePadBBG[3];
	volatile int m_bfmeABG;
	volatile int m_bfmeBBG;
	volatile int m_bfmeCBG;
};

extern "C" void *rva0060bbd0Vftable[];

class Rva0060BBD0 : public BfmeNamedBG_Rva0060BBD0
{
public:
	Rva0060BBD0(AsciiStringBG_Rva0060BBD0 name);
};

Rva0060BBD0::Rva0060BBD0(AsciiStringBG_Rva0060BBD0 name)
{
	bfmeBaseInitBG(name);

	m_bfmeVfptrBG = rva0060bbd0Vftable;
}

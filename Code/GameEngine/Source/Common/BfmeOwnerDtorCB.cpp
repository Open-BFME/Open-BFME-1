// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a destructor at retail 0x00619BB0, 106 bytes.  Two bases: the
// array member goes first, then the second base restores its vftable, then the
// first base's string is released.  The null test before the vftable store is
// the this-adjustment to a base that does not sit at offset zero.

extern "C" void *bfmeVftableCB[];

class StringBaseNarrowCB
{
protected:
	~StringBaseNarrowCB(void);

	char *m_bfmeNarrowCB;
};

class AsciiStringCB : public StringBaseNarrowCB
{
public:
	~AsciiStringCB(void)
	{
	}
};

class BfmeElemCB
{
public:
	~BfmeElemCB(void);

	char m_bfmePadECB[0x44];
};

class BfmeFirstCB
{
public:
	~BfmeFirstCB(void)
	{
	}

	char m_bfmePadACB[0x3c];
	AsciiStringCB m_bfmeNameCB;
	char m_bfmePadBCB[0x18];
};

class BfmeSecondCB
{
public:
	~BfmeSecondCB(void)
	{
		m_bfmeVfptrCB = bfmeVftableCB;
	}

	void *volatile m_bfmeVfptrCB;
};

class BfmeOwnerCB : public BfmeFirstCB, public BfmeSecondCB
{
public:
	~BfmeOwnerCB(void);

	BfmeElemCB m_bfmeElemsCB[8];
};

BfmeOwnerCB::~BfmeOwnerCB(void)
{
}

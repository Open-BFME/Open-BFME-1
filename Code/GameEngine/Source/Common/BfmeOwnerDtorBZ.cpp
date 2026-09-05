// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a destructor at retail 0x00075D70, 106 bytes.  Two bases: the
// array member goes first, then the second base restores its vftable, then the
// first base's string is released.  The null test before the vftable store is
// the this-adjustment to a base that does not sit at offset zero.

extern "C" void *bfmeVftableBZ[];

class StringBaseNarrowBZ
{
protected:
	~StringBaseNarrowBZ(void);

	char *m_bfmeNarrowBZ;
};

class AsciiStringBZ : public StringBaseNarrowBZ
{
public:
	~AsciiStringBZ(void)
	{
	}
};

class BfmeElemBZ
{
public:
	~BfmeElemBZ(void);

	char m_bfmePadEBZ[0x44];
};

class BfmeFirstBZ
{
public:
	~BfmeFirstBZ(void)
	{
	}

	char m_bfmePadABZ[0x3c];
	AsciiStringBZ m_bfmeNameBZ;
	char m_bfmePadBBZ[0x18];
};

class BfmeSecondBZ
{
public:
	~BfmeSecondBZ(void)
	{
		m_bfmeVfptrBZ = bfmeVftableBZ;
	}

	void *volatile m_bfmeVfptrBZ;
};

class BfmeOwnerBZ : public BfmeFirstBZ, public BfmeSecondBZ
{
public:
	~BfmeOwnerBZ(void);

	BfmeElemBZ m_bfmeElemsBZ[8];
};

BfmeOwnerBZ::~BfmeOwnerBZ(void)
{
}

// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a destructor at retail 0x00099000, 87 bytes.  The eight-element
// array is torn down through the vector destructor iterator before the string,
// which is reverse declaration order.

class StringBaseNarrowBU
{
protected:
	~StringBaseNarrowBU(void);

	char *m_bfmeNarrowBU;
};

class AsciiStringBU : public StringBaseNarrowBU
{
public:
	~AsciiStringBU(void)
	{
	}
};

class BfmeElemBU
{
public:
	~BfmeElemBU(void);

	char m_bfmePadEBU[0x44];
};

class BfmeOwnerBU
{
public:
	~BfmeOwnerBU(void);

	char m_bfmePadABU[0x3c];
	AsciiStringBU m_bfmeNameBU;
	char m_bfmePadBBU[0x18];
	BfmeElemBU m_bfmeElemsBU[8];
};

BfmeOwnerBU::~BfmeOwnerBU(void)
{
}

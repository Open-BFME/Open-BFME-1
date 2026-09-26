// Three more tiny ones: an all-clear test over two fields, a destructor that
// unhooks itself from a global head, and a bit read out of a table.
//
// The complement in the bit read stays a byte operation only if the value is
// narrowed to a byte on both sides of it; written on the whole word MSVC
// complements the register.

class Gen_004891C0
{
public:
	int bfmeIsClear(void) const;

private:
	int m_bfmeHead[8];					// +0x00
	int m_bfmeFirst;					// +0x20
	int m_bfmeSecond;					// +0x24
};

// ?bfmeIsClear@Gen_004891C0@@QBEHXZ
int Gen_004891C0::bfmeIsClear(void) const
{
	if (m_bfmeFirst == 0 && m_bfmeSecond == 0)
		return 1;

	return 0;
}

class Gen_004902A0;

extern Gen_004902A0 *g_bfmeHeadCA;				// retail 0x012F3350

class Gen_004902A0
{
public:
	virtual ~Gen_004902A0(void);				// slot +0x00

	Gen_004902A0 *m_bfmeNext;				// +0x04
};

// ??1Gen_004902A0@@UAE@XZ
Gen_004902A0::~Gen_004902A0(void)
{
	if (g_bfmeHeadCA == this)
		g_bfmeHeadCA = m_bfmeNext;
}

class BfmeTableCA
{
public:
	int m_bfmeHead[3];					// +0x00
	unsigned int *m_bfmeBits;				// +0x0C
};

class Gen_005381A0
{
public:
	int bfmeBit(unsigned char index) const;

private:
	BfmeTableCA *m_bfmeTable;				// +0x00
};

// ?bfmeBit@Gen_005381A0@@QBEHE@Z
int Gen_005381A0::bfmeBit(unsigned char index) const
{
	BfmeTableCA *table = m_bfmeTable;

	unsigned int bits = table->m_bfmeBits[index] >> 3;

	bits = (unsigned char)~(unsigned char)bits;

	return bits & 1;
}

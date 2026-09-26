// Three more tiny ones: a scale that reads as one while a flag is up, a bit
// read out of another object, and a window test against the clock -- the two
// ends of the window are unsigned, and the answer is one only when both
// comparisons pass.

class BfmeClockBN
{
public:
	int m_bfmeHead[15];					// +0x00
	unsigned int m_bfmeStamp;				// +0x3C
};

extern BfmeClockBN *g_bfmeClockBN;				// retail 0x012F0898

class Gen_001BEC20
{
public:
	int bfmeScale(void) const;

private:
	int m_bfmeHead[197];					// +0x000
	int m_bfmeStored;					// +0x314
	char m_bfmeGap[0x90];					// +0x318
	unsigned char m_bfmeFixed;				// +0x3A8
};

// ?bfmeScale@Gen_001BEC20@@QBEHXZ
int Gen_001BEC20::bfmeScale(void) const
{
	if (m_bfmeFixed)
		return 1;

	return m_bfmeStored;
}

class BfmeThingBN
{
public:
	char m_bfmeHead[0x344];					// +0x000
	unsigned char m_bfmeBits;				// +0x344
};

// ?bfmeIsClear@@YGHPAVBfmeThingBN@@@Z
int __stdcall bfmeIsClear(BfmeThingBN *thing)
{
	return ~(thing->m_bfmeBits >> 3) & 1;
}

class Gen_001E1980
{
public:
	unsigned char bfmeIsWithin(void) const;

private:
	int m_bfmeHead[7];					// +0x00
	unsigned int m_bfmeStart;				// +0x1C
	int m_bfmeGap[1];					// +0x20
	unsigned int m_bfmeEnd;					// +0x24
};

// ?bfmeIsWithin@Gen_001E1980@@QBEEXZ
unsigned char Gen_001E1980::bfmeIsWithin(void) const
{
	unsigned int stamp = g_bfmeClockBN->m_bfmeStamp;

	if (stamp >= m_bfmeStart && stamp < m_bfmeEnd)
		return 1;

	return 0;
}

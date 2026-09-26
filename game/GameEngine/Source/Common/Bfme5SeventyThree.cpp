// Three more: a five-value setter, a comparator with a byte tiebreak, and a
// partial fill.

class Gen_0049D020
{
public:
	void bfmeSet(int first, int second, int third, int fourth, int fifth);

private:
	char m_bfmeHead[0x280];					// +0x000
	int m_bfmeFirst;					// +0x280
	int m_bfmeSecond;					// +0x284
	int m_bfmeThird;					// +0x288
	int m_bfmeFourth;					// +0x28C
	int m_bfmeFifth;					// +0x290
};

// ?bfmeSet@Gen_0049D020@@QAEXHHHHH@Z
void Gen_0049D020::bfmeSet(int first, int second, int third, int fourth, int fifth)
{
	m_bfmeFirst = first;
	m_bfmeSecond = second;
	m_bfmeThird = third;
	m_bfmeFourth = fourth;
	m_bfmeFifth = fifth;
}

class BfmeItemEK
{
public:
	int m_bfmeHead[12];					// +0x00
	int m_bfmeRank;						// +0x30
	int m_bfmeGap;						// +0x34
	char m_bfmeSpare;					// +0x38
	signed char m_bfmeTie;					// +0x39
};

// ?bfmeGreater@@YG_NPBVBfmeItemEK@@0@Z
bool __stdcall bfmeGreater(const BfmeItemEK *first, const BfmeItemEK *second)
{
	if (first->m_bfmeRank > second->m_bfmeRank)
		return true;

	if (first->m_bfmeRank < second->m_bfmeRank)
		return false;

	return first->m_bfmeTie < second->m_bfmeTie;
}

class BfmeItemEL
{
public:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeWidth;					// +0x0C
	int m_bfmeX;						// +0x10
	int m_bfmeY;						// +0x14
};

// ?bfmeFillPart@@YAXPAVBfmeItemEL@@0PBV1@@Z
void __cdecl bfmeFillPart(BfmeItemEL *first, BfmeItemEL *last, const BfmeItemEL *value)
{
	while (first != last)
	{
		first->m_bfmeA = value->m_bfmeA;
		first->m_bfmeC = value->m_bfmeC;
		first->m_bfmeWidth = value->m_bfmeWidth;
		first->m_bfmeX = value->m_bfmeX;
		*(unsigned char *)&first->m_bfmeY = *(const unsigned char *)&value->m_bfmeY;

		++first;
	}
}

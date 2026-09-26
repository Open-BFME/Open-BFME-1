// ?bfmeLessZQ@BfmeKeyZQ@@QBEDPBV1@@Z
// Retail 0x0052E940 is the member form of the landed 0x0052F070 key
// comparator. Both records hold a flag at +0 and an AsciiString at +4.
// cl: /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class BfmeKeyZQ
{
public:
	char bfmeLessZQ(const BfmeKeyZQ *other) const;

	char m_bfmeFlagZQ;
	unsigned char m_bfmePadZQ[3];
	AsciiString m_bfmeNameZQ;
};

char BfmeKeyZQ::bfmeLessZQ(const BfmeKeyZQ *other) const
{
	char flag = m_bfmeFlagZQ;

	if ((other->m_bfmeFlagZQ == 0) ^ (flag == 0))
		return flag;

	int comparison = m_bfmeNameZQ.compareNoCase(other->m_bfmeNameZQ);

	return (char)(0 | (comparison < 0));
}

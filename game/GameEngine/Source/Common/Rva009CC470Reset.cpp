// cl: /O2 /Ob0
//
// The two dwords at +0 and +4 are AsciiStrings: retail releases each with
// StringBase<char>::releaseBuffer at 0x00887940, which the shared header's
// inline clear() calls.  The previous placeholder declared a local
// Rva0036CA00Str::clear that nothing defines.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva009CC470
{
	AsciiString m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;

public:
	void reset();
};

void Rva009CC470::reset()
{
	m_00.StringBase<char>::clear();
	m_04.StringBase<char>::clear();
	m_08 = 0;
	m_0C = 0;
}
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the bounds-checked slot accessor at retail 0x0048DE20, 92 bytes.
// Out-of-range lookups return a function-local static, whose guard bit and
// atexit registration retail carries inline. The slots are AsciiString:
// the atexit helper calls StringBase<char>::releaseBuffer (0x00887940).

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Gen_0048DE20
{
public:
	AsciiString *bfmeAtYJ(int index);

	char m_bfmePad0000[0x303C];				// +0x0000
	int m_bfmeCount;					// +0x303C
	AsciiString *m_bfmeSlots;				// +0x3040
};

// ?bfmeAtYJ@Gen_0048DE20@@QAEPAVAsciiString@@H@Z
AsciiString *Gen_0048DE20::bfmeAtYJ(int index)
{
	if (m_bfmeSlots != 0 && index >= 0 && index < m_bfmeCount)
		return &m_bfmeSlots[index];

	static AsciiString s_bfmeEmptyYJ;

	return &s_bfmeEmptyYJ;
}

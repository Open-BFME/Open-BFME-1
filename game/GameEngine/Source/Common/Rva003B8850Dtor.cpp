// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: destructor of a 12-byte record of three AsciiStrings. Retail
// 0x003B8850, 121 bytes; each AsciiString destructor is the inline
// releaseBuffer call (0x00887940), six in all.

#include "ascii_string.h"

class Rva003B8850
{
public:
	~Rva003B8850();

private:
	AsciiString m_a;
	AsciiString m_b;
	AsciiString m_c;
};

Rva003B8850::~Rva003B8850()
{
	m_a.~AsciiString();
	m_b.~AsciiString();
	m_c.~AsciiString();
}

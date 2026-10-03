// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: StringInfo dtor. AsciiString @+0 then UnicodeString @+4.

#include "ascii_string.h"

#include "unicode_string.h"

class StringInfo
{
public:
	~StringInfo();

private:
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

// ??1StringInfo@@QAE@XZ
StringInfo::~StringInfo()
{
}

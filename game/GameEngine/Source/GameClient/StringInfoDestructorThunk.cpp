// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: StringInfo dtor. AsciiString @+0 then UnicodeString @+4.

#include "ascii_string.h"

#include "unicode_string.h"

// Retail releases the UnicodeString member by calling
// StringBase<unsigned short>::releaseBuffer (0x008881D0) directly; the
// header's UnicodeString declares an out-of-line ~UnicodeString (0x0005EEA0).
// This member view keeps the layout and inlines the release.
struct StringInfoUnicodeText
{
	~StringInfoUnicodeText()
	{
		((StringBase<unsigned short> *)this)->clear();
	}

	void *m_data;
};

class StringInfo
{
public:
	~StringInfo();

private:
	AsciiString m_ascii;
	StringInfoUnicodeText m_unicode;
};

// ??1StringInfo@@QAE@XZ
StringInfo::~StringInfo()
{
}

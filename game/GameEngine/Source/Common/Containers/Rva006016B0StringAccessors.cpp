// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#include "unicode_string.h"

// Retail returns the UnicodeString through StringBase<wchar_t>'s copy body.
// Make the canonical forwarding body visible here so this accessor emits that
// direct copy call rather than an out-of-line UnicodeString copy call.
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&other);
}

class Rva006016B0
{
public:
	AsciiString getString();

private:
	unsigned char m_beforeString[0x48];
	AsciiString m_string;
};

class Rva006ED320
{
public:
	UnicodeString getString();

private:
	unsigned char m_beforeString[4];
	UnicodeString m_string;
};

AsciiString Rva006016B0::getString()
{
	return m_string;
}

UnicodeString Rva006ED320::getString()
{
	return m_string;
}

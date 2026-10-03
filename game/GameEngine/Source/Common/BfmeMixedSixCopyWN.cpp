// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the mixed six-member copy constructor at retail 0x004E9FD0,
// 148 bytes: a word, three narrow strings, a word and two wide strings.

#include "ascii_string.h"
#include "unicode_string.h"

// The canonical header declares these forwarders out of line. Keep their
// retail inline bodies visible here so calls go directly to StringBase at
// 0x00888400 (copy) and 0x008881D0 (release), as they do for AsciiString.
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&other);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

class Gen_004E9FD0
{
public:
	Gen_004E9FD0(const Gen_004E9FD0 &other);

	int m_bfmeKind;						// +0x00
	AsciiString m_bfmeFirst;					// +0x04
	AsciiString m_bfmeSecond;					// +0x08
	AsciiString m_bfmeThird;					// +0x0C
	int m_bfmeCount;					// +0x10
	UnicodeString m_bfmeText;					// +0x14
	UnicodeString m_bfmeHint;					// +0x18
};

// ??0Gen_004E9FD0@@QAE@ABV0@@Z
Gen_004E9FD0::Gen_004E9FD0(const Gen_004E9FD0 &other)
	: m_bfmeKind(other.m_bfmeKind),
	  m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeCount(other.m_bfmeCount),
	  m_bfmeText(other.m_bfmeText),
	  m_bfmeHint(other.m_bfmeHint)
{
}

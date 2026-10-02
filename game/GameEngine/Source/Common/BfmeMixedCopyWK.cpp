// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the mixed-string copy constructor at retail 0x000F9C60,
// 115 bytes: four words and a flag copied inline, then a wide string and a
// narrow one.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// Retail calls the StringBase copy/release bodies through inline string
// forwarders; keep the wide forwarders visible just like AsciiString's.
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&other);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

class Gen_000F9C60
{
public:
	Gen_000F9C60(const Gen_000F9C60 &other);

	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
	bool m_bfmeFlag;					// +0x10
	UnicodeString m_bfmeText;					// +0x14
	AsciiString m_bfmeName;					// +0x18
};

// ??0Gen_000F9C60@@QAE@ABV0@@Z
Gen_000F9C60::Gen_000F9C60(const Gen_000F9C60 &other)
	: m_bfmeA(other.m_bfmeA),
	  m_bfmeB(other.m_bfmeB),
	  m_bfmeC(other.m_bfmeC),
	  m_bfmeD(other.m_bfmeD),
	  m_bfmeFlag(other.m_bfmeFlag),
	  m_bfmeText(other.m_bfmeText),
	  m_bfmeName(other.m_bfmeName)
{
}

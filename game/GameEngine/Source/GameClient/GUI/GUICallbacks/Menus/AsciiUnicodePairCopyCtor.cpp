// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: compiler-generated copy ctor of a 0x20-byte record whose first
// two members are AsciiString then UnicodeString, retail 0x004F97B0, 117 bytes.
// The frame exists so the char string is destroyed if the wide copy throws;
// the six dwords after that are POD and copied after both strings exist.

#include "../../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "../../../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


struct AsciiUnicodePair
{
	AsciiString m_ascii;
	UnicodeString m_unicode;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;

	AsciiUnicodePair(const AsciiUnicodePair &other);
};

AsciiUnicodePair::AsciiUnicodePair(const AsciiUnicodePair &other)
	: m_ascii(other.m_ascii)
	, m_unicode(other.m_unicode)
	, m_a(other.m_a)
	, m_b(other.m_b)
	, m_c(other.m_c)
	, m_d(other.m_d)
	, m_e(other.m_e)
	, m_f(other.m_f)
{
}

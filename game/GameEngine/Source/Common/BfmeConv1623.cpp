// Open-BFME5 conversions.

// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

class BfmeEntVTV
{
public:
	BfmeEntVTV(const BfmeEntVTV &other);
	AsciiString m_bfme00;
	int m_bfme04;
	UnicodeString m_bfme08;
};

BfmeEntVTV::BfmeEntVTV(const BfmeEntVTV &other)
	: m_bfme00(other.m_bfme00), m_bfme04(other.m_bfme04), m_bfme08(other.m_bfme08)
{
}

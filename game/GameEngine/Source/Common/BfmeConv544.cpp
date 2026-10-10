// Retail 0x001DE800 (36 bytes) copy-constructs its leading AsciiString from
// the argument (StringBase<char> copy constructor, 0x00887B60) and zeroes the
// five words after it. Owner unknown; the class keeps the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva001DE800
{
public:
	Rva001DE800(const AsciiString &name);
	AsciiString m_name;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
};

Rva001DE800::Rva001DE800(const AsciiString &name)
	: m_name(name), m_a(0), m_b(0), m_c(0), m_d(0), m_e(0)
{
}

// Retail 0x000BF090 (40 bytes) builds { AsciiString, three words }: the name
// through StringBase<char>'s copy constructor (0x00887B60), then a copy of a
// three-word value. Owner unknown; the types keep the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva000BF090Value
{
	int m_a;
	int m_b;
	int m_c;
};

class Rva000BF090
{
public:
	Rva000BF090(const AsciiString &name, const Rva000BF090Value &value);
	AsciiString m_name;
	int m_a;
	int m_b;
	int m_c;
};

Rva000BF090::Rva000BF090(const AsciiString &name, const Rva000BF090Value &value)
	: m_name(name), m_a(value.m_a), m_b(value.m_b), m_c(value.m_c)
{
}

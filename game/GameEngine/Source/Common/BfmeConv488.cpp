// Retail 0x00094790 (26 bytes) constructs an { AsciiString, pointer } pair in
// place: StringBase<char>'s copy constructor (0x00887B60) builds the name, then
// the second word is stored. Owner unknown; the class keeps the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva00094790
{
public:
	Rva00094790(const AsciiString &name, void *value);
	AsciiString m_name;
	void *m_value;
};

Rva00094790::Rva00094790(const AsciiString &name, void *value)
	: m_name(name), m_value(value)
{
}

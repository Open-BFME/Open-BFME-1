// Retail 0x00469AD0 (41 bytes) builds { AsciiString, counted reference, word }:
// the name through StringBase<char>'s copy constructor (0x00887B60), then a
// copy of a reference whose count at +4 is bumped when non-null. Owner
// unknown; the types keep the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva00469AD0Ref
{
	unsigned char m_head[4];
	int m_count;
};

struct Rva00469AD0Value
{
	Rva00469AD0Value(const Rva00469AD0Value &src)
		: m_ref(src.m_ref)
	{
		if (m_ref != 0)
			++m_ref->m_count;
		m_val = src.m_val;
	}
	Rva00469AD0Ref *m_ref;
	void *m_val;
};

class Rva00469AD0
{
public:
	Rva00469AD0(const AsciiString &name, const Rva00469AD0Value &value);
	AsciiString m_name;
	Rva00469AD0Value m_value;
};

Rva00469AD0::Rva00469AD0(const AsciiString &name, const Rva00469AD0Value &value)
	: m_name(name), m_value(value)
{
}

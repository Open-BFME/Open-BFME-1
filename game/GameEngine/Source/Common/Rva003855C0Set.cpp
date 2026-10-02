// cl: /O2 /Ob0
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva003855C0
{
	char m_00[0x174];
	StringBase<char> m_174;
	int m_178;
	int m_17C;

public:
	void reset();
};

void Rva003855C0::reset()
{
	m_174.set(AsciiString::TheEmptyString);
	m_178 = 0;
	m_17C = 0;
}

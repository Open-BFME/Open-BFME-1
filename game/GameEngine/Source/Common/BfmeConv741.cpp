// Retail 0x001A87C0 returns, by value, the AsciiString at index `index` of an
// eight-entry array at +0x54: the hidden-return copy is StringBase<char>'s
// copy constructor (0x00887B60). Owner unknown; the class keeps the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva001A87C0
{
public:
	AsciiString rva001A87C0(int index);
	unsigned char m_head[0x54];
	AsciiString m_names[8];
};

AsciiString Rva001A87C0::rva001A87C0(int index)
{
	return m_names[index];
}

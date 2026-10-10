// Retail 0x00190560 returns, by value, the AsciiString at index `index` of an
// eight-entry array at +0x48: the hidden-return copy is StringBase<char>'s
// copy constructor (0x00887B60). Owner unknown; the class keeps the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva00190560
{
public:
	AsciiString rva00190560(int index);
	unsigned char m_head[0x48];
	AsciiString m_names[8];
};

AsciiString Rva00190560::rva00190560(int index)
{
	return m_names[index];
}

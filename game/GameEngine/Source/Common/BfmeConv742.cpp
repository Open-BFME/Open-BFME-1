// Retail 0x0029C440 returns, by value, the AsciiString at index `index` of an
// eight-entry array at +0x38: the hidden-return copy is StringBase<char>'s
// copy constructor (0x00887B60). Owner unknown; the class keeps the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva0029C440
{
public:
	AsciiString rva0029C440(int index);
	unsigned char m_head[0x38];
	AsciiString m_names[8];
};

AsciiString Rva0029C440::rva0029C440(int index)
{
	return m_names[index];
}

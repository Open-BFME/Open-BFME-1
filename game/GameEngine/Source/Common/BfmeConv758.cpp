// Retail 0x0058D740 returns, by value, the AsciiString at +0x84 of the object
// its +4 pointer names: the hidden-return copy is StringBase<char>'s copy
// constructor (0x00887B60). Owner unknown; the types keep the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva0058D740Data
{
	unsigned char m_head[0x84];
	AsciiString m_name;
};

class Rva0058D740
{
public:
	AsciiString rva0058D740();
	unsigned char m_head[4];
	Rva0058D740Data *m_data;
};

AsciiString Rva0058D740::rva0058D740()
{
	return m_data->m_name;
}

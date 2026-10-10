// Retail 0x0020E820 returns, by value, the AsciiString at +0x2C of the object
// stored 0xC bytes before `this` (the method runs on a subobject): the
// hidden-return copy is StringBase<char>'s copy constructor (0x00887B60).
// Owner unknown; the types keep the address.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva0020E820Owner
{
	unsigned char m_head[0x2c];
	AsciiString m_name;
};

struct Rva0020E820
{
	AsciiString rva0020E820();
};

AsciiString Rva0020E820::rva0020E820()
{
	Rva0020E820Owner *owner = *(Rva0020E820Owner **)((char *)this - 0xc);
	return owner->m_name;
}

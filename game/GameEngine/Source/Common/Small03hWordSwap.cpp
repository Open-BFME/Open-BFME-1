// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x009CC2C0 is a 38-byte word shuffle over the dword at this+0:
// ((v & 0xFF00) + (v << 16)) << 8 plus the (v >> 16) & 0xFF byte at bit 8
// plus v >> 24. The split-hi spelling (hi = v >> 16 masked and shifted in
// its own statements) is what emits retail's xor-edx + spill + mov-dh tail;
// the folded single-expression spelling mis-allocates registers. Twins
// with 0x009CC2F0 (+4 load) below. Neighbours: BfmeOwnVTUCtor,
// Rva009CC330NameEnd. IDENTITY IS NOT RECOVERED: both owners keep their
// address tokens (one-identity rule).
class Rva009CC2C0Box
{
public:
	unsigned int m_word;
	unsigned int swap() const;
};
unsigned int Rva009CC2C0Box::swap() const
{
	unsigned int v = m_word;
	unsigned int a = (v & 0xFF00) + (v << 16);
	a <<= 8;
	unsigned int hi = v >> 16;
	hi &= 0xFF;
	hi <<= 8;
	return a + hi + (v >> 24);
}

class Rva009CC2F0Box
{
public:
	unsigned char m_pad[4];
	unsigned int m_word;
	unsigned int swap() const;
};
unsigned int Rva009CC2F0Box::swap() const
{
	unsigned int v = m_word;
	unsigned int a = (v & 0xFF00) + (v << 16);
	a <<= 8;
	unsigned int hi = v >> 16;
	hi &= 0xFF;
	hi <<= 8;
	return a + hi + (v >> 24);
}

// Retail 0x009CC290 is the cdecl free-function twin of the same word
// shuffle (35 B, ret with no this-load or push). Same split-hi spelling.
unsigned int __cdecl Rva009CC290Swap(unsigned int v)
{
	unsigned int a = (v & 0xFF00) + (v << 16);
	a <<= 8;
	unsigned int hi = v >> 16;
	hi &= 0xFF;
	hi <<= 8;
	return a + hi + (v >> 24);
}

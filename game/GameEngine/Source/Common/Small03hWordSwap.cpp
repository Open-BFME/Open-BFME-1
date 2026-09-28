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

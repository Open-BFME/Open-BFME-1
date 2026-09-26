// Consume two dwords from a four-byte-aligned instruction stream.
struct BfmeReadCursor8C5A20
{
	unsigned char *m_next;
};

struct BfmeReadPair8C5A20
{
	unsigned char m_reserved[0x5c];
	unsigned m_first;
	unsigned m_second;
};

void __cdecl bfmeReadAlignedPair8C5A20(BfmeReadPair8C5A20 *destination, BfmeReadCursor8C5A20 *cursor)
{
	unsigned *words = (unsigned *)(((unsigned)cursor->m_next + 3) & ~3u);
	cursor->m_next = (unsigned char *)(words + 2);
	destination->m_first = words[0];
	destination->m_second = words[1];
}

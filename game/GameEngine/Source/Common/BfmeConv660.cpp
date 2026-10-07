struct BfmePairCXA
{
	void *m_bfmeA;
	void *m_bfmeB;
};

// The per-element call (ILT 0x000391E9 -> 0x00260910) is the matched
// STLport unguarded linear insert GenInsert00260910 over an 8-byte element.
struct Gen8ByteElement00260910
{
	int m_00;
	int m_04;
};
typedef bool (*Gen8ByteLess00260910)(const Gen8ByteElement00260910 &, const Gen8ByteElement00260910 &);
void GenInsert00260910(Gen8ByteElement00260910 *last, Gen8ByteElement00260910 value, Gen8ByteLess00260910 less);

void bfmeGoCXA(BfmePairCXA *begin, BfmePairCXA *end, void *spare, void *arg)
{
	while (begin != end)
	{
		GenInsert00260910((Gen8ByteElement00260910 *)begin, *(Gen8ByteElement00260910 *)begin, (Gen8ByteLess00260910)arg);
		++begin;
	}
}

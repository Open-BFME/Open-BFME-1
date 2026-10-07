struct BfmePairCXB
{
	void *m_bfmeA;
	void *m_bfmeB;
};

// Retail calls ILT 0x000391E9 -> 0x00260910, the matched STLport unguarded
// linear insert (Rva00260910UnguardedLinearInsert.cpp).
struct Gen8ByteElement00260910
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess00260910 )(
	const Gen8ByteElement00260910 &, const Gen8ByteElement00260910 & );

void GenInsert00260910( Gen8ByteElement00260910 *last,
	Gen8ByteElement00260910 value, Gen8ByteElementLess00260910 comp );

void bfmeGoCXB(BfmePairCXB *begin, BfmePairCXB *end, void *arg)
{
	while (begin != end)
	{
		GenInsert00260910((Gen8ByteElement00260910 *)begin,
			*(Gen8ByteElement00260910 *)begin, (Gen8ByteElementLess00260910)arg);
		++begin;
	}
}

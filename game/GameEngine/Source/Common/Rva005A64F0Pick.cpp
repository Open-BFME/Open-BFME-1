// cl: /O2 /Ob0

struct Rva005A64F0Rec
{
	char pad[0x10];
	unsigned m_10;
	unsigned char m_14;
};

Rva005A64F0Rec *Rva005A64F0Pick(Rva005A64F0Rec *a, Rva005A64F0Rec *b)
{
	if (!a || (a->m_14 & 1))
	{
		if (!b || (b->m_14 & 1))
			return 0;
		return b;
	}
	if (!b || (b->m_14 & 1))
		return a;
	if (a->m_10 > b->m_10)
		return a;
	return b;
}

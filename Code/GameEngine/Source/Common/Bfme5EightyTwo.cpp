// Two more: a bit written either way, and a count of the marked entries.

void bfmeSetBit(unsigned int *words, unsigned int index, int on)
{
	if (on)
		words[index >> 5] |= (1U << (index & 31));
	else
		words[index >> 5] &= ~(1U << (index & 31));
}

class BfmeThingGK
{
public:
	int m_bfmeGap[12];							// +0x00
	int m_bfmeIndex;							// +0x30
	int m_bfmeGap2[2];							// +0x34
	BfmeThingGK *m_bfmeNext;					// +0x3c
};

class Gen_0029D2E0
{
public:
	int bfmeCountMarked(const unsigned int *words) const;
private:
	int m_bfmeGap[2];							// +0x00
	BfmeThingGK *m_bfmeHead;					// +0x08
};

int Gen_0029D2E0::bfmeCountMarked(const unsigned int *words) const
{
	int count = 0;
	BfmeThingGK *thing = m_bfmeHead;
	while (thing != 0)
	{
		unsigned int index = (unsigned int)thing->m_bfmeIndex;
		if (thing->m_bfmeIndex != -1 && (words[index >> 5] & (1U << (index & 31))) != 0)
			++count;
		thing = thing->m_bfmeNext;
	}
	return count;
}

// ?bfmeLinearInsertFloatAscending@@YAXPAUBfmeSortPair@@U1@@Z
// partial score=0.55 date=2026-09-02
// cl: /O2 /Ob2

struct BfmeSortPair
{
	unsigned int m_value;
	float m_key;
};

void bfmeLinearInsertFloatAscending(BfmeSortPair *last, BfmeSortPair pending)
{
	BfmeSortPair *previous = (BfmeSortPair *)((unsigned int)last - sizeof(BfmeSortPair));

bfme_check_previous:
	if (pending.m_key < previous->m_key)
	{
		*last = *previous;
		last = previous;
		--previous;
		goto bfme_check_previous;
	}

	*last = pending;
}

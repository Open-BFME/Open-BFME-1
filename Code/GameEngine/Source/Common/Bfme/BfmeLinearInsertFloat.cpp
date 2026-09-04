// cl: /O2 /Ob2

struct BfmeSortPair
{
	unsigned int m_value;
	float m_key;
};

struct BfmeSortCompare
{
	bool operator()(const BfmeSortPair &left, const BfmeSortPair &right) const
	{
		return left.m_key < right.m_key;
	}
};

struct BfmeSortCompareDescending
{
	bool operator()(const BfmeSortPair &left, const BfmeSortPair &right) const
	{
		return left.m_key > right.m_key;
	}
};

void bfmeLinearInsertFloatAscending(BfmeSortPair *last, BfmeSortPair pending)
{
	BfmeSortPair *previous = last;
	--previous;
	BfmeSortCompare compare;
	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}
	*last = pending;
}

// ?bfmeLinearInsertFloatDescending@@YAXPAUBfmeSortPair@@U1@@Z
void bfmeLinearInsertFloatDescending(BfmeSortPair *last, BfmeSortPair pending)
{
	BfmeSortPair *previous = last;
	--previous;
	BfmeSortCompareDescending compare;
	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}
	*last = pending;
}

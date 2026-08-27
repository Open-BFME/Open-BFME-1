// The unguarded arm of the ranked linear insertion sort.  The comparator is
// specialized here: records rank by the word at +0x30 and break ties with the
// byte at +0x39.

class BfmeRecAT
{
public:
	int m_bfmeHead[12];
	int m_bfmeRank;
	char m_bfmePad[5];
	char m_bfmeFlag;
};

class BfmeCompAT
{
public:
	bool operator()(const BfmeRecAT *left, const BfmeRecAT *right) const
	{
		int rightRank = right->m_bfmeRank;
		int leftRank = left->m_bfmeRank;

		if (leftRank > rightRank)
			return true;

		if (leftRank < rightRank)
			return false;

		return left->m_bfmeFlag < right->m_bfmeFlag;
	}

	int m_bfmeState;
};

// ?bfmeUnguardedInsertAT@@YAXPAPAVBfmeRecAT@@PAV1@VBfmeCompAT@@@Z
void __cdecl bfmeUnguardedInsertAT(BfmeRecAT **last, BfmeRecAT *value, BfmeCompAT comp)
{
	BfmeRecAT **next = last - 1;

	while (comp(value, *next))
	{
		*last = *next;

		last = next;
		--next;
	}

	*last = value;
}

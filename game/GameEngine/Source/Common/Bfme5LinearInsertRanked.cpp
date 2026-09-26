// A linear insert whose comparator is inlined: it ranks two records by a word
// and breaks the tie with a byte.
//
// The three-way shape is visible in the branches -- greater takes the front
// arm, less takes the unguarded one, and only equality reaches the byte
// compare -- while the comparator object itself is still passed on by value to
// the out-of-line arm, because it is a parameter even though it carries
// nothing the comparison reads.
//
// The two ranks have to be read into locals, the right one first: written as a
// direct comparison of the two members the operand order and the registers
// move together, and one of them always comes out the wrong way round.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeRecAT
{
public:
	int m_bfmeHead[12];					// +0x00
	int m_bfmeRank;						// +0x30
	char m_bfmePad[5];					// +0x34
	char m_bfmeFlag;					// +0x39
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

	int m_bfmeState;					// +0x00
};

inline BfmeRecAT **bfmeCopyBackward(BfmeRecAT **first, BfmeRecAT **last, BfmeRecAT **result)
{
	int bytes = (char *)last - (char *)first;

	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);

	return (BfmeRecAT **)((char *)result - bytes);
}

void __cdecl bfmeUnguardedInsertAT(BfmeRecAT **last, BfmeRecAT *value, BfmeCompAT comp);
								// retail thunk 0x0001F1FE -> 0x0041F1FE

// ?bfmeLinearInsertAT@@YAXPAPAVBfmeRecAT@@0PAV1@VBfmeCompAT@@@Z
void __cdecl bfmeLinearInsertAT(BfmeRecAT **first, BfmeRecAT **last, BfmeRecAT *value, BfmeCompAT comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAT(last, value, comp);
	}
}

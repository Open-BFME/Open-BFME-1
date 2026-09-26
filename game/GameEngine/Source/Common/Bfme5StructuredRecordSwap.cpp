// Swaps the independently stored pieces of a 28-byte record.  The leading
// and offset-20 members use their own non-member swap helpers.

struct BfmeStructuredSwapPart
{
	int m_value;
};

class BfmeStructuredSwapRecord;

void __cdecl bfmeSwapStructuredHead(
	BfmeStructuredSwapRecord *left,
	BfmeStructuredSwapRecord *right);
void __cdecl bfmeSwapStructuredPart(
	BfmeStructuredSwapPart *left,
	BfmeStructuredSwapPart *right);

inline void bfmeSwapStructuredWord(int &left, int &right)
{
	int value = left;
	left = right;
	right = value;
}

inline void bfmeSwapStructuredShort(short &left, short &right)
{
	short value = left;
	left = right;
	right = value;
}

class BfmeStructuredSwapRecord
{
public:
	void bfmeSwap(BfmeStructuredSwapRecord &other);

private:
	int m_head;
	int m_word04;
	int m_gap08;
	int m_word0c;
	int m_word10;
	BfmeStructuredSwapPart m_part14;
	short m_word18;
	short m_word1a;
};

// ?bfmeSwap@BfmeStructuredSwapRecord@@QAEXAAV1@@Z
void BfmeStructuredSwapRecord::bfmeSwap(BfmeStructuredSwapRecord &other)
{
	bfmeSwapStructuredHead(this, &other);

	bfmeSwapStructuredWord(m_word04, other.m_word04);
	bfmeSwapStructuredWord(m_word0c, other.m_word0c);
	bfmeSwapStructuredWord(m_word10, other.m_word10);

	bfmeSwapStructuredPart(&m_part14, &other.m_part14);

	bfmeSwapStructuredShort(m_word18, other.m_word18);
	bfmeSwapStructuredShort(m_word1a, other.m_word1a);
}

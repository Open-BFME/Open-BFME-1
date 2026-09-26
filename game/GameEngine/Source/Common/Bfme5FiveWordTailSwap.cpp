// Swap a record's five scalar words, then delegate the non-trivial tail.

struct BfmeSwapTailCJ;

void __cdecl bfmeSwapTailCJ(BfmeSwapTailCJ *first, BfmeSwapTailCJ *second);

inline void bfmeSwapWordCJ(int &first, int &second)
{
	int value = first;
	first = second;
	second = value;
}

class BfmeRecordCJ
{
public:
	void bfmeSwap(BfmeRecordCJ &other);

private:
	int m_words[5];
	BfmeSwapTailCJ *m_tailStorage;
};

// ?bfmeSwap@BfmeRecordCJ@@QAEXAAV1@@Z
void BfmeRecordCJ::bfmeSwap(BfmeRecordCJ &other)
{
	bfmeSwapWordCJ(m_words[0], other.m_words[0]);
	bfmeSwapWordCJ(m_words[1], other.m_words[1]);
	bfmeSwapWordCJ(m_words[2], other.m_words[2]);
	bfmeSwapWordCJ(m_words[3], other.m_words[3]);
	bfmeSwapWordCJ(m_words[4], other.m_words[4]);

	bfmeSwapTailCJ(reinterpret_cast<BfmeSwapTailCJ *>(m_words + 5),
		reinterpret_cast<BfmeSwapTailCJ *>(other.m_words + 5));
}

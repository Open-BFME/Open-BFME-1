// Constructs a returned two-member record from two non-trivial four-byte
// values.  The EH state protects the first member while the second is copied.

class BfmeWordEL
{
public:
	BfmeWordEL(const BfmeWordEL &other);
	~BfmeWordEL(void);

private:
	int m_value;
};

struct BfmePairEL
{
	BfmePairEL(const BfmeWordEL &firstValue, const BfmeWordEL &secondValue)
		: first(firstValue), second(secondValue)
	{
	}

	BfmeWordEL first;
	BfmeWordEL second;
};

// ?bfmeMakePairEL@@YA?AUBfmePairEL@@ABVBfmeWordEL@@0@Z
BfmePairEL __cdecl bfmeMakePairEL(
	const BfmeWordEL &first,
	const BfmeWordEL &second)
{
	return BfmePairEL(first, second);
}

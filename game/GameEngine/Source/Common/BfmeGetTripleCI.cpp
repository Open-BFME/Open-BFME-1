// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a by-value getter at retail 0x006E1C60, 24 bytes.  Three fields
// go straight into the caller's return slot; the two floats interleave with
// the integer because the x87 stack is filled before it is drained.

struct BfmeTripleCI
{
	BfmeTripleCI(int index, float first, float second)
		: m_bfmeIndexCI(index), m_bfmeFirstCI(first), m_bfmeSecondCI(second)
	{
	}

	int m_bfmeIndexCI;
	float m_bfmeFirstCI;
	float m_bfmeSecondCI;
};

class BfmeOwnerCI
{
public:
	BfmeTripleCI bfmeGetCI(void);

	char m_bfmePadCI[0x6c];
	int m_bfmeIndexCI;
	float m_bfmeFirstCI;
	float m_bfmeSecondCI;
};

BfmeTripleCI BfmeOwnerCI::bfmeGetCI(void)
{
	return BfmeTripleCI(m_bfmeIndexCI, m_bfmeFirstCI, m_bfmeSecondCI);
}

// Three more: the three whole-set operations on a ten word mask.

class BfmeBitsMA
{
public:
	void bfmeAndWith(const BfmeBitsMA *other);
	void bfmeOrWith(const BfmeBitsMA *other);
	void bfmeInvert(void);
private:
	unsigned int m_bfmeWords[10];
};

void BfmeBitsMA::bfmeAndWith(const BfmeBitsMA *other)
{
	m_bfmeWords[0] &= other->m_bfmeWords[0];
	m_bfmeWords[1] &= other->m_bfmeWords[1];
	m_bfmeWords[2] &= other->m_bfmeWords[2];
	m_bfmeWords[3] &= other->m_bfmeWords[3];
	m_bfmeWords[4] &= other->m_bfmeWords[4];
	m_bfmeWords[5] &= other->m_bfmeWords[5];
	m_bfmeWords[6] &= other->m_bfmeWords[6];
	m_bfmeWords[7] &= other->m_bfmeWords[7];
	m_bfmeWords[8] &= other->m_bfmeWords[8];
	m_bfmeWords[9] &= other->m_bfmeWords[9];
}

void BfmeBitsMA::bfmeOrWith(const BfmeBitsMA *other)
{
	m_bfmeWords[0] |= other->m_bfmeWords[0];
	m_bfmeWords[1] |= other->m_bfmeWords[1];
	m_bfmeWords[2] |= other->m_bfmeWords[2];
	m_bfmeWords[3] |= other->m_bfmeWords[3];
	m_bfmeWords[4] |= other->m_bfmeWords[4];
	m_bfmeWords[5] |= other->m_bfmeWords[5];
	m_bfmeWords[6] |= other->m_bfmeWords[6];
	m_bfmeWords[7] |= other->m_bfmeWords[7];
	m_bfmeWords[8] |= other->m_bfmeWords[8];
	m_bfmeWords[9] |= other->m_bfmeWords[9];
}

void BfmeBitsMA::bfmeInvert(void)
{
	m_bfmeWords[0] = ~m_bfmeWords[0];
	m_bfmeWords[1] = ~m_bfmeWords[1];
	m_bfmeWords[2] = ~m_bfmeWords[2];
	m_bfmeWords[3] = ~m_bfmeWords[3];
	m_bfmeWords[4] = ~m_bfmeWords[4];
	m_bfmeWords[5] = ~m_bfmeWords[5];
	m_bfmeWords[6] = ~m_bfmeWords[6];
	m_bfmeWords[7] = ~m_bfmeWords[7];
	m_bfmeWords[8] = ~m_bfmeWords[8];
	m_bfmeWords[9] = ~m_bfmeWords[9];
}

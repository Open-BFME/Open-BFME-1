// ?bfmeTestYN@BfmeOwnerYN@@QAEDPAUBfmeMaskYN@@@Z
// Open-BFME5 conversions.

struct BfmeSubYN
{
	unsigned char m_bfmeBytesYN[4];
};

struct BfmeMaskYN
{
	char bfmeMatchYN(BfmeSubYN *sub);
	char bfmeAnyYN(BfmeMaskYN *other);

	int m_bfmeAYN;
	int m_bfmeBYN;
	int m_bfmeCYN;
};

class BfmeOwnerYN
{
public:
	char bfmeTestYN(BfmeMaskYN *other);

	unsigned char m_bfmeHeadYN[4];
	BfmeMaskYN m_bfmeMaskYN;
	BfmeSubYN m_bfmeSubYN;
};

char BfmeOwnerYN::bfmeTestYN(BfmeMaskYN *other)
{
	if (other->bfmeMatchYN(&m_bfmeSubYN) != 0)
		return 0;

	BfmeMaskYN masked = *other;

	masked.m_bfmeAYN &= m_bfmeMaskYN.m_bfmeAYN;
	masked.m_bfmeBYN &= m_bfmeMaskYN.m_bfmeBYN;
	masked.m_bfmeCYN &= m_bfmeMaskYN.m_bfmeCYN;

	return m_bfmeMaskYN.bfmeAnyYN(&masked) == 0;
}

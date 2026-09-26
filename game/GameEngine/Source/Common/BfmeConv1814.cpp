struct BfmeInnerSX
{
	unsigned char m_bfmeRawSX[4];
};

struct BfmeKeySX
{
	char m_bfmeASX;
	char m_bfmeBSX;
	char m_bfmeCSX;
	char m_bfmePadSX;
	int m_bfmeDSX;
	BfmeInnerSX m_bfmeInnerSX;
};

bool __cdecl bfmeSameSX(const BfmeInnerSX &first, const BfmeInnerSX &second);
int __cdecl bfmeEqualSX(const BfmeKeySX &first, const BfmeKeySX &second)
{
	return first.m_bfmeASX == second.m_bfmeASX
		&& first.m_bfmeBSX == second.m_bfmeBSX
		&& first.m_bfmeCSX == second.m_bfmeCSX
		&& first.m_bfmeDSX == second.m_bfmeDSX
		&& bfmeSameSX(first.m_bfmeInnerSX, second.m_bfmeInnerSX);
}

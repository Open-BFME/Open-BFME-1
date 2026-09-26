struct BfmeInnerRX
{
	unsigned char m_bfmeRawRX[4];
};

struct BfmeKeyRX
{
	char m_bfmeARX;
	char m_bfmeBRX;
	char m_bfmeCRX;
	char m_bfmePadRX;
	int m_bfmeDRX;
	BfmeInnerRX m_bfmeInnerRX;
};

bool __cdecl bfmeSameRX(const BfmeInnerRX &first, const BfmeInnerRX &second);
bool __cdecl bfmeDiffersRX(const BfmeKeyRX &first, const BfmeKeyRX &second)
{
	int equal = first.m_bfmeARX == second.m_bfmeARX
		&& first.m_bfmeBRX == second.m_bfmeBRX
		&& first.m_bfmeCRX == second.m_bfmeCRX
		&& first.m_bfmeDRX == second.m_bfmeDRX
		&& bfmeSameRX(first.m_bfmeInnerRX, second.m_bfmeInnerRX);

	return !(char)equal;
}

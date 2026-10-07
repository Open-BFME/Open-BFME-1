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

// callees.py 0x00453380: the inner compare is ILT 0x00015195 -> 0x00452FE0
// (matched ?Rva00452FE0Same, Rva00452FE0Same.cpp). The only name defined at
// 0x00015195 is that 5-byte thunk, so the reference carries its symbol, as
// BfmeConv1814.cpp does.
extern "C" bool __cdecl __identifier("?j_00015195@@YAXXZ")(
	const BfmeInnerRX *first, const BfmeInnerRX *second);
bool __cdecl bfmeDiffersRX(const BfmeKeyRX &first, const BfmeKeyRX &second)
{
	int equal = first.m_bfmeARX == second.m_bfmeARX
		&& first.m_bfmeBRX == second.m_bfmeBRX
		&& first.m_bfmeCRX == second.m_bfmeCRX
		&& first.m_bfmeDRX == second.m_bfmeDRX
		&& __identifier("?j_00015195@@YAXXZ")(&first.m_bfmeInnerRX, &second.m_bfmeInnerRX);

	return !(char)equal;
}

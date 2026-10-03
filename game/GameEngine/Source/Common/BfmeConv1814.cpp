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

// The retail call at 0x00453320 targets the ILT entry 0x00015195, whose body
// lives at 0x00452FE0 (?Rva00452FE0Same, game/.../Rva00452FE0Same.cpp).  The
// only name defined at 0x00015195 is the 5-byte thunk that jumps to it, so
// the reference has to carry that exact symbol; the body keeps its cdecl two
// pointer arguments and its bool result.
extern "C" bool __cdecl __identifier("?j_00015195@@YAXXZ")(
	const BfmeInnerSX *first, const BfmeInnerSX *second );

int __cdecl bfmeEqualSX(const BfmeKeySX &first, const BfmeKeySX &second)
{
	return first.m_bfmeASX == second.m_bfmeASX
		&& first.m_bfmeBSX == second.m_bfmeBSX
		&& first.m_bfmeCSX == second.m_bfmeCSX
		&& first.m_bfmeDSX == second.m_bfmeDSX
		&& __identifier("?j_00015195@@YAXXZ")(
			&first.m_bfmeInnerSX, &second.m_bfmeInnerSX );
}

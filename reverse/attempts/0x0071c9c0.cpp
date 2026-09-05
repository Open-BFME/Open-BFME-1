// ?place@Rva0071C9C0@@QAEHHMMMPBH@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD
//
// Retail 0x0071C9C0, 397 B, from dump d_006e7d70.asm. Neighbours in this
// directory: 0x0071C7E0 BaseHeightMapResetBuffer::clear3098, 0x0071C940
// BaseHeightMapResetBuffer::resetMatchingRow (same file), 0x0071CBB0
// W3DTreeBuffer::pushAsideTree, 0x0071CD20 stampShroudVisible.
//
// This body shares W3DTreeBuffer's record geometry (count at +0x1E1CC8,
// records at +0x1548 with stride 0xA4, drawableID-shaped field at record
// +0x5C, tree-type index at record +0x40, a type table read at
// +0x1E1CE4 with stride 0x5C) documented in
// Gen_0071CBB0_W3DTreeBuffer_PushAsideTree.cpp, so it is almost certainly
// another W3DTreeBuffer method, but its exact name and the two 5-word
// parameter records (a 3-float position and a 12-dword struct pointer) are
// not recovered -- address-derived name, raw offsets instead of the sibling
// file's named struct so a difference in unknown padding cannot break the
// byte match.

typedef int Int;
typedef float Real;

class Rva0071C9C0
{
public:
	int place(Int id, Real x, Real y, Real z, const int *src);

private:
	char m_pad[0x1E1CC8];
	Int m_count;
	unsigned char m_dirty;
};

int Rva0071C9C0::place(Int id, Real x, Real y, Real z, const int *src)
{
	Int wantId = id;
	if (m_count <= 0)
		return 0;

	Int i = 0;
	char *row = (char *)this + 0x15A4;
	do
	{
		if (*(Int *)row == wantId)
			goto found;
		++i;
		row += 0xA4;
	} while (i < m_count);
	return 0;

found:
	char *rec = (char *)this + 0x1548 + (unsigned int)i * 0xA4;
	*(Real *)(rec + 0x00) = x;
	*(Real *)(rec + 0x04) = y;
	*(Real *)(rec + 0x08) = z;
	for (int k = 0; k < 12; ++k)
		*(int *)(rec + 0x10 + k * 4) = src[k];

	Int treeType = *(Int *)(rec + 0x40);
	const char *entry = (const char *)this + 0x1E1CE4 + (unsigned int)treeType * 0x5C;
	*(Real *)(rec + 0x48) = *(const Real *)(entry + 0x00);
	*(Real *)(rec + 0x4C) = *(const Real *)(entry + 0x04);
	*(Real *)(rec + 0x50) = *(const Real *)(entry + 0x08);
	*(Real *)(rec + 0x54) = *(const Real *)(entry + 0x0C);

	*(Real *)(rec + 0x48) = *(Real *)(rec + 0x0C) * *(Real *)(rec + 0x48);
	*(Real *)(rec + 0x4C) = *(Real *)(rec + 0x0C) * *(Real *)(rec + 0x4C);
	*(Real *)(rec + 0x50) = *(Real *)(rec + 0x0C) * *(Real *)(rec + 0x50);
	*(Real *)(rec + 0x54) = *(Real *)(rec + 0x54) * *(Real *)(rec + 0x0C);

	*(Real *)(rec + 0x48) = *(Real *)(rec + 0x00) + *(Real *)(rec + 0x48);
	*(Real *)(rec + 0x4C) = *(Real *)(rec + 0x04) + *(Real *)(rec + 0x4C);
	*(Real *)(rec + 0x50) = *(Real *)(rec + 0x08) + *(Real *)(rec + 0x50);

	m_dirty = 1;
	return 1;
}

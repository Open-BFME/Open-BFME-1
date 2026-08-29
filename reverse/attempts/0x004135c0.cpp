// ?d_004135c0@@YAXXZ
// partial score=0.9 date=2026-08-29
// Banked near-miss for 0x004135C0 (81B), sibling of BfmeConv1158.cpp.
// Exact length and instruction sequence; only the register allocation differs
// (retail keeps a0/a3/a4 in ebp/ebx/edi, MSVC 7.1 keeps a2/a3/a4).
void BfmeOwner1158::bfmeSubMAll1158(int a, int b, int c, int d, int e)
{
	for (BfmeItem1158 **p = m_bfmeItems; *p; ++p) {
		BfmeSub1158 *s = (*p)->bfmeGetSub1158();

		if (s)
			s->bfmeSubM1158(a, b, c, d, e);
	}
}

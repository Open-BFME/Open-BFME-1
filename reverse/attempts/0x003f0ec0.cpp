// ?bfmeFwdEQC@@YGHHPAUBfmeSrcEQC@@HHHH@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// exact size 43/43; residue is the argument-shuttle register choice only.
// Pin needed: ?bfmeInnerEQC@@YGHHHHHHH@Z,0x0001FA14,pin
struct BfmeSrcEQC
{
	unsigned char m_bfmeHeadEQC[0x10];
	int m_bfmeKindEQC;
};

int __stdcall bfmeInnerEQC(int a, int kind, int b, int c, int d, int e, int f);

int __stdcall bfmeFwdEQC(int a, BfmeSrcEQC *src, int b, int c, int d, int e)
{
	int kind = src->m_bfmeKindEQC;
	return bfmeInnerEQC(a, kind, b, c, d, e, 0);
}

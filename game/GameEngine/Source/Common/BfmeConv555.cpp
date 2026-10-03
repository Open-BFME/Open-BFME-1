class BfmeThingBXH
{
public:
	BfmeThingBXH *bfmeGoBXH(BfmeThingBXH *other, int spare);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

// The ILT thunk this body calls (0x000222AF) jumps to 0x00077240, the body the
// ledger carries as ?Rva00077240@@YAHHH@Z (BigObfHookWrappers.cpp), so the call
// is spelled with that owning name instead of the undefined bfmeCalcBXH.
int Rva00077240(int value, int seed);

BfmeThingBXH *BfmeThingBXH::bfmeGoBXH(BfmeThingBXH *other, int spare)
{
	int old = m_bfmeVal;
	m_bfmeVal = Rva00077240(old, 0x0790A442u);
	other->m_bfmeVal = old;
	return other;
}

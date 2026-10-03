class BfmeThingBXG
{
public:
	BfmeThingBXG *bfmeGoBXG(BfmeThingBXG *other);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

// Retail routes this call through the already matched five-byte ILT
// ?j_000222af@@YAXXZ (0x000222AF -> FUN_00477240), reached by the pin row
// ?bfmeCalcBXG@@YAHHI@Z.  The ILT's ledger name is the void(void) one, so the
// two stack arguments go through a pointer cast of the same relocation.
void j_000222af();

typedef int (*BfmeCalcBXG)(int value, unsigned int seed);

BfmeThingBXG *BfmeThingBXG::bfmeGoBXG(BfmeThingBXG *other)
{
	int value = reinterpret_cast<BfmeCalcBXG>(j_000222af)(m_bfmeVal, 0x0790A442u);
	m_bfmeVal = value;
	other->m_bfmeVal = value;
	return other;
}

class BfmeThingBXA
{
public:
	BfmeThingBXA *bfmeGoBXA(BfmeThingBXA *other);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

// Retail routes this call through the already matched five-byte ILT
// ?j_00023254@@YAXXZ (0x00023254 -> FUN_0094e7e0), reached by the pin row
// ?bfmeCalcBXA@@YAHHI@Z.  The ILT's ledger name is the void(void) one, so the
// two stack arguments go through a pointer cast of the same relocation.
void j_00023254();

typedef int (*BfmeCalcBXA)(int value, unsigned int seed);

BfmeThingBXA *BfmeThingBXA::bfmeGoBXA(BfmeThingBXA *other)
{
	int value = reinterpret_cast<BfmeCalcBXA>(j_00023254)(m_bfmeVal, 0x352D2FF1u);
	m_bfmeVal = value;
	other->m_bfmeVal = value;
	return other;
}

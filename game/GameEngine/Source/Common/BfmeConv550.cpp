class BfmeThingBXC
{
public:
	BfmeThingBXC *bfmeGoBXC(BfmeThingBXC *other, int spare);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

// Retail routes this call through the already matched five-byte ILT
// ?j_0003f7ce@@YAXXZ (0x0003F7CE -> FUN_0096df40), reached by the pin row
// ?bfmeCalcBXC@@YAHHI@Z.  The ILT's ledger name is the void(void) one, so the
// two stack arguments go through a pointer cast of the same relocation.
void j_0003f7ce();

typedef int (*BfmeCalcBXC)(int value, unsigned int seed);

BfmeThingBXC *BfmeThingBXC::bfmeGoBXC(BfmeThingBXC *other, int spare)
{
	int old = m_bfmeVal;
	m_bfmeVal = reinterpret_cast<BfmeCalcBXC>(j_0003f7ce)(old, 0xBA792210u);
	other->m_bfmeVal = old;
	return other;
}

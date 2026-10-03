class BfmeThingBXB
{
public:
	BfmeThingBXB *bfmeGoBXB(BfmeThingBXB *other);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

// Retail routes this call through the already matched five-byte ILT
// ?j_0003f7ce@@YAXXZ (0x0003F7CE -> FUN_0096df40), reached by the pin row
// ?bfmeCalcBXB@@YAHHI@Z.  The ILT's ledger name is the void(void) one, so the
// two stack arguments go through a pointer cast of the same relocation.
void j_0003f7ce();

typedef int (*BfmeCalcBXB)(int value, unsigned int seed);

BfmeThingBXB *BfmeThingBXB::bfmeGoBXB(BfmeThingBXB *other)
{
	int value = reinterpret_cast<BfmeCalcBXB>(j_0003f7ce)(m_bfmeVal, 0xBA792210u);
	m_bfmeVal = value;
	other->m_bfmeVal = value;
	return other;
}

// Retail's call goes through the ILT thunk at 0x00042FA0, whose ledger row is
// ?j_00042fa0@@YAXXZ (game/gen_small/thunks_032.cpp).
extern void j_00042fa0();

class BfmeThingBSE
{
public:
	BfmeThingBSE *bfmeGoBSE(BfmeThingBSE *other);
	unsigned char m_bfmeHead[4];
	void *m_bfmeWhat;
};

BfmeThingBSE *BfmeThingBSE::bfmeGoBSE(BfmeThingBSE *other)
{
	void *b = other->m_bfmeWhat;
	void *a = m_bfmeWhat;
	m_bfmeWhat = reinterpret_cast<void *(__cdecl *)(void *, void *)>(j_00042fa0)(a, b);
	return this;
}
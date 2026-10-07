struct BfmePairCXC
{
	void *m_bfmeA;
	void *m_bfmeB;
};

// Retail calls ILT 0x2E1BD -> 0x004372E0, the matched StringLookUp
// unguarded linear insert (GameTextStringLookUpInsert.cpp).
struct GameTextAsciiString;
struct GameTextStringLookUp;
struct GameTextStringCompare
{
	void *state;
};
void __cdecl GameTextUnguardedLinearInsert004372E0(
	GameTextStringLookUp *hole, GameTextAsciiString *label, void *info,
	GameTextStringCompare comp);

void bfmeGoCXC(BfmePairCXC *begin, BfmePairCXC *end, void *spare, void *arg)
{
	while (begin != end)
	{
		GameTextStringCompare comp = { arg };
		GameTextUnguardedLinearInsert004372E0(
			reinterpret_cast<GameTextStringLookUp *>(begin),
			reinterpret_cast<GameTextAsciiString *>(begin->m_bfmeA),
			begin->m_bfmeB, comp);
		++begin;
	}
}

struct BfmePairCXD
{
	void *m_bfmeA;
	void *m_bfmeB;
};

// Each element goes to ILT 0x0002E1BD -> 0x004372E0, matched as the GameText
// StringLookUp unguarded linear insert (element, its label and info, and the
// one-pointer comparator by value).
struct GameTextStringLookUp;
struct GameTextAsciiString;
struct GameTextStringCompare
{
	void *state;
};
void GameTextUnguardedLinearInsert004372E0(GameTextStringLookUp *last, GameTextAsciiString *label, void *info, GameTextStringCompare comp);

void bfmeGoCXD(BfmePairCXD *begin, BfmePairCXD *end, void *arg)
{
	while (begin != end)
	{
		GameTextStringCompare comp = { arg };
		GameTextUnguardedLinearInsert004372E0((GameTextStringLookUp *)begin, (GameTextAsciiString *)begin->m_bfmeA, begin->m_bfmeB, comp);
		++begin;
	}
}

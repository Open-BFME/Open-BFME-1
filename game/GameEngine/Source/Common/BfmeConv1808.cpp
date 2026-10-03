struct BfmeBlockTP
{
	int m_bfmeATP;
	int m_bfmeBTP;
	int m_bfmeCTP;
	int m_bfmeDTP;
};

// Retail's call lands on the ILT thunk at 0x00022D95, whose matched body
// lives in game/gen_small/gthunks_038.cpp, so the call is spelled as that
// thunk's real symbol. __identifier carries the parameter list the call site
// proves (nine stack words) without decorating it a second time.
extern "C" void __identifier("?j_00022d95@@YAXXZ")(void *first, BfmeBlockTP *second, BfmeBlockTP *third,
	BfmeBlockTP block, void *fifth, int sixth);

void __cdecl bfmeCallTP(void *first, BfmeBlockTP *second, void *third, void *fourth)
{
	BfmeBlockTP *adjusted = (BfmeBlockTP *)((char *)second - 0x10);

	__identifier("?j_00022d95@@YAXXZ")(first, adjusted, adjusted, *adjusted, fourth, 0);
}

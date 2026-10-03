struct BfmeBlockTQ
{
	int m_bfmeATQ;
	int m_bfmeBTQ;
	int m_bfmeCTQ;
	int m_bfmeDTQ;
};

// Retail's call lands on the ILT thunk at 0x00022D95, whose matched body
// lives in game/gen_small/gthunks_038.cpp, so the call is spelled as that
// thunk's real symbol. __identifier carries the parameter list the call site
// proves (nine stack words) without decorating it a second time.
extern "C" void __identifier("?j_00022d95@@YAXXZ")(void *first, BfmeBlockTQ *second, BfmeBlockTQ *third,
	BfmeBlockTQ block, void *fifth, int sixth);

void __cdecl bfmeCallTQ(void *first, BfmeBlockTQ *second, void *third)
{
	BfmeBlockTQ *adjusted = (BfmeBlockTQ *)((char *)second - 0x10);

	__identifier("?j_00022d95@@YAXXZ")(first, adjusted, adjusted, *adjusted, third, 0);
}

class BfmeThingBDG
{
public:
	void bfmeGoBDG(void *what);
	unsigned char m_bfmeHead[0x264];
	int m_bfmeState;
};

// The call at 0x0052C640 targets RVA 0x0003FE5E, whose only definition in the
// ledger is the 5-byte ILT thunk ?j_0003fe5e@@YAXXZ
// (game/gen_small/thunks_030.cpp).  Retail pushes nothing for it and keeps no
// value of ecx across it, so void(void) is the whole of the ABI this body uses
// and the thunk's own name is the honest spelling of the call.
extern void j_0003fe5e();

void BfmeThingBDG::bfmeGoBDG(void *what)
{
	if (m_bfmeState == 1)
		j_0003fe5e();
}
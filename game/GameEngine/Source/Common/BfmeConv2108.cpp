class BfmeEntryZG
{
public:
	void bfmeStepZG();
	void bfmeFinishZG(void *slot, bool flag);

	unsigned char m_bfmeHeadZG[0x20];
	int m_bfme20ZG;
	unsigned char m_bfmeGapZG[0x18];
	int m_bfme3CZG;
};

// The state-3 advance calls the ILT thunk at 0x0003FE09
// (`?j_0003fe09@@YAXXZ`, game/gen_small/thunks_030.cpp), not a body of the
// entry's own, so the call is named by the thunk at that address. The retail
// call passes this + &m_bfme3CZG, i.e. the thiscall shape of finish().

extern void j_0003fe09();

void BfmeEntryZG::bfmeStepZG()
{
	typedef void (BfmeEntryZG::*Call)(void *, bool);
	union { void (*raw)(); Call finish; } call;

	if (m_bfme20ZG != 3)
		return;

	m_bfme20ZG = 4;
	call.raw = j_0003fe09;
	(this->*call.finish)(&m_bfme3CZG, false);
}

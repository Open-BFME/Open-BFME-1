class BfmeAgentAR;
class BfmeSeedTarget;

// The two calls this body makes besides ?handle@Gen002B2080 are read out of its
// retail bytes at 0x001FBBC0:
//   call 0x4160B3 (thunk -> 0x001EF3D0)  ?invoke@Rva001EF3D0Caller@@QAEXPAVFlagPairTarget@@@Z
//   call 0x429DAC (thunk -> 0x002D9B90)  ?bfmeSeed@Gen_002D9B90@@QAEXPAVBfmeSeedTarget@@@Z
// Both owners are matched TUs elsewhere in game/, so the references below carry
// their real names instead of invented BfmeHostAR/BfmeSubAR members. Retail
// passes `this` itself to the first (ecx = edi, unadjusted), so no class is
// derived from; the second's `this` is this+0x20.

// Retail ILT 0x000044C1 (targets/game/reverse/functions.csv, gen-thunk row
// ?j_000044c1@@YAXXZ) is a 5-byte `jmp 0x6b2080`, i.e. RVA 0x002B2080, which
// the ledger matches as
// ?handle@Gen002B2080@@QAEXPAVFlagPairTarget@@@Z
// (game/GameEngine/Source/GameLogic/AI/Gen002B2080Handle.cpp). Only the one
// member is spelled here, so no layout of that class is imported; the caller
// passes its own `this` and the same pointer the ILT took, exactly as retail
// does (ecx + one pushed argument, `ret 4` on the callee side).
class FlagPairTarget;

class Gen002B2080
{
public:
	void handle(FlagPairTarget *target);
};

class Rva001EF3D0Caller
{
public:
	void invoke(FlagPairTarget *target);
};

class Gen_002D9B90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;
};

struct BfmeInfoAR
{
	unsigned char m_bfmeFlagAR;
	unsigned char m_bfmeLevelAR;
};

class BfmeAgentAR
{
public:
	virtual void bfmeSlot00AR();
	virtual void bfmeSlot01AR();
	virtual void bfmeSlot02AR();
	virtual void bfmeSlot03AR();
	virtual void bfmeSlot04AR();
	virtual void bfmeSlot05AR();
	virtual void bfmeSlot06AR();
	virtual void bfmeSlot07AR();
	virtual void bfmeSlot08AR();
	virtual void bfmeSlot09AR();
	virtual void bfmeFillAR(BfmeInfoAR *info);
	virtual void bfmeSlot11AR();
	virtual void bfmeSlot12AR();
	virtual void bfmeSlot13AR();
	virtual void bfmeSlot14AR();
	virtual void bfmeSlot15AR();
	virtual void bfmeSlot16AR();
	virtual void bfmeSlot17AR();
	virtual void bfmeSlot18AR();
	virtual void bfmeSlot19AR();
	virtual void bfmeSlot20AR();
	virtual void bfmeSlot21AR();
	virtual void bfmeSlot22AR();
	virtual void bfmeSlot23AR();
	virtual void bfmeSlot24AR();
	virtual void bfmeSlot25AR();
	virtual void bfmeSlot26AR();
	virtual void bfmeSlot27AR();
	virtual void bfmeSlot28AR();
	virtual void bfmeSlot29AR();
	virtual void bfmeApplyAR(void *what);
};

class BfmeVirtAR
{
public:
	virtual void bfmeReleaseAR(BfmeAgentAR *ag);
};

class BfmeHostAR
{
public:
	void bfmeSendAR(BfmeAgentAR *ag);

	unsigned char m_bfmeHeadAR[0x20];
	Gen_002D9B90 m_bfmeSubAR;
	unsigned char m_bfmePadAR[7];
	BfmeVirtAR m_bfmeVirtAR;
	unsigned char m_bfmeMidAR[0x58];
	unsigned char m_bfmeStateAR[4];
};

void BfmeHostAR::bfmeSendAR(BfmeAgentAR *ag)
{
	BfmeInfoAR info;

	info.m_bfmeFlagAR = 1;
	info.m_bfmeLevelAR = 3;
	ag->bfmeFillAR(&info);

	if (info.m_bfmeLevelAR >= 2)
		((Gen002B2080 *)this)->handle((FlagPairTarget *)ag);
	else
		((Rva001EF3D0Caller *)this)->invoke((FlagPairTarget *)ag);

	m_bfmeSubAR.bfmeSeed((BfmeSeedTarget *)ag);

	if (info.m_bfmeLevelAR >= 3)
	{
		m_bfmeVirtAR.bfmeReleaseAR(ag);
		ag->bfmeApplyAR(m_bfmeStateAR);
	}
}

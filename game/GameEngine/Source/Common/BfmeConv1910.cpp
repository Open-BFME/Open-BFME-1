struct BfmeInfoBE
{
	unsigned char m_bfmeFlagBE;
	unsigned char m_bfmeLevelBE;
};

class BfmeAgentBE
{
public:
	virtual void bfmeSlot00BE();
	virtual void bfmeSlot01BE();
	virtual void bfmeSlot02BE();
	virtual void bfmeSlot03BE();
	virtual void bfmeSlot04BE();
	virtual void bfmeSlot05BE();
	virtual void bfmeSlot06BE();
	virtual void bfmeSlot07BE();
	virtual void bfmeSlot08BE();
	virtual void bfmeSlot09BE();
	virtual void bfmeFillBE(BfmeInfoBE *info);
	virtual void bfmeSlot11BE();
	virtual void bfmeSlot12BE();
	virtual void bfmeSlot13BE();
	virtual void bfmeSlot14BE();
	virtual void bfmeSlot15BE();
	virtual void bfmeSlot16BE();
	virtual void bfmeSlot17BE();
	virtual void bfmeSlot18BE();
	virtual void bfmeSlot19BE();
	virtual void bfmeSlot20BE();
	virtual void bfmeSlot21BE();
	virtual void bfmeSlot22BE();
	virtual void bfmeSlot23BE();
	virtual void bfmeSlot24BE();
	virtual void bfmeSlot25BE();
	virtual void bfmeSlot26BE();
	virtual void bfmeSlot27BE();
	virtual void bfmeSlot28BE();
	virtual void bfmeWordBE(void *dst);
	virtual void bfmeSlot30BE();
	virtual void bfmeSlot31BE();
	virtual void bfmeSlot32BE();
	virtual void bfmeSlot33BE();
	virtual void bfmeSlot34BE();
	virtual void bfmeByteBE(unsigned char *dst);
};

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00AC();
	virtual void bfmeSlot01AC();
	virtual void bfmeSlot02AC();
	virtual void bfmeSlot03AC();
	virtual void bfmeSlot04AC();
	virtual void bfmeSlot05AC();
	virtual void bfmeSlot06AC();
	virtual void bfmeSlot07AC();
	virtual void bfmeSlot08AC();
	virtual void bfmeSlot09AC();
	virtual void bfmeSlot10AC();
	virtual void bfmeSlot11AC();
	virtual void bfmeSlot12AC();
	virtual void bfmeSlot13AC();
	virtual void bfmeSlot14AC();
	virtual void bfmeSlot15AC();
	virtual void bfmeSlot16AC();
	virtual void bfmeSlot17AC();
	virtual void bfmeSlot18AC();
	virtual void bfmeSlot19AC();
	virtual void bfmeSlot20AC();
	virtual void bfmeSlot21AC();
	virtual void bfmeSlot22AC();
	virtual void bfmeSlot23AC();
	virtual void bfmeSlot24AC();
	virtual void bfmeSlot25AC();
	virtual void bfmeSlot26AC();
	virtual void bfmeSlot27AC();
	virtual void bfmeSlot28AC();
	virtual void bfmeSlot29AC();
	virtual void bfmeSlot30AC();
	virtual void bfmeSlot31AC();
	virtual void bfmeSlot32AC();
	virtual void bfmeSlot33AC();
	virtual void bfmeSlot34AC();
	virtual void bfmeSlot35AC();
	virtual void bfmeSlot36AC();
	virtual void bfmeSlot37AC();
	virtual void bfmeSlot38AC();
	virtual void bfmeSlot39AC();
	virtual void bfmeSlot40AC();
	virtual void bfmeSlot41AC();
	virtual void bfmeSlot42AC();
	virtual void bfmeSlot43AC();
	virtual void bfmeSlot44AC();
	virtual void bfmeSlot45AC();
	virtual void bfmeSlot46AC();
	virtual void bfmeSlot47AC();
	virtual void bfmeSlot48AC();
	virtual void bfmeSlot49AC();
	virtual void bfmeSlot50AC();
	virtual void bfmeSlot51AC();
	virtual void bfmeSlot52AC();
	virtual void bfmeSlot53AC();
	virtual void bfmeSlot54AC();
	virtual void bfmeSlot55AC();
	virtual void bfmeSlot56AC();
	virtual void bfmeSlot57AC();
	virtual void bfmeSlot58AC();
	virtual void bfmeSlot59AC();
	virtual void bfmeSlot60AC();
	virtual void bfmeSlot61AC();
	virtual void bfmeSlot62AC();
	virtual void bfmeSlot63AC();
	virtual void bfmeSlot64AC();
	virtual void bfmeSlot65AC();
	virtual void bfmeSlot66AC();
	virtual void bfmeSlot67AC();
	virtual void bfmeSlot68AC();
	virtual void bfmeSlot69AC();
	virtual void bfmeSlot70AC();
	virtual void bfmeSlot71AC();
	virtual void bfmeSlot72AC();
	virtual void bfmeSlot73AC();
	virtual void bfmeSlot74AC();
	virtual void bfmeSlot75AC();
	virtual void bfmeSlot76AC();
	virtual void bfmeSlot77AC();
	virtual void bfmeSlot78AC();
	virtual void bfmeSlot79AC();
	virtual void bfmeSlot80AC();
	virtual void bfmeSlot81AC();
	virtual void bfmeAudioBE(BfmeAgentBE *ag, void *dst);
};

// retail reads the audio manager singleton (0x012ED668) here; defined in
// game/GameEngine/Source/Common/Audio/GameAudio.cpp.
class AudioManager;
extern AudioManager *TheAudio;

// Retail reaches both of this host's helpers through five-byte ILT thunks, not
// through the helper bodies themselves: the call at 0x0036BCB6/0x0036BCDC/
// 0x0036BCEE targets 0x0000C9B4 (?j_0000c9b4@@YAXXZ,
// game/gen_small/thunks_005.cpp, tail-jumping to the __cdecl forwarder at
// 0x0010C3C0) and the call at 0x0036BCE7 targets 0x000160B3
// (?j_000160b3@@YAXXZ, game/gen_small/thunks_010.cpp, tail-jumping to
// 0x001EF3D0). Referencing the thunks' own symbols is what links; the
// member declarations below keep the recovered meaning and stay declared-only
// so no undefined helper body is emitted.
void j_0000c9b4();
void j_000160b3();

typedef void (__cdecl *Rva0000C9B4XferCall)(BfmeAgentBE *, void *);

// TU-local: the spelling of retail's transfer helper only exists to shape the
// call, so it must not emit a symbol of its own.
static __forceinline void bfmeXferBE(BfmeAgentBE *ag, void *dst)
{
	((Rva0000C9B4XferCall)(void *)j_0000c9b4)(ag, dst);
}

class BfmeHostBE
{
public:
	void bfmeSaveBE(BfmeAgentBE *ag);
	void bfmeStepBE(BfmeAgentBE *ag);

	unsigned char m_bfmeHeadBE[0x14];
	unsigned char m_bfmeSlotABE[4];
	unsigned char m_bfmeSlotBBE[4];
	unsigned char m_bfmeSlotCBE[4];
	unsigned char m_bfmeSlotDBE[4];
	unsigned char m_bfmeSlotEBE;
	unsigned char m_bfmeSlotFBE;
};

void BfmeHostBE::bfmeSaveBE(BfmeAgentBE *ag)
{
	BfmeInfoBE info;

	info.m_bfmeFlagBE = 1;
	info.m_bfmeLevelBE = 1;
	ag->bfmeFillBE(&info);

	bfmeXferBE(ag, m_bfmeSlotABE);
	ag->bfmeByteBE(&m_bfmeSlotEBE);
	ag->bfmeWordBE(m_bfmeSlotCBE);
	bfmeXferBE(ag, m_bfmeSlotBBE);

	{
		union { void (*raw)(); void (BfmeHostBE::*m)(BfmeAgentBE *); } step;
		step.raw = j_000160b3;
		(this->*step.m)(ag);
	}

	bfmeXferBE(ag, m_bfmeSlotBBE);
	ag->bfmeWordBE(m_bfmeSlotCBE);
	ag->bfmeByteBE(&m_bfmeSlotFBE);

	((Rva005A00B0AudioClient *)TheAudio)->bfmeAudioBE(ag, m_bfmeSlotDBE);
}

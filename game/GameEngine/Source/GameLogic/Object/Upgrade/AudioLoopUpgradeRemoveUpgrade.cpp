// AudioLoopUpgrade::removeUpgrade at retail 0x002D34B0 (48 B): slot 7 of the
// UpgradeMux table 0x010CBD08, which AudioLoopUpgrade's registered constructor
// 0x002D32B0 stores at its +0x20 sub-object. The only route is ILT 0x000417E0,
// whose VA appears once in the image. Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot),
// which undoes
// slot 9 (AudioLoopUpgrade::upgradeImplementation, 0x002D33E0, which starts the
// loop): this body kills the playing handle and resets it to 1.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

class BfmeG1024
{
public:
	virtual void bfmeVG01024();
	virtual void bfmeVG11024();
	virtual void bfmeVG21024();
	virtual void bfmeVG31024();
	virtual void bfmeVG41024();
	virtual void bfmeVG51024();
	virtual void bfmeVG61024();
	virtual void bfmeVG71024();
	virtual void bfmeVG81024();
	virtual void bfmeVG91024();
	virtual void bfmeVG101024();
	virtual void bfmeVG111024();
	virtual void bfmeVG121024();
	virtual void bfmeVG131024();
	virtual void bfmeVG141024();
	virtual void bfmeVG151024();
	virtual void bfmeVG161024();
	virtual void bfmeVG171024();
	virtual void bfmeVG181024();
	virtual void bfmeKill1024(int v);
};

// Retail's audio global, at 0x012ED668, is AudioManager *TheAudio
// (?TheAudio@@3PAVAudioManager@@A). The BfmeG1024 view above is TU-local.
class AudioManager;
extern AudioManager *TheAudio;

class BfmeH1024
{
public:
	char m_bfmePad[8];
	int m_bfmeVal;
};

// Retail calls the ILT thunk at 0x000157DA, owned by game/gen_small/thunks_009.cpp
// as ?j_000157da@@YAXXZ (its target, 0x002B2040, has no ledger row of its own).
// The call is reached through a member-function pointer so it keeps its
// thiscall shape; bfmeAdd1024 is never referenced by name.
extern "C" void __cdecl __identifier("?j_000157da@@YAXXZ")();
typedef void (BfmeH1024::*BfmeAdd1024Thunk)(int a, int b);
union BfmeAdd1024ThunkRef
{
	void *m_thunk;
	BfmeAdd1024Thunk m_call;
};

class AudioLoopUpgrade
{
protected:
	virtual void removeUpgrade();

public:
	char m_bfmePad[0x8];	// +0x04, after the vptr
	int m_bfmeH;
};

void AudioLoopUpgrade::removeUpgrade()
{
	if (TheAudio != 0) {
		((BfmeG1024 *)TheAudio)->bfmeKill1024(m_bfmeH);
		m_bfmeH = 1;
	}

	BfmeAdd1024ThunkRef add1024;
	add1024.m_thunk = (void *)&__identifier("?j_000157da@@YAXXZ");
	(((BfmeH1024 *)((char *)this - 0x20))->*add1024.m_call)(
		((BfmeH1024 *)((char *)this - 0x20))->m_bfmeVal, 0x3fffffff);
}

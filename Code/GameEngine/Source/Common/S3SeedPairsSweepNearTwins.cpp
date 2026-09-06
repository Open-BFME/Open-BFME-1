// cl: /DNDEBUG /MD /EHs-c-

// Two address-derived near-twins of the seed-pair sweep family in
// Code/GameEngine/Source/Common/S3SeedPairsSweep.cpp (see that file's header
// for the shared shape: seed a two-byte pair via slot 0x28, then hand the
// address of one or more sub-objects to the target, sometimes via a direct
// bfmeAccept ILT instead of a virtual TakeAt call).

struct BfmeSeedPair_NT
{
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget_NT
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSeed(BfmeSeedPair_NT *pair);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);		// vtable+0x70
	virtual void bfmeTakeAt74(void *item);	// vtable+0x74
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);	// vtable+0x8c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h (ClientSubsystem-derived audio manager)
class BfmeAudioClientUpdate_NT
{
public:
	virtual void bfmeSlot000(void);
	virtual void bfmeSlot004(void);
	virtual void bfmeSlot008(void);
	virtual void bfmeSlot00c(void);
	virtual void bfmeSlot010(void);
	virtual void bfmeSlot014(void);
	virtual void bfmeSlot018(void);
	virtual void bfmeSlot01c(void);
	virtual void bfmeSlot020(void);
	virtual void bfmeSlot024(void);
	virtual void bfmeSlot028(void);
	virtual void bfmeSlot02c(void);
	virtual void bfmeSlot030(void);
	virtual void bfmeSlot034(void);
	virtual void bfmeSlot038(void);
	virtual void bfmeSlot03c(void);
	virtual void bfmeSlot040(void);
	virtual void bfmeSlot044(void);
	virtual void bfmeSlot048(void);
	virtual void bfmeSlot04c(void);
	virtual void bfmeSlot050(void);
	virtual void bfmeSlot054(void);
	virtual void bfmeSlot058(void);
	virtual void bfmeSlot05c(void);
	virtual void bfmeSlot060(void);
	virtual void bfmeSlot064(void);
	virtual void bfmeSlot068(void);
	virtual void bfmeSlot06c(void);
	virtual void bfmeSlot070(void);
	virtual void bfmeSlot074(void);
	virtual void bfmeSlot078(void);
	virtual void bfmeSlot07c(void);
	virtual void bfmeSlot080(void);
	virtual void bfmeSlot084(void);
	virtual void bfmeSlot088(void);
	virtual void bfmeSlot08c(void);
	virtual void bfmeSlot090(void);
	virtual void bfmeSlot094(void);
	virtual void bfmeSlot098(void);
	virtual void bfmeSlot09c(void);
	virtual void bfmeSlot0a0(void);
	virtual void bfmeSlot0a4(void);
	virtual void bfmeSlot0a8(void);
	virtual void bfmeSlot0ac(void);
	virtual void bfmeSlot0b0(void);
	virtual void bfmeSlot0b4(void);
	virtual void bfmeSlot0b8(void);
	virtual void bfmeSlot0bc(void);
	virtual void bfmeSlot0c0(void);
	virtual void bfmeSlot0c4(void);
	virtual void bfmeSlot0c8(void);
	virtual void bfmeSlot0cc(void);
	virtual void bfmeSlot0d0(void);
	virtual void bfmeSlot0d4(void);
	virtual void bfmeSlot0d8(void);
	virtual void bfmeSlot0dc(void);
	virtual void bfmeSlot0e0(void);
	virtual void bfmeSlot0e4(void);
	virtual void bfmeSlot0e8(void);
	virtual void bfmeSlot0ec(void);
	virtual void bfmeSlot0f0(void);
	virtual void bfmeSlot0f4(void);
	virtual void bfmeSlot0f8(void);
	virtual void bfmeSlot0fc(void);
	virtual void bfmeSlot100(void);
	virtual void bfmeSlot104(void);
	virtual void bfmeSlot108(void);
	virtual void bfmeSlot10c(void);
	virtual void bfmeSlot110(void);
	virtual void bfmeSlot114(void);
	virtual void bfmeSlot118(void);
	virtual void bfmeSlot11c(void);
	virtual void bfmeSlot120(void);
	virtual void bfmeSlot124(void);
	virtual void bfmeSlot128(void);
	virtual void bfmeSlot12c(void);
	virtual void bfmeSlot130(void);
	virtual void bfmeSlot134(void);
	virtual void bfmeSlot138(void);
	virtual void bfmeSlot13c(void);
	virtual void bfmeSlot140(void);
	virtual void bfmeSlot144(void);
	virtual void bfmeTakeItem148(BfmeSeedTarget_NT *target, void *item);	// vtable+0x148
};

extern BfmeAudioClientUpdate_NT *g_Va012ED668;

class BfmeSubAccept_00029DAC_NT
{
public:
	void bfmeAccept(BfmeSeedTarget_NT *target);		// ILT 0x00029DAC
};

// ---------------------------------------------------------------------------
// 0x002D6ED0 -- near-twin of ?bfmeSeed@Gen_0016C8C0@@QAEXPAVBfmeSeedTarget@@@Z
// (Code/GameEngine/Source/Common/S3SeedPairsSweep.cpp). Same shape, but the
// two bfmeTakeAt calls have different targets, and two direct bfmeAccept ILTs
// replace nothing -- they are appended after both TakeAt calls, with the
// second one operating on a sub-object 8 bytes BEFORE `this`.
// ---------------------------------------------------------------------------
class Gen_002D6ED0
{
public:
	void bfmeSeed(BfmeSeedTarget_NT *target);

private:
	void bfmeAccept(BfmeSeedTarget_NT *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem1;				// +0x20 (bfmeTakeAt74)
	char m_bfmePad1[0x3];
	char m_bfmeItem0;				// +0x24 (bfmeTakeAt8C)
};

void Gen_002D6ED0::bfmeSeed(BfmeSeedTarget_NT *target)
{
	BfmeSeedPair_NT pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt74(&m_bfmeItem1);
	bfmeAccept(target);
	((BfmeSubAccept_00029DAC_NT *)((char *)this - 8))->bfmeAccept(target);
}

// ---------------------------------------------------------------------------
// 0x002D35A0 -- near-twin of ?bfmeSeed@Gen_001F6900@@QAEXPAVBfmeSeedTarget@@@Z
// (Code/GameEngine/Source/Common/S3SeedPairsSweep.cpp). Same shape, but the
// second bfmeTakeAt8C call is replaced by a call through the global audio
// client-update pointer, and the second bfmeAccept operates on a sub-object
// at +0x20 instead of a plain bfmeTakeAt8C.
// ---------------------------------------------------------------------------
class Gen_002D35A0
{
public:
	void bfmeSeed(BfmeSeedTarget_NT *target);

private:
	void bfmeAccept(BfmeSeedTarget_NT *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	class BfmeSubAccept_00029DAC_NT *m_bfmeSub20;		// +0x20 (used by address, not value)
	char m_bfmePad1[0x8];
	char m_bfmeItem2c;				// +0x2C
};

void Gen_002D35A0::bfmeSeed(BfmeSeedTarget_NT *target)
{
	BfmeSeedPair_NT pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	g_Va012ED668->bfmeTakeItem148(target, &m_bfmeItem2c);
	bfmeAccept(target);
	((BfmeSubAccept_00029DAC_NT *)((char *)this + 0x20))->bfmeAccept(target);
}

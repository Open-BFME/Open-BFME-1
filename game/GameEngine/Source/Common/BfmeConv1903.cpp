struct BfmeInfoAW
{
	unsigned char m_bfmeFlagAW;
	unsigned char m_bfmeLevelAW;
};

class BfmeAgentAW
{
public:
	virtual void bfmeSlot00AW();
	virtual void bfmeSlot01AW();
	virtual void bfmeSlot02AW();
	virtual void bfmeSlot03AW();
	virtual char bfmeSkipAW();
	virtual void bfmeSlot05AW();
	virtual void bfmeSlot06AW();
	virtual void bfmeSlot07AW();
	virtual void bfmeSlot08AW();
	virtual void bfmeSlot09AW();
	virtual void bfmeFillAW(BfmeInfoAW *info);
	virtual void bfmeSlot11AW();
	virtual void bfmeSlot12AW();
	virtual void bfmeSlot13AW();
	virtual void bfmeSlot14AW();
	virtual void bfmeSlot15AW();
	virtual void bfmeSlot16AW();
	virtual void bfmeSlot17AW();
	virtual void bfmeSlot18AW();
	virtual void bfmeSlot19AW();
	virtual void bfmeSlot20AW();
	virtual void bfmeSlot21AW();
	virtual void bfmeSlot22AW();
	virtual void bfmeSlot23AW();
	virtual void bfmeSlot24AW();
	virtual void bfmeSlot25AW();
	virtual void bfmeSlot26AW();
	virtual void bfmeLateAW(void *dst);
	virtual void bfmeSlot28AW();
	virtual void bfmeStoreAW(void *dst);
	virtual void bfmeSlot30AW();
	virtual void bfmeSlot31AW();
	virtual void bfmeSlot32AW();
	virtual void bfmeSlot33AW();
	virtual void bfmeSlot34AW();
	virtual void bfmeWriteAW(void *dst);
};

// The cross-TU helper this body reaches through the ILT thunk at 0x0000FFE2 is
// NOT an extern "C" symbol: the thunk is `E9 09 67 0D 00`, i.e. it jumps to
// retail 0x000E66F0, which the ledger owns as the matched 267-byte row
// ?bfmeHandOver_0000FFE2@@YAPAVBfmeSeedTarget@@PAV1@PAX@Z
// (game/GameEngine/Source/Common/S3SeedPairsHoisted.cpp).  That name decodes to
// a __cdecl free function returning BfmeSeedTarget* and taking
// (BfmeSeedTarget*, void*) -- `PAV1@` back-references the return type, so it is
// TWO arguments, not three.  That is exactly the call this body makes:
//
//     push ecx          ; ecx = this + 0xe8
//     push esi          ; esi = ag
//     call 0x0000FFE2
//     add esp, 8        ; caller cleans: __cdecl, two stack arguments
//
// so the local `extern "C" bfmeXferAW` placeholder is respelled to the defined
// name.  The return value is discarded in retail (eax is reloaded from [esi]
// immediately), and an unused return value emits no code.
class BfmeSeedTarget;

BfmeSeedTarget *__cdecl bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);

// The other call this body makes -- the one BEFORE the skip test, which it
// places first in the body -- is retail's ILT thunk at 0x000289F7
// (`E9 94 ED 27 00`, i.e. it jumps to RVA 0x002A7790).  That RVA is the
// ledger's matched 426-byte row
// ?bfmeAccept@Gen_00257D10@@AAEXPAVBfmeSeedTarget@@@Z
// (game/GameEngine/Source/Common/Gen00257D10Accept.cpp), and symbols.csv
// already pins that name at the very ILT this body calls.  It is the same
// function this file's twin BfmeConv1900.cpp reaches: ?bfmeSaveAT@BfmeHostAT@@
// QAEXPAVBfmeAgentAT@@@Z at RVA 0x002676A0 calls ILT 0x000289F7 too (callees.py
// 0x002676A0 98: `0x289f7 -> 0x2a7790`), and that TU spells the call
//
//     ((Gen_00257D10 *)this)->bfmeAccept((BfmeSeedTarget *)ag);
//
// with the same `friend class BfmeHostAT;` + private-member declaration.  So
// `bfmeBeginAW` is a placeholder for that identity, not a separate body, and
// it is respelled to it verbatim.  `AAE` is the private access code, which is
// why the friend declaration is needed and why BfmeConv1900.cpp carries one.
// The identity is corroborated by shape, not just by the thunk: bfmeAccept and
// this body both build the seed pair {1,2} at slots +0x10 (skip) and +0x28
// (seed/fill) of the agent, and bfmeSaveAW's own fields at +0xE8..+0xF8 sit
// past the highest offset bfmeAccept touches (+0xE5), so the two are members of
// one retail object and `this` here is that object.
class BfmeHostAW;

class Gen_00257D10
{
	friend class BfmeHostAW;

private:
	void bfmeAccept(BfmeSeedTarget *target);
};

class BfmeHostAW
{
public:
	void bfmeSaveAW(BfmeAgentAW *ag);

	unsigned char m_bfmeHeadAW[0xe8];
	unsigned char m_bfmeSlotAAW[4];
	unsigned char m_bfmeSlotBAW[4];
	unsigned char m_bfmeSlotCAW[4];
	unsigned char m_bfmeSlotDAW[4];
	unsigned char m_bfmeSlotEAW[4];
};

void BfmeHostAW::bfmeSaveAW(BfmeAgentAW *ag)
{
	((Gen_00257D10 *)this)->bfmeAccept((BfmeSeedTarget *)ag);

	if (ag->bfmeSkipAW() != 0)
		return;

	BfmeInfoAW info;

	info.m_bfmeFlagAW = 1;
	info.m_bfmeLevelAW = 2;
	ag->bfmeFillAW(&info);

	bfmeHandOver_0000FFE2((BfmeSeedTarget *)ag, m_bfmeSlotAAW);
	ag->bfmeWriteAW(m_bfmeSlotCAW);
	ag->bfmeStoreAW(m_bfmeSlotBAW);

	if (info.m_bfmeLevelAW >= 2)
	{
		ag->bfmeLateAW(m_bfmeSlotDAW);
		ag->bfmeLateAW(m_bfmeSlotEAW);
	}
}

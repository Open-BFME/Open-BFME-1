// ?startGame@GameSpyStagingRoom@@UAEXH@Z
// partial score=0.3 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include ...
//
// IDENTITY (high confidence, cross-checked against several already-matched
// neighbours, not just probe.py's shape heuristics):
//   0x0063A3B0 is GameSpyStagingRoom::startGame(Int gameID), a virtual override
//   of GameInfo::startGame. A near-identical scaffold already lives at
//   Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp around
//   line 560 ("?startGame@GameSpyStagingRoom@@ present-unmatched"), copied
//   almost verbatim from the ZH reference (GeneralsMD StagingRoomGameInfo.cpp
//   line 537). Evidence tying this exact body to that exact symbol:
//     - the ILT call near the "numHumans < 2" branch (retail +0x20a, call
//       0x00006ce4) is the SAME ILT the ledger already records as
//       "callers ... 0x0063A5BC ... via ILT 0x00006CE4" on the matched
//       ?launchGame@GameSpyStagingRoom@@QAEXXZ row (0x00639950).
//     - reverse/functions.csv note on ?attachSlotList@NAT@@ (0x00670F10)
//       explicitly names "GameSpyStagingRoom::startGame caller".
//     - reverse/functions.csv note on ?establishConnectionPaths@NAT@@
//       (0x00672A60) names "staging caller63A62C viaFF92" -- 0x0063A62C is
//       inside this body's 662-byte range.
//     - TheNAT global is confirmed at VA 0x012F770C by the launchGame note;
//       retail deletes/nulls it near the top of this body exactly where ZH's
//       startGame does "if (TheNAT != NULL) { delete TheNAT; TheNAT = NULL; }".
//     - the two GameSlot helper calls the brief pinned as placeholders
//       (bfmeChk1079@BfmeM1079 at ILT 0x000279CB, bfmeCallDQG@BfmeItemDQG at
//       ILT 0x0003A20B) are real ILT thunks: 0x000279CB jumps to
//       ?isHuman@GameSlot@@QBE_NXZ (0x0061E580, matched) and 0x0003A20B jumps
//       to ?getName@GameSlot@@QBE?AVUnicodeString@@XZ (0x003879C0, matched).
//       Both are exactly the two GameSlot queries ZH's startGame makes per
//       slot before AsciiString::translate.
//     - all four GameSpyGameSlot setters ZH's startGame calls are already
//       matched: setProfileID (0x001A19C0), setLocale (0x006380F0),
//       setSlotRankPoints (0x0045BEC0), setFavoriteSide (0x006370C0); so is
//       setLoginName (0x00638060) and getLocalSlotNum@GameSpyStagingRoom
//       (0x006383E0, vtable slot 0x14 per several ledger notes).
//     - GameSpyStagingRoom's proven layout (Code/GameEngine/Source/GameNetwork/
//       GameSpy/GameSpyStagingRoom_ctor.cpp): GameInfo base is 0x58 bytes,
//       m_slots[8] of GameSpyGameSlot (0x78 stride each, matching this body's
//       loop stride exactly) start at +0x58, m_localName lands at +0x424
//       (matches Code/GameEngine/Source/Common/promoted__amIHost_...cpp's
//       independently-derived +0x424 for m_localName), m_isQM lands at +0x43C
//       -- exactly the byte this body tests with "test byte ptr[edi+0x43c]"
//       to choose between the QM/non-QM branch (matches ZH's "if (m_isQM)").
//     - GameInfo::m_localIP sits at +0x34 of the GameInfo base (vtable(4) +
//       m_preorderMask+m_crcInterval+m_inGame+m_inProgress+m_surrendered+pad+
//       m_gameID+m_slot[8]), matching this body's "mov [edi+0x34], esi" right
//       after the first TheGameSpyInfo call (= setLocalIP(getInternalIP())).
//
// WHAT IS STILL WRONG (probe.py against the existing scaffold source, as-is):
//   ours=539B retail=662B, 387 non-reloc byte diffs, first at +2.
//   1. TheGameSpyInfo->getInternalIP() resolves to vtable slot 0x120 (72,
//      i.e. the plain ZH GameSpyInfoInterface slot count) but retail calls
//      slot 0x14c (83) -- BFME's real GameSpyInfoInterface has ELEVEN extra
//      virtuals inserted somewhere before getInternalIP/getExternalIP (which
//      stay adjacent to each other: retail's second TheGameSpyInfo call is at
//      slot 0x150 = 84, i.e. immediately after 83, exactly like ZH's
//      getInternalIP()/getExternalIP() pair, so the 11 insertions are a
//      contiguous block strictly BEFORE both, not between them). A local
//      shim (BFME_VSLOT-style dummy virtuals, see WOLLobbyMenuPopulateGroup-
//      RoomListbox.cpp for the established idiom in this repo) reinterpreting
//      TheGameSpyInfo through a class with 83 leading dummy virtual slots
//      before the two real ones fixes the CALL displacement, but has not been
//      compiled/verified yet.
//   2. The second TheGameSpyInfo call's result is stored as a 16-bit quantity
//      (mov word ptr [stack], ax; later reloaded as a full dword with garbage
//      upper bits and stored to [edi+0x38] -- a 4-byte store). GameInfo's own
//      field at +0x38 is m_mapName (AsciiString*, 4 bytes) per the plain ZH
//      layout math, which does not explain a 16-bit-meaningful write. Either
//      GameInfo gained a BFME field between m_localIP (+0x34) and m_mapName,
//      or this pair of instructions belongs to something other than a direct
//      getExternalIP()-style call. NOT RESOLVED -- needs a probe.py iteration
//      once (1) is fixed to see the isolated byte diff for this instruction
//      pair specifically.
//   3. Missing SEH: retail's prologue pushes a real per-function exception
//      handler (push 0x010416f3) before mov eax,fs:[0]; the current compiled
//      object instead does "push 0" there, i.e. it is not establishing a
//      real __except frame at all. This is almost certainly downstream of (1)
//      and (2) confusing the compiler's EH-state tracking for the AsciiString/
//      UnicodeString temporaries in the loop (gsName, the getName() return
//      value), OR of a difference between the local GameSpyGameSlot/PlayerInfo
//      reconstruction in this TU and their real (possibly non-trivial-dtor)
//      shape. Needs investigation with the real SEH frame present before
//      concluding what is missing.
//   4. Stack frame is 0x14 bytes (ours) vs 0x28 (retail) -- 5 missing dwords,
//      consistent with (3): once real EH-guarded temporaries are correctly
//      modelled the frame should grow to match.
//   5. Register allocation: this is kept in ebx in ours vs edi in retail, and
//      esi/edi push order is swapped, both likely downstream of the EH/frame
//      shape (see docs/shape_levers.md "Whole body one callee-saved register
//      apart" and "Register assignment follows local DEFINITION ORDER" levers)
//      rather than needing a specific fix of their own.
//
// NEXT STEP for whoever picks this up: build the 83-dummy-slot local shim
// (mechanical, ~20 lines with a macro), re-run probe.py, then work the
// SEH/frame/register diffs top-down with docs/shape_levers.md -- the class
// layout and every callee identity above should not need to be re-derived.

#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameSlot
{
public:
	Bool isHuman() const;
	UnicodeString getName() const;
};

class GameSpyGameSlot : public GameSlot
{
public:
	void setLoginName(AsciiString name);
	void setProfileID(Int id);
	void setLocale(AsciiString locale);
	void setSlotRankPoints(Int pts);
	void setFavoriteSide(Int side);

private:
	unsigned char m_pad[0x38];
};

struct PlayerInfo
{
	AsciiString m_name;
	AsciiString m_locale;
	Int m_wins, m_losses, m_profileID, m_flags, m_rankPoints, m_side, m_preorder;
};

class PlayerInfoMap;   // std::map<AsciiString,PlayerInfo,AsciiComparator>; unmodelled here

class GameSpyInfoInterfaceShim
{
public:
#define BFME_GSI_VSLOT(n) virtual void bfmeSlot##n();
	BFME_GSI_VSLOT(0) BFME_GSI_VSLOT(1) BFME_GSI_VSLOT(2) BFME_GSI_VSLOT(3) BFME_GSI_VSLOT(4)
	BFME_GSI_VSLOT(5) BFME_GSI_VSLOT(6) BFME_GSI_VSLOT(7) BFME_GSI_VSLOT(8) BFME_GSI_VSLOT(9)
	BFME_GSI_VSLOT(10) BFME_GSI_VSLOT(11) BFME_GSI_VSLOT(12) BFME_GSI_VSLOT(13) BFME_GSI_VSLOT(14)
	BFME_GSI_VSLOT(15) BFME_GSI_VSLOT(16) BFME_GSI_VSLOT(17) BFME_GSI_VSLOT(18) BFME_GSI_VSLOT(19)
	BFME_GSI_VSLOT(20) BFME_GSI_VSLOT(21) BFME_GSI_VSLOT(22) BFME_GSI_VSLOT(23) BFME_GSI_VSLOT(24)
	BFME_GSI_VSLOT(25) BFME_GSI_VSLOT(26) BFME_GSI_VSLOT(27) BFME_GSI_VSLOT(28) BFME_GSI_VSLOT(29)
	BFME_GSI_VSLOT(30) BFME_GSI_VSLOT(31) BFME_GSI_VSLOT(32) BFME_GSI_VSLOT(33) BFME_GSI_VSLOT(34)
	BFME_GSI_VSLOT(35) BFME_GSI_VSLOT(36) BFME_GSI_VSLOT(37) BFME_GSI_VSLOT(38) BFME_GSI_VSLOT(39)
	BFME_GSI_VSLOT(40) BFME_GSI_VSLOT(41) BFME_GSI_VSLOT(42) BFME_GSI_VSLOT(43) BFME_GSI_VSLOT(44)
	BFME_GSI_VSLOT(45) BFME_GSI_VSLOT(46) BFME_GSI_VSLOT(47) BFME_GSI_VSLOT(48) BFME_GSI_VSLOT(49)
	BFME_GSI_VSLOT(50) BFME_GSI_VSLOT(51) BFME_GSI_VSLOT(52) BFME_GSI_VSLOT(53) BFME_GSI_VSLOT(54)
	BFME_GSI_VSLOT(55) BFME_GSI_VSLOT(56) BFME_GSI_VSLOT(57) BFME_GSI_VSLOT(58) BFME_GSI_VSLOT(59)
	BFME_GSI_VSLOT(60) BFME_GSI_VSLOT(61) BFME_GSI_VSLOT(62) BFME_GSI_VSLOT(63) BFME_GSI_VSLOT(64)
	BFME_GSI_VSLOT(65) BFME_GSI_VSLOT(66) BFME_GSI_VSLOT(67) BFME_GSI_VSLOT(68) BFME_GSI_VSLOT(69)
	BFME_GSI_VSLOT(70) BFME_GSI_VSLOT(71) BFME_GSI_VSLOT(72) BFME_GSI_VSLOT(73) BFME_GSI_VSLOT(74)
	BFME_GSI_VSLOT(75) BFME_GSI_VSLOT(76) BFME_GSI_VSLOT(77) BFME_GSI_VSLOT(78) BFME_GSI_VSLOT(79)
	BFME_GSI_VSLOT(80) BFME_GSI_VSLOT(81) BFME_GSI_VSLOT(82)
#undef BFME_GSI_VSLOT
	virtual UnsignedInt bfmeGetInternalIP(void);   // real retail slot 0x14c (83)
	virtual UnsignedInt bfmeGetExternalIP(void);   // real retail slot 0x150 (84) -- return width TBD, see note 2 above
	virtual Int bfmeGetLocalProfileID(void);       // NOT YET SLOT-VERIFIED; ZH slot 21 unshifted assumption, needs checking too
	virtual PlayerInfoMap *bfmeGetPlayerInfoMap(void); // NOT YET SLOT-VERIFIED; ZH slot 13 unshifted assumption
};

class GameSpyStagingRoomPartial
{
public:
	Bool m_isQM_placeholder_at_0x43C; // real field is at GameInfo(0x58)+slots(0x3C0)+gameName(4)+id(4)+transport(4)+localName(4)+requiresPassword(1)+allowObservers(1)+pad(6)+exeCRC(4)+iniCRC(4)+version(4) = 0x43C
};

// Not compiled/verified as a whole -- this file records the shim shape and
// the identity evidence for the next agent, per docs/shape_levers.md's
// mandate to record what changed, not just what was tried.

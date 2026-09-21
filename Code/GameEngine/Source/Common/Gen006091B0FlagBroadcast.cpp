// Retail RVA 0x006091B0 (229 bytes). No named caller, vtable slot, or
// canonical BFME class/method proves the owner (tools/callers_of.py finds
// no reaching caller; tools/vtable_lookup.py finds no slot; two prior
// sessions independently reached the same conclusion). The only proven
// this-relative field is a bool at +0x8, so the class keeps the
// address-derived Gen_006091B0 spelling already used by neighbours in this
// file (see Bfme5TinyTwentyNine.cpp's Gen_00609320/Gen_00523380).
//
// WHAT THE BYTES SHOW. A one-byte bool setter with an early-out when the new
// value equals the field already stored at +0x8. On a real change it stores
// the new value, and -- only when the new value is true -- appends
// GameMessage 0x3EB with a literal TRUE boolean argument and pokes
// TheInGameUI (vslot 0xE8) and TheControlBar (vslot 0x14). Every change
// (either direction) then runs Glo012F4B98's paired step runner
// (bfmeRun_00589680, already landed in S3GuardedDelegates3.cpp), mirrors the
// new flag into TheGameLogic+0x11D, and -- only when transitioning to true
// and TheAudioClientUpdate exists -- pokes its vslot 0x3C with a literal
// TRUE. Finally, when g_bfmeGameCW exists, it is reinterpreted as the
// already-landed BfmeLivingWorldManager (same singleton: both classes read
// TheGameLogic-family offset +0x288 as a bool, see
// LivingWorldManagerRva00615B10.cpp and Bfme5TinyTwentyNine.cpp) and one of
// its two already-landed per-flag methods runs; TheGameLogic+0x10C is then
// classified against {0,1,5,7} and the result (0/1) is handed to the
// already-landed Rva0060D5D0Noop stdcall no-op as a tail call.
//
// UNRECOVERED: retail loads g_bfmeGameCW/Glo012F4B98/TheGameLogic into ECX
// immediately before three of these calls even though every one of those
// three callees (bfmeRun_00589680, Rva0060D5D0Noop x2) is already proven to
// ignore its incoming register/stack argument entirely -- most likely those
// call sites are really thiscall member calls that retail's linker folded
// (identical-code-folding) onto the already-landed free-function bodies.
// Reproducing that fold from this TU is not attempted; the calls below use
// the already-landed free-function spellings directly, which leaves a few
// non-relocation bytes (the extra ECX loads) unexplained.

typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	float x, y, z;
};

// Reused from the matched Code/GameEngine/Source/Common/Rva006187D0MoveArmyToPosition.cpp
class GameMessage
{
public:
	virtual ~GameMessage();
	void appendBooleanArgument(Bool value);

private:
	GameMessage *m_next;
	GameMessage *m_prev;
	void *m_list;
	int m_type;
	int m_playerIndex;
	unsigned char m_argCount;
	unsigned char m_padding[3];
	void *m_argList;
	void *m_argTail;
};

class MessageStream
{
public:
	virtual void slot00(void); virtual void slot04(void); virtual void slot08(void);
	virtual void slot0C(void); virtual void slot10(void); virtual void slot14(void);
	virtual void slot18(void); virtual void slot1C(void); virtual void slot20(void);
	virtual void slot24(void); virtual void slot28(void); virtual void slot2C(void);
	virtual void slot30(void);
	virtual GameMessage *appendMessage(UnsignedInt type);
};

extern MessageStream *TheMessageStream;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void slot00(void); virtual void slot04(void); virtual void slot08(void);
	virtual void slot0C(void); virtual void slot10(void); virtual void slot14(void);
	virtual void slot18(void); virtual void slot1C(void); virtual void slot20(void);
	virtual void slot24(void); virtual void slot28(void); virtual void slot2C(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void);
	virtual void slot3C(void); virtual void slot40(void); virtual void slot44(void);
	virtual void slot48(void); virtual void slot4C(void); virtual void slot50(void);
	virtual void slot54(void); virtual void slot58(void); virtual void slot5C(void);
	virtual void slot60(void); virtual void slot64(void); virtual void slot68(void);
	virtual void slot6C(void); virtual void slot70(void); virtual void slot74(void);
	virtual void slot78(void); virtual void slot7C(void); virtual void slot80(void);
	virtual void slot84(void); virtual void slot88(void); virtual void slot8C(void);
	virtual void slot90(void); virtual void slot94(void); virtual void slot98(void);
	virtual void slot9C(void); virtual void slotA0(void); virtual void slotA4(void);
	virtual void slotA8(void); virtual void slotAC(void); virtual void slotB0(void);
	virtual void slotB4(void); virtual void slotB8(void); virtual void slotBC(void);
	virtual void slotC0(void); virtual void slotC4(void); virtual void slotC8(void);
	virtual void slotCC(void); virtual void slotD0(void); virtual void slotD4(void);
	virtual void slotD8(void); virtual void slotDC(void); virtual void slotE0(void);
	virtual void slotE4(void);
	virtual void slotE8(void);
};

extern InGameUI *TheInGameUI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	virtual void slot00(void); virtual void slot04(void); virtual void slot08(void);
	virtual void slot0C(void); virtual void slot10(void);
	virtual void slot14(void);
};

extern ControlBar *TheControlBar;

extern "C" void bfmeRun_00589680(void);

// Retail loads Glo012F4B98 into ECX immediately before this call even though
// bfmeRun_00589680's own (already landed) body never touches ECX -- almost
// certainly a thiscall member whose identical-code-folded body the linker
// merged onto that free function. Route through such a member so the ECX
// setup reappears, and alias its never-defined body onto the real callee.
class Glo012F4B98Type
{
public:
	void run();
};

extern Glo012F4B98Type *Glo012F4B98;

#pragma comment(linker, "/alternatename:?run@Glo012F4B98Type@@QAEXXZ=?bfmeRun_00589680@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unrecovered000[0x10C];
	int m_field10C;
	unsigned char m_unrecovered110[0x11D - 0x110];
	Bool m_field11D;
};

extern GameLogic *TheGameLogic;

class AudioClient
{
public:
	virtual void slot00(void); virtual void slot04(void); virtual void slot08(void);
	virtual void slot0C(void); virtual void slot10(void); virtual void slot14(void);
	virtual void slot18(void); virtual void slot1C(void); virtual void slot20(void);
	virtual void slot24(void); virtual void slot28(void); virtual void slot2C(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void);
	virtual void slot3C(Bool value);
};

extern AudioClient *TheAudioClientUpdate;

// Reused verbatim from the matched
// Code/GameEngine/Source/GameLogic/ScriptEngine/LivingWorldManagerRva00615B10.cpp
// and LivingWorldManagerRva00615C20.cpp.
class BfmeLivingWorldManager
{
public:
	void rva00615b10();
	void rva00615c20();
};

extern "C" void __stdcall Rva0060D5D0Noop(void *);

// The class both this view and Bfme5TinyTwentyNine.cpp's BfmeGameCW read the
// same singleton at +0x288 through, so g_bfmeGameCW is the same object as
// the BfmeLivingWorldManager the two rva006159xx methods above already prove.
// Retail reloads g_bfmeGameCW into ECX immediately before each tail call to
// the already-landed Rva0060D5D0Noop stdcall no-op, which never touches
// ECX -- the same identical-code-folded-thiscall-member shape as
// Glo012F4B98Type::run above, so route through a member here too.
class BfmeGameCW
{
public:
	void poke(int value);
};

extern BfmeGameCW *g_bfmeGameCW;

#pragma comment(linker, "/alternatename:?poke@BfmeGameCW@@QAEXH@Z=?Rva0060D5D0Noop@@YGXPAX@Z")

class Gen_006091B0
{
public:
	void bfmeSetEnabled(Bool enable);

private:
	unsigned char m_bfmeHead[8];
	Bool m_bfmeFlag;
};

// ?bfmeSetEnabled@Gen_006091B0@@QAEX_N@Z
void Gen_006091B0::bfmeSetEnabled(Bool enable)
{
	if (enable == m_bfmeFlag)
		return;

	m_bfmeFlag = enable;

	if (enable)
	{
		GameMessage *msg = TheMessageStream->appendMessage(0x3EB);
		msg->appendBooleanArgument(true);
		TheInGameUI->slotE8();
		TheControlBar->slot14();
	}

	Glo012F4B98->run();

	TheGameLogic->m_field11D = m_bfmeFlag;

	if (TheAudioClientUpdate && m_bfmeFlag)
		TheAudioClientUpdate->slot3C(true);

	if (g_bfmeGameCW)
	{
		BfmeLivingWorldManager *manager = (BfmeLivingWorldManager *)g_bfmeGameCW;
		if (m_bfmeFlag)
			manager->rva00615b10();
		else
			manager->rva00615c20();

		int state = TheGameLogic->m_field10C;
		int value = (state == 0 || state == 7 || state == 1 || state == 5) ? 1 : 0;
		g_bfmeGameCW->poke(value);
	}
}

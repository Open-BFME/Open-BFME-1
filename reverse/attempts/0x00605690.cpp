// ??0Rva00605690Owner@@QAE@ABVGameSpyGroupRoom@@H@Z
// partial score=0.91 date=2026-09-21
// cl: /O2 /Ob0
#include <string.h>
// Retail 0x00605690 (?d_00605690@@YAXXZ, dump d_00601890.asm).
// One caller, itself a still-dump body (?d_006059f0@@YAXXZ). Full field
// layout and both parameter slots are solid: base-copy-construct a 4-byte
// GameSpyGroupRoom subobject (matched ??0GameSpyGroupRoom@@QAE@ABV0@@Z,
// generic single-int shared copy ctor pinned in symbols.csv), then
// m_4 = 0, m_8 = kind, then two 40-byte zero regions at +0xc and +0x34
// (memset() reproduces retail's lea+shared-edx store shape exactly), then
// a trailing zero byte at +0x5c. No named caller or owning class;
// everything below the base copy is address-derived.
//
// RESIDUE (9/100 bytes, all in one 7-byte window): retail materialises
// BOTH constants it needs anywhere in the body (xor edx,edx for the two
// memsets; xor eax,eax for m_4 and the trailing m_5c byte) in one batch
// BEFORE storing m_4 and m_8, in program order m_4 then m_8. Every source
// shape tried (init-list m_4(0),m_8(kind); body assignment in various
// orders; memsets before/after) has the *same two constants*, the *same
// three stores*, and the *same final byte count* -- only the scheduler's
// choice of when to interleave the m_8 store (which has no dependency on
// either xor and so is free to move) differs, and no source reordering
// changed it. Independently confirmed by an earlier Codex session with the
// same 1-instruction residue. Needs a genuine store-scheduling lever, not
// yet documented.

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &other);

	int m_id;
};

class Rva00605690Owner : public GameSpyGroupRoom
{
public:
	Rva00605690Owner(const GameSpyGroupRoom &room, int kind);

	int m_4;
	int m_8;
	int m_c[10];
	int m_34[10];
	unsigned char m_5c;
};

Rva00605690Owner::Rva00605690Owner(const GameSpyGroupRoom &room, int kind)
	: GameSpyGroupRoom(room), m_4(0), m_8(kind)
{
	memset(m_c, 0, sizeof(m_c));
	memset(m_34, 0, sizeof(m_34));
	m_5c = 0;
}

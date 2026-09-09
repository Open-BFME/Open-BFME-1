// ??0GlobalData@@QAE@XZ
// partial score=0.19 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
//
// Open-BFME5: GlobalData::GlobalData(), retail 0x00084510, 4621 bytes
// (the ledger's 4499-byte estimate was stale -- the extent ends in `ret`
// at +0x120c, confirmed with dis_retail.py; this is the real boundary).
//
// STRUCTURAL DRAFT, not yet byte-exact. This is the store-run-constructor /
// unwind-state lever from docs/shape_levers.md applied at scale: the /EHsc
// FuncInfo at VA 0x011E2888 lists 50 states (build/ehmap.py), each a
// destructible sub-object of GlobalData in DECLARATION order. Every state's
// funclet was disassembled (mov ecx,[ebp-0x10134]; add ecx,<offset>; jmp
// <dtor>, or the eh-vector iterator form for arrays) to recover the member
// list below -- offset, size and destructor identity for all 49 of
// GlobalData's own destructible members (state 0 destroys the inherited
// SubsystemInterface base).
//
// Every destructible type below is REUSED, not re-modelled:
//   - BFMERetailAsciiString: the project's standard AsciiString stand-in
//     (dtor ILT 0x0000D828, already pinned everywhere).
//   - _STL::vector<BFMERetailAsciiString>: dtor already pinned at 0x000658A0
//     under this exact template spelling (symbols.csv:4134) -- ICF-folded
//     onto ??1PlayerUpgradeSpecialPowerModuleData, confirmed by inspecting
//     the callee body's loop shape and by SubsystemLegend.cpp's own working
//     vector<AsciiString> member using the same dtor address.
//   - AttributeHandleStandIn: already a MATCHED class (ctor 0x0003747A, dtor
//     0x0039D550) in AttributeHandleStandInDestructor.cpp /
//     AttributeModifierAuraUpdateModuleDataCtorThunk.cpp -- declared here,
//     not redefined, so the linker resolves to the existing body.
//   - Coord3D: real, already-matched class (coord3d.cpp; default ctor
//     0x00016C93->0x00083330, 3 bytes, dtor 0x00016C93 thunk chain ends at
//     ??1Coord3D). Minimal local redeclaration (name + size only) to avoid
//     pulling in the full header graph, exactly like BFMERetailAsciiString
//     stands in for the real AsciiString elsewhere in this project.
//   - Rva00083150: already-matched class (Rva00083150Ctor.cpp) -- a 0x300
//     byte, six-row/32-float grid defaulted to 1.0f, called via a plain
//     thiscall ctor with NO unwind state (its own ctor cannot throw, so it
//     never got a state slot -- that is why 50 states cover only 49 of
//     GlobalData's members plus the SubsystemInterface base).
//   - BfmeGdElem36 / BfmeGdUnicodeString: two NEW stand-ins, pinned below.
//     BfmeGdElem36 is a 36-byte element (three 18-element array members at
//     +0x224/+0x4ac/+0x734) whose real ctor (0x00083440: mov eax,ecx / ret)
//     and dtor (0x00083450: ret) are BOTH empty -- confirmed by disassembly,
//     so the element's actual field layout is irrelevant to this function's
//     bytes and is left as an opaque byte blob.  BfmeGdUnicodeString's dtor
//     is retail's own real UnicodeString release path (0x0045EEA0 is an ILT
//     that jumps to the already-pinned ??1UnicodeString@@QAE@XZ body at
//     0x008881D0); a locally-named stand-in avoids an ODR clash with the
//     full UnicodeString class already defined in
//     Code/GameEngine/Source/Common/System/UnicodeString.cpp.
//
// UPDATE (worker W6, wave 2): the assigned brief's "CRC tail" theory for the
// 0x10138-byte __chkstk frame is WRONG -- checked directly against the full
// call list of the retail body (every `call`/`call [..]` instruction from
// +0x0 to +0x120c, 47 total): there is NO GetModuleFileName, NO File::open,
// NO read loop and NO CRC object anywhere in this function. The only import
// call is `call dword ptr [0x1359000]` at +0x0ffe, which reverse/imports.csv
// identifies as USER32!GetDoubleClickTime (matches ZH's tail-of-ctor
// `m_doubleClickTimeMS = GetDoubleClickTime();`, so the general "this is
// ZH's ctor tail" mapping still holds -- just not the CRC part). The other
// unresolved tail calls (0x1b76b, 0xa984, 0x2f923, 0x3f508) are all
// already-matched `gen-thunk` placeholder rows (Code/gen_small/thunks_*.cpp)
// -- 5-byte jump stubs to FUN_004aea50 / FUN_00465250 / etc, not identified
// real callees yet.
//
// What the buffer actually IS is still unresolved, but its SIZE is now
// pinned empirically: adding an unused (one volatile byte touched) local
// `char[0x10134]` reproduces retail's exact `mov eax, 0x10138` / __chkstk
// prologue (0x10134 local + 4 bytes compiler overhead = 0x10138) and pushes
// the first diff from the missing-chkstk-call point to the next one (score
// 2774 -> 2820 bytes, still far short of 4621). Per docs/shape_levers.md
// "frame first": this only gets the PROLOGUE aligned; everything after it
// still needs real content, at which point the buffer's shape may turn out
// to matter (e.g. if it's really several arrays MSVC coalesced).
//
// New lead for the NEXT diff (right after the chkstk fix): retail's prologue
// pushes ebx, ebp, esi, edi (4 callee-saved regs) but this draft's compiled
// output only pushes esi/edi (no ebp) at that point -- ebp is never used
// because this draft has no real loop. ZH's constructor has a genuine
// `for (i = 0; i < MAX_WATER_GRID_SETTINGS; i++) { ...12 stores...
// m_vertexWaterAvailableMaps[i].clear(); }` block; a loop with that much
// per-iteration work is a strong candidate for the compiler hoisting the
// induction variable into a 4th callee-saved register (ebp) across the many
// calls inside the loop body (AsciiString::clear() per iteration). Writing
// that loop as a REAL for-loop (not unrolled stores) instead of flat
// m_pad_XXXX blocks is the next thing to try, once MAX_WATER_GRID_SETTINGS
// and the array's BFME offset/stride are confirmed from the disassembly.
//
// NOT YET DONE (why this is a partial, not a landed body):
//   - The ~230 plain scalar members between the destructible ones are
//     represented as raw `unsigned char m_pad_XXXX[N]` blocks, not typed
//     fields with retail's actual constants. build/stores2.txt (generated
//     in this session, not carried in this commit) has every individual
//     store already decoded to (offset, size, value) -- someone continuing
//     this body should replay that table into typed members inside each pad
//     run instead of re-disassembling.
//   - At least three call sites (+0x40f/+0x421 `RetailLayoutString::set`,
//     +0xc72 `UnicodeString::set`) assign LITERAL STRING content to specific
//     AsciiString/UnicodeString members -- these need the literal bytes read
//     out of retail's .rdata and are not yet reproduced.
//   - GlobalData's own vtable store (`mov dword ptr [esi], 0x0107C68C` right
//     after the SubsystemInterface base ctor call) has no pin yet; nothing
//     in this file forces our compiled vtable to that literal.
//   - A handful of trailing calls past +0xf60 (thunks 0x1b76b, 0xa984,
//     0x2f923, an indirect call through edi, 0x3f508, and an __imp_ call
//     through [0x1359000]) are not yet decoded.
//
// The size below is verified: SubsystemInterface (8) + the member list =
// 0x1290, matching newOverride's own comment that `operator new` is handed
// 0x1290 and m_next lives at +0x128c.

class SubsystemInterface
{
public:
	SubsystemInterface();                                      ///< matched 0x009A1A30
	virtual ~SubsystemInterface();                              ///< matched 0x009A1A40

private:
	unsigned int m_pad04;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) { }
	~BFMERetailAsciiString();

	void *m_data;
};

// AttributeHandleStandIn: already matched at
// Code/GameEngine/Source/GameLogic/Object/Update/AttributeHandleStandInDestructor.cpp
// (dtor 0x0039D550) / AttributeModifierAuraUpdateModuleDataCtorThunk.cpp
// (ctor pinned 0x0003747A). Declared, not redefined.
class AttributeHandleStandIn
{
public:
	AttributeHandleStandIn();
	~AttributeHandleStandIn();

private:
	unsigned int m_value;
};

// Real, already-matched class (Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp).
// Minimal local redeclaration: name + size only, ctor/dtor resolved externally.
class Coord3D
{
public:
	Coord3D();
	~Coord3D();

private:
	float x, y, z;
};

// Already-matched class (Code/GameEngine/Source/Common/Rva00083150Ctor.cpp):
// six rows of 32 floats, all defaulted to 1.0f, nothrow ctor (no unwind state).
class Rva00083150
{
public:
	Rva00083150();

private:
	unsigned int m_grid[6][32];
};

// New stand-in: retail's element ctor (0x00083440: mov eax,ecx / ret) and
// dtor (0x00083450: ret) are both empty, so the field layout does not matter
// to this function's bytes.  Pinned below.
class BfmeGdElem36
{
public:
	BfmeGdElem36() { }
	~BfmeGdElem36() { }

private:
	unsigned char m_data[36];
};

// New stand-in for the UnicodeString-shaped member at +0x1280.  Retail's
// dtor call goes through ILT 0x0045EEA0, which itself jumps to the
// already-pinned ??1UnicodeString@@QAE@XZ body at 0x008881D0. A locally
// named class avoids redefining the real UnicodeString from
// Code/GameEngine/Source/Common/System/UnicodeString.cpp in this TU.
class BfmeGdUnicodeString
{
public:
	BfmeGdUnicodeString() : m_data(0) { }
	~BfmeGdUnicodeString();

private:
	void *m_data;
};

class GlobalData : public SubsystemInterface
{
public:
	GlobalData();

private:
	BFMERetailAsciiString m_str_8;				///< +0x8
	BFMERetailAsciiString m_str_c;				///< +0xc
	BFMERetailAsciiString m_str_10;				///< +0x10
	BFMERetailAsciiString m_str_14;				///< +0x14
	unsigned char m_18;				///< +0x18
	unsigned char m_19;				///< +0x19
	unsigned char m_1a;				///< +0x1a
	unsigned char m_1b;				///< +0x1b
	unsigned char m_1c;				///< +0x1c
	unsigned char m_1d;				///< +0x1d
	unsigned char m_1e;				///< +0x1e
	unsigned char m_1f;				///< +0x1f
	unsigned char m_20;				///< +0x20
	unsigned int m_24;				///< +0x24
	unsigned char m_28;				///< +0x28
	unsigned char m_29;				///< +0x29
	unsigned char m_2a;				///< +0x2a
	unsigned int m_2c;				///< +0x2c
	unsigned int m_30;				///< +0x30
	unsigned int m_34;				///< +0x34
	unsigned char m_38;				///< +0x38
	unsigned char m_39;				///< +0x39
	unsigned char m_3a;				///< +0x3a
	unsigned char m_3b;				///< +0x3b
	unsigned char m_3c;				///< +0x3c
	unsigned int m_40;				///< +0x40
	unsigned char m_44;				///< +0x44
	unsigned char m_45;				///< +0x45
	unsigned char m_46;				///< +0x46
	unsigned int m_48;				///< +0x48
	unsigned char m_4c;				///< +0x4c
	unsigned char m_4d;				///< +0x4d
	unsigned char m_4e;				///< +0x4e
	unsigned char m_4f;				///< +0x4f
	unsigned char m_50;				///< +0x50
	unsigned int m_54;				///< +0x54
	unsigned char m_58;				///< +0x58
	unsigned char m_59;				///< +0x59
	unsigned int m_5c;				///< +0x5c
	unsigned char m_60;				///< +0x60
	unsigned char m_61;				///< +0x61
	unsigned char m_62;				///< +0x62
	unsigned char m_63;				///< +0x63
	unsigned char m_64;				///< +0x64
	unsigned char m_65;				///< +0x65
	unsigned int m_68;				///< +0x68
	unsigned int m_6c;				///< +0x6c
	unsigned char m_70;				///< +0x70
	unsigned int m_74;				///< +0x74
	unsigned int m_78;				///< +0x78
	unsigned int m_7c;				///< +0x7c
	unsigned int m_80;				///< +0x80
	unsigned int m_84;				///< +0x84
	unsigned int m_88;				///< +0x88
	unsigned char m_8c;				///< +0x8c
	unsigned char m_8d;				///< +0x8d
	unsigned char m_8e;				///< +0x8e
	unsigned char m_8f;				///< +0x8f
	unsigned char m_90;				///< +0x90
	unsigned char m_pad_21[0x3];				///< +0x21
	unsigned char m_pad_2b[0x1];				///< +0x2b
	unsigned char m_pad_3d[0x3];				///< +0x3d
	unsigned char m_pad_47[0x1];				///< +0x47
	unsigned char m_pad_51[0x3];				///< +0x51
	unsigned char m_pad_5a[0x2];				///< +0x5a
	unsigned char m_pad_66[0x2];				///< +0x66
	unsigned char m_pad_71[0x3];				///< +0x71
	unsigned char m_pad_91[0x3];				///< +0x91
	BFMERetailAsciiString m_str_94;				///< +0x94
	unsigned int m_98;				///< +0x98
	BFMERetailAsciiString m_strArr_9c[4];				///< +0x9c
	unsigned int m_ac;				///< +0xac
	unsigned int m_bc;				///< +0xbc
	unsigned int m_cc;				///< +0xcc
	unsigned int m_dc;				///< +0xdc
	unsigned int m_ec;				///< +0xec
	unsigned int m_fc;				///< +0xfc
	unsigned int m_10c;				///< +0x10c
	unsigned int m_11c;				///< +0x11c
	unsigned int m_12c;				///< +0x12c
	unsigned int m_13c;				///< +0x13c
	unsigned int m_14c;				///< +0x14c
	unsigned int m_15c;				///< +0x15c
	unsigned int m_16c;				///< +0x16c
	unsigned int m_180;				///< +0x180
	unsigned int m_190;				///< +0x190
	unsigned int m_194;				///< +0x194
	unsigned int m_198;				///< +0x198
	unsigned int m_19c;				///< +0x19c
	unsigned int m_1a4;				///< +0x1a4
	unsigned int m_1a8;				///< +0x1a8
	unsigned int m_1b0;				///< +0x1b0
	unsigned char m_1b8;				///< +0x1b8
	unsigned int m_1bc;				///< +0x1bc
	unsigned int m_1c0;				///< +0x1c0
	unsigned int m_1c4;				///< +0x1c4
	unsigned int m_1c8;				///< +0x1c8
	unsigned int m_1cc;				///< +0x1cc
	unsigned int m_1d0;				///< +0x1d0
	unsigned int m_1d4;				///< +0x1d4
	unsigned int m_1d8;				///< +0x1d8
	unsigned int m_1dc;				///< +0x1dc
	unsigned int m_1e0;				///< +0x1e0
	unsigned int m_1e4;				///< +0x1e4
	unsigned int m_1e8;				///< +0x1e8
	unsigned int m_1ec;				///< +0x1ec
	unsigned int m_1f0;				///< +0x1f0
	unsigned char m_pad_b0[0xc];				///< +0xb0
	unsigned char m_pad_c0[0xc];				///< +0xc0
	unsigned char m_pad_d0[0xc];				///< +0xd0
	unsigned char m_pad_e0[0xc];				///< +0xe0
	unsigned char m_pad_f0[0xc];				///< +0xf0
	unsigned char m_pad_100[0xc];				///< +0x100
	unsigned char m_pad_110[0xc];				///< +0x110
	unsigned char m_pad_120[0xc];				///< +0x120
	unsigned char m_pad_130[0xc];				///< +0x130
	unsigned char m_pad_140[0xc];				///< +0x140
	unsigned char m_pad_150[0xc];				///< +0x150
	unsigned char m_pad_160[0xc];				///< +0x160
	unsigned char m_pad_170[0x10];				///< +0x170
	unsigned char m_pad_184[0xc];				///< +0x184
	unsigned char m_pad_1a0[0x4];				///< +0x1a0
	unsigned char m_pad_1ac[0x4];				///< +0x1ac
	unsigned char m_pad_1b4[0x4];				///< +0x1b4
	unsigned char m_pad_1b9[0x3];				///< +0x1b9
	unsigned char m_pad_1f4[0xc];				///< +0x1f4
	BFMERetailAsciiString m_str_200;				///< +0x200
	unsigned int m_204;				///< +0x204
	unsigned int m_208;				///< +0x208
	BFMERetailAsciiString m_str_20c;				///< +0x20c
	unsigned int m_210;				///< +0x210
	unsigned int m_214;				///< +0x214
	unsigned int m_21c;				///< +0x21c
	unsigned char m_220;				///< +0x220
	unsigned char m_221;				///< +0x221
	unsigned char m_222;				///< +0x222
	unsigned char m_223;				///< +0x223
	unsigned char m_pad_218[0x4];				///< +0x218
	BfmeGdElem36 m_elem36_224[18];				///< +0x224
	BfmeGdElem36 m_elem36_4ac[18];				///< +0x4ac
	BfmeGdElem36 m_elem36_734[18];				///< +0x734
	unsigned int m_9bc;				///< +0x9bc
	unsigned int m_9c0;				///< +0x9c0
	unsigned int m_9c4;				///< +0x9c4
	unsigned int m_9e0;				///< +0x9e0
	unsigned int m_9e4;				///< +0x9e4
	unsigned int m_9e8;				///< +0x9e8
	unsigned char m_pad_9c8[0x18];				///< +0x9c8
	unsigned char m_pad_9ec[0x18];				///< +0x9ec
	Coord3D m_coord3d_a04[3];				///< +0xa04
	unsigned int m_a28;				///< +0xa28
	unsigned int m_a2c;				///< +0xa2c
	unsigned int m_a30;				///< +0xa30
	unsigned int m_a34;				///< +0xa34
	unsigned int m_a38;				///< +0xa38
	unsigned int m_a3c;				///< +0xa3c
	unsigned int m_a40;				///< +0xa40
	unsigned int m_a44;				///< +0xa44
	unsigned int m_a48;				///< +0xa48
	unsigned int m_a4c;				///< +0xa4c
	unsigned int m_a50;				///< +0xa50
	unsigned int m_a54;				///< +0xa54
	unsigned int m_a5c;				///< +0xa5c
	unsigned int m_a60;				///< +0xa60
	unsigned int m_a64;				///< +0xa64
	unsigned int m_a68;				///< +0xa68
	unsigned char m_a6c;				///< +0xa6c
	unsigned char m_a6d;				///< +0xa6d
	unsigned char m_a6e;				///< +0xa6e
	unsigned char m_a6f;				///< +0xa6f
	unsigned char m_a70;				///< +0xa70
	unsigned char m_a71;				///< +0xa71
	unsigned char m_a72;				///< +0xa72
	unsigned char m_a73;				///< +0xa73
	unsigned char m_a74;				///< +0xa74
	unsigned char m_a75;				///< +0xa75
	unsigned char m_a76;				///< +0xa76
	unsigned char m_a77;				///< +0xa77
	unsigned char m_a7c;				///< +0xa7c
	unsigned char m_a7d;				///< +0xa7d
	unsigned char m_a7e;				///< +0xa7e
	unsigned char m_a7f;				///< +0xa7f
	unsigned char m_a80;				///< +0xa80
	unsigned char m_a81;				///< +0xa81
	unsigned int m_a84;				///< +0xa84
	unsigned int m_a88;				///< +0xa88
	unsigned char m_a8c;				///< +0xa8c
	unsigned char m_a8d;				///< +0xa8d
	unsigned char m_a8e;				///< +0xa8e
	unsigned char m_a8f;				///< +0xa8f
	unsigned char m_a90;				///< +0xa90
	unsigned char m_a91;				///< +0xa91
	unsigned char m_a92;				///< +0xa92
	unsigned char m_a93;				///< +0xa93
	unsigned char m_a94;				///< +0xa94
	unsigned char m_a95;				///< +0xa95
	unsigned char m_a96;				///< +0xa96
	unsigned char m_a97;				///< +0xa97
	unsigned int m_a98;				///< +0xa98
	unsigned char m_a9c;				///< +0xa9c
	unsigned char m_a9d;				///< +0xa9d
	unsigned char m_a9e;				///< +0xa9e
	unsigned char m_a9f;				///< +0xa9f
	unsigned char m_aa0;				///< +0xaa0
	unsigned char m_pad_a58[0x4];				///< +0xa58
	unsigned char m_pad_a78[0x4];				///< +0xa78
	unsigned char m_pad_a82[0x2];				///< +0xa82
	unsigned char m_pad_aa1[0x3];				///< +0xaa1
	BFMERetailAsciiString m_str_aa4;				///< +0xaa4
	BFMERetailAsciiString m_str_aa8;				///< +0xaa8
	unsigned char m_aac;				///< +0xaac
	unsigned int m_ab0;				///< +0xab0
	unsigned int m_ab4;				///< +0xab4
	unsigned char m_pad_aad[0x3];				///< +0xaad
	BFMERetailAsciiString m_str_ab8;				///< +0xab8
	BFMERetailAsciiString m_str_abc;				///< +0xabc
	unsigned int m_ac0;				///< +0xac0
	BFMERetailAsciiString m_str_ac4;				///< +0xac4
	BFMERetailAsciiString m_str_ac8;				///< +0xac8
	unsigned int m_acc;				///< +0xacc
	BFMERetailAsciiString m_str_ad0;				///< +0xad0
	BFMERetailAsciiString m_str_ad4;				///< +0xad4
	unsigned int m_ad8;				///< +0xad8
	BFMERetailAsciiString m_str_adc;				///< +0xadc
	BFMERetailAsciiString m_str_ae0;				///< +0xae0
	unsigned int m_ae4;				///< +0xae4
	BFMERetailAsciiString m_str_ae8;				///< +0xae8
	BFMERetailAsciiString m_str_aec;				///< +0xaec
	unsigned int m_af0;				///< +0xaf0
	BFMERetailAsciiString m_str_af4;				///< +0xaf4
	BFMERetailAsciiString m_str_af8;				///< +0xaf8
	unsigned int m_afc;				///< +0xafc
	BFMERetailAsciiString m_str_b00;				///< +0xb00
	BFMERetailAsciiString m_str_b04;				///< +0xb04
	unsigned int m_b08;				///< +0xb08
	unsigned int m_b10;				///< +0xb10
	unsigned int m_b14;				///< +0xb14
	unsigned char m_b18;				///< +0xb18
	unsigned int m_b1c;				///< +0xb1c
	unsigned short m_b20;				///< +0xb20
	unsigned int m_b2c;				///< +0xb2c
	unsigned int m_b30;				///< +0xb30
	unsigned int m_b34;				///< +0xb34
	unsigned int m_b38;				///< +0xb38
	unsigned int m_b3c;				///< +0xb3c
	unsigned int m_b40;				///< +0xb40
	unsigned int m_b44;				///< +0xb44
	unsigned int m_b48;				///< +0xb48
	unsigned int m_b4c;				///< +0xb4c
	unsigned int m_b54;				///< +0xb54
	unsigned int m_b58;				///< +0xb58
	unsigned int m_b5c;				///< +0xb5c
	unsigned int m_b60;				///< +0xb60
	unsigned int m_b64;				///< +0xb64
	unsigned int m_b68;				///< +0xb68
	unsigned int m_b6c;				///< +0xb6c
	unsigned char m_b7c;				///< +0xb7c
	unsigned char m_b7d;				///< +0xb7d
	unsigned char m_pad_b0c[0x4];				///< +0xb0c
	unsigned char m_pad_b19[0x3];				///< +0xb19
	unsigned char m_pad_b22[0xa];				///< +0xb22
	unsigned char m_pad_b50[0x4];				///< +0xb50
	unsigned char m_pad_b70[0xc];				///< +0xb70
	unsigned char m_pad_b7e[0x2];				///< +0xb7e
	BFMERetailAsciiString m_str_b80;				///< +0xb80
	BFMERetailAsciiString m_str_b84;				///< +0xb84
	unsigned char m_b88;				///< +0xb88
	unsigned int m_b8c;				///< +0xb8c
	unsigned int m_b94;				///< +0xb94
	unsigned int m_b98;				///< +0xb98
	unsigned int m_b9c;				///< +0xb9c
	unsigned int m_ba0;				///< +0xba0
	unsigned int m_ba4;				///< +0xba4
	unsigned int m_ba8;				///< +0xba8
	unsigned int m_bac;				///< +0xbac
	unsigned char m_pad_b89[0x3];				///< +0xb89
	unsigned char m_pad_b90[0x4];				///< +0xb90
	BFMERetailAsciiString m_str_bb0;				///< +0xbb0
	unsigned char m_bb4;				///< +0xbb4
	unsigned char m_bb5;				///< +0xbb5
	unsigned char m_bb6;				///< +0xbb6
	unsigned char m_bb7;				///< +0xbb7
	unsigned char m_bb8;				///< +0xbb8
	unsigned char m_bb9;				///< +0xbb9
	unsigned int m_bbc;				///< +0xbbc
	unsigned int m_bc0;				///< +0xbc0
	unsigned char m_bc4;				///< +0xbc4
	unsigned char m_bc5;				///< +0xbc5
	unsigned int m_bc8;				///< +0xbc8
	unsigned int m_bd0;				///< +0xbd0
	unsigned int m_be0;				///< +0xbe0
	unsigned int m_be4;				///< +0xbe4
	unsigned int m_bf0;				///< +0xbf0
	unsigned char m_bf4;				///< +0xbf4
	unsigned int m_bfc;				///< +0xbfc
	unsigned int m_c00;				///< +0xc00
	unsigned char m_c04;				///< +0xc04
	unsigned char m_c05;				///< +0xc05
	unsigned char m_c06;				///< +0xc06
	unsigned char m_c07;				///< +0xc07
	unsigned char m_c08;				///< +0xc08
	unsigned char m_c09;				///< +0xc09
	unsigned char m_c0a;				///< +0xc0a
	unsigned char m_c0b;				///< +0xc0b
	unsigned char m_c0c;				///< +0xc0c
	unsigned char m_c0d;				///< +0xc0d
	unsigned int m_c10;				///< +0xc10
	unsigned int m_c14;				///< +0xc14
	unsigned int m_c30;				///< +0xc30
	unsigned int m_c34;				///< +0xc34
	unsigned int m_c38;				///< +0xc38
	unsigned char m_pad_bba[0x2];				///< +0xbba
	unsigned char m_pad_bc6[0x2];				///< +0xbc6
	unsigned char m_pad_bcc[0x4];				///< +0xbcc
	unsigned char m_pad_bd4[0xc];				///< +0xbd4
	unsigned char m_pad_be8[0x8];				///< +0xbe8
	unsigned char m_pad_bf5[0x7];				///< +0xbf5
	unsigned char m_pad_c0e[0x2];				///< +0xc0e
	unsigned char m_pad_c18[0x18];				///< +0xc18
	unsigned char m_pad_c3c[0x4];				///< +0xc3c
	BFMERetailAsciiString m_str_c40;				///< +0xc40
	_STL::vector<BFMERetailAsciiString> m_vec_c44;				///< +0xc44
	unsigned char m_c50;				///< +0xc50
	unsigned char m_c58;				///< +0xc58
	unsigned char m_c59;				///< +0xc59
	unsigned int m_c64;				///< +0xc64
	unsigned int m_c68;				///< +0xc68
	unsigned int m_c6c;				///< +0xc6c
	unsigned char m_c70;				///< +0xc70
	unsigned int m_c74;				///< +0xc74
	unsigned int m_c78;				///< +0xc78
	unsigned int m_c7c;				///< +0xc7c
	unsigned int m_c80;				///< +0xc80
	unsigned char m_c84;				///< +0xc84
	unsigned char m_c85;				///< +0xc85
	unsigned char m_c86;				///< +0xc86
	unsigned int m_c88;				///< +0xc88
	unsigned int m_c8c;				///< +0xc8c
	unsigned int m_c90;				///< +0xc90
	unsigned char m_ca0;				///< +0xca0
	unsigned int m_ca4;				///< +0xca4
	unsigned int m_cb0;				///< +0xcb0
	unsigned int m_cb4;				///< +0xcb4
	unsigned char m_cf0;				///< +0xcf0
	unsigned char m_cf1;				///< +0xcf1
	unsigned char m_cf2;				///< +0xcf2
	unsigned char m_cf3;				///< +0xcf3
	unsigned char m_cf4;				///< +0xcf4
	unsigned char m_cf5;				///< +0xcf5
	unsigned char m_cf6;				///< +0xcf6
	unsigned char m_cf7;				///< +0xcf7
	unsigned char m_cf8;				///< +0xcf8
	unsigned char m_cf9;				///< +0xcf9
	unsigned char m_cfa;				///< +0xcfa
	unsigned char m_cfb;				///< +0xcfb
	unsigned char m_cfc;				///< +0xcfc
	unsigned char m_d04;				///< +0xd04
	unsigned char m_d05;				///< +0xd05
	unsigned int m_d08;				///< +0xd08
	unsigned char m_d0c;				///< +0xd0c
	unsigned char m_d0d;				///< +0xd0d
	unsigned int m_d18;				///< +0xd18
	unsigned char m_d1c;				///< +0xd1c
	unsigned int m_d24;				///< +0xd24
	unsigned char m_d28;				///< +0xd28
	unsigned int m_d30;				///< +0xd30
	unsigned char m_d58;				///< +0xd58
	unsigned int m_d60;				///< +0xd60
	unsigned char m_d84;				///< +0xd84
	unsigned char m_d85;				///< +0xd85
	unsigned char m_d86;				///< +0xd86
	unsigned char m_d87;				///< +0xd87
	unsigned char m_d88;				///< +0xd88
	unsigned char m_d89;				///< +0xd89
	unsigned char m_d8a;				///< +0xd8a
	unsigned char m_d8b;				///< +0xd8b
	unsigned char m_pad_c51[0x7];				///< +0xc51
	unsigned char m_pad_c5a[0xa];				///< +0xc5a
	unsigned char m_pad_c71[0x3];				///< +0xc71
	unsigned char m_pad_c87[0x1];				///< +0xc87
	unsigned char m_pad_c94[0xc];				///< +0xc94
	unsigned char m_pad_ca1[0x3];				///< +0xca1
	unsigned char m_pad_ca8[0x8];				///< +0xca8
	unsigned char m_pad_cb8[0x38];				///< +0xcb8
	unsigned char m_pad_cfd[0x7];				///< +0xcfd
	unsigned char m_pad_d06[0x2];				///< +0xd06
	unsigned char m_pad_d0e[0xa];				///< +0xd0e
	unsigned char m_pad_d1d[0x7];				///< +0xd1d
	unsigned char m_pad_d29[0x7];				///< +0xd29
	unsigned char m_pad_d34[0x24];				///< +0xd34
	unsigned char m_pad_d59[0x7];				///< +0xd59
	unsigned char m_pad_d64[0x20];				///< +0xd64
	BFMERetailAsciiString m_str_d8c;				///< +0xd8c
	BFMERetailAsciiString m_str_d90;				///< +0xd90
	unsigned int m_d94;				///< +0xd94
	unsigned int m_d98;				///< +0xd98
	unsigned int m_d9c;				///< +0xd9c
	unsigned int m_da0;				///< +0xda0
	unsigned int m_da4;				///< +0xda4
	unsigned int m_da8;				///< +0xda8
	unsigned char m_dac;				///< +0xdac
	unsigned char m_db4;				///< +0xdb4
	unsigned char m_db5;				///< +0xdb5
	unsigned char m_db6;				///< +0xdb6
	unsigned char m_pad_dad[0x7];				///< +0xdad
	unsigned char m_pad_db7[0x1];				///< +0xdb7
	BFMERetailAsciiString m_str_db8;				///< +0xdb8
	unsigned char m_dbc;				///< +0xdbc
	unsigned char m_dbd;				///< +0xdbd
	unsigned char m_dbe;				///< +0xdbe
	unsigned char m_dbf;				///< +0xdbf
	BFMERetailAsciiString m_str_dc0;				///< +0xdc0
	BFMERetailAsciiString m_str_dc4;				///< +0xdc4
	unsigned int m_dc8;				///< +0xdc8
	unsigned char m_dcc;				///< +0xdcc
	unsigned char m_dcd;				///< +0xdcd
	unsigned char m_pad_dce[0x2];				///< +0xdce
	BFMERetailAsciiString m_str_dd0;				///< +0xdd0
	unsigned int m_dd4;				///< +0xdd4
	unsigned int m_dd8;				///< +0xdd8
	unsigned int m_ddc;				///< +0xddc
	unsigned int m_de0;				///< +0xde0
	unsigned int m_dec;				///< +0xdec
	unsigned int m_df0;				///< +0xdf0
	unsigned int m_df4;				///< +0xdf4
	unsigned int m_df8;				///< +0xdf8
	unsigned int m_dfc;				///< +0xdfc
	unsigned int m_e00;				///< +0xe00
	unsigned int m_e04;				///< +0xe04
	unsigned int m_e08;				///< +0xe08
	unsigned int m_e0c;				///< +0xe0c
	unsigned int m_e10;				///< +0xe10
	unsigned int m_e14;				///< +0xe14
	unsigned int m_e18;				///< +0xe18
	unsigned int m_e1c;				///< +0xe1c
	unsigned int m_e20;				///< +0xe20
	unsigned int m_e24;				///< +0xe24
	unsigned int m_e28;				///< +0xe28
	unsigned int m_e2c;				///< +0xe2c
	unsigned int m_e30;				///< +0xe30
	unsigned char m_e34;				///< +0xe34
	unsigned int m_e3c;				///< +0xe3c
	unsigned int m_e40;				///< +0xe40
	unsigned int m_e4c;				///< +0xe4c
	unsigned int m_e50;				///< +0xe50
	unsigned char m_e54;				///< +0xe54
	unsigned char m_e55;				///< +0xe55
	unsigned int m_e5c;				///< +0xe5c
	unsigned char m_e60;				///< +0xe60
	unsigned int m_e68;				///< +0xe68
	unsigned char m_e6c;				///< +0xe6c
	unsigned int m_e70;				///< +0xe70
	unsigned int m_e78;				///< +0xe78
	unsigned int m_e80;				///< +0xe80
	unsigned int m_e84;				///< +0xe84
	unsigned int m_e88;				///< +0xe88
	unsigned int m_e8c;				///< +0xe8c
	unsigned int m_e90;				///< +0xe90
	unsigned int m_e98;				///< +0xe98
	unsigned int m_ea0;				///< +0xea0
	unsigned int m_ea4;				///< +0xea4
	unsigned int m_eac;				///< +0xeac
	unsigned char m_ec8;				///< +0xec8
	unsigned int m_ecc;				///< +0xecc
	unsigned char m_ed0;				///< +0xed0
	unsigned char m_ed1;				///< +0xed1
	unsigned int m_ed8;				///< +0xed8
	unsigned char m_pad_de4[0x8];				///< +0xde4
	unsigned char m_pad_e35[0x7];				///< +0xe35
	unsigned char m_pad_e44[0x8];				///< +0xe44
	unsigned char m_pad_e56[0x6];				///< +0xe56
	unsigned char m_pad_e61[0x7];				///< +0xe61
	unsigned char m_pad_e6d[0x3];				///< +0xe6d
	unsigned char m_pad_e74[0x4];				///< +0xe74
	unsigned char m_pad_e7c[0x4];				///< +0xe7c
	unsigned char m_pad_e94[0x4];				///< +0xe94
	unsigned char m_pad_e9c[0x4];				///< +0xe9c
	unsigned char m_pad_ea8[0x4];				///< +0xea8
	unsigned char m_pad_eb0[0x18];				///< +0xeb0
	unsigned char m_pad_ec9[0x3];				///< +0xec9
	unsigned char m_pad_ed2[0x6];				///< +0xed2
	AttributeHandleStandIn m_attr_edc;				///< +0xedc
	Rva00083150 m_grid_ee0;				///< +0xee0
	_STL::vector<BFMERetailAsciiString> m_vec_11e0;				///< +0x11e0
	unsigned char m_11ec;				///< +0x11ec
	unsigned int m_11f0;				///< +0x11f0
	unsigned char m_11fc;				///< +0x11fc
	unsigned char m_pad_11ed[0x3];				///< +0x11ed
	unsigned char m_pad_11f4[0x8];				///< +0x11f4
	unsigned char m_pad_11fd[0x3];				///< +0x11fd
	BFMERetailAsciiString m_str_1200;				///< +0x1200
	BFMERetailAsciiString m_str_1204;				///< +0x1204
	_STL::vector<BFMERetailAsciiString> m_vec_1208;				///< +0x1208
	unsigned char m_pad_1214[0x8];				///< +0x1214
	AttributeHandleStandIn m_attr_121c;				///< +0x121c
	unsigned int m_1220;				///< +0x1220
	unsigned int m_1224;				///< +0x1224
	unsigned int m_1228;				///< +0x1228
	unsigned int m_122c;				///< +0x122c
	unsigned int m_1230;				///< +0x1230
	unsigned int m_1234;				///< +0x1234
	unsigned int m_1238;				///< +0x1238
	unsigned int m_123c;				///< +0x123c
	unsigned int m_1240;				///< +0x1240
	unsigned int m_1244;				///< +0x1244
	unsigned int m_1248;				///< +0x1248
	unsigned int m_124c;				///< +0x124c
	unsigned int m_1250;				///< +0x1250
	unsigned int m_1254;				///< +0x1254
	unsigned int m_1258;				///< +0x1258
	unsigned int m_125c;				///< +0x125c
	unsigned int m_1260;				///< +0x1260
	unsigned int m_1264;				///< +0x1264
	unsigned int m_1268;				///< +0x1268
	unsigned char m_126c;				///< +0x126c
	unsigned int m_1270;				///< +0x1270
	unsigned char m_1278;				///< +0x1278
	unsigned char m_pad_126d[0x3];				///< +0x126d
	unsigned char m_pad_1274[0x4];				///< +0x1274
	unsigned char m_pad_1279[0x3];				///< +0x1279
	BFMERetailAsciiString m_str_127c;				///< +0x127c
	BfmeGdUnicodeString m_ustr_1280;				///< +0x1280
	BFMERetailAsciiString m_str_1284;				///< +0x1284
	BFMERetailAsciiString m_str_1288;				///< +0x1288

	GlobalData *m_next;						///< +0x128c
};

// ??0GlobalData@@QAE@XZ
GlobalData::GlobalData()
{
	// Empirically-sized placeholder for retail's still-unidentified ~64KB
	// local (see the header note above): this exact size reproduces retail's
	// `mov eax, 0x10138` __chkstk prologue. The `volatile` touch is only to
	// stop /O2 from eliminating the otherwise-unread array; it is NOT a
	// claim about what retail's code actually does with the buffer.
	char m_scratchTest[0x10134];
	*(volatile char*)m_scratchTest = 0;
	m_dd8 = 0;
	m_ddc = 0;
	m_de0 = 0;
	m_dec = 0;
	m_df0 = 0;
	m_df4 = 0;
	m_df8 = 0;
	m_dfc = 0;
	m_e00 = 0;
	m_e04 = 0;
	m_e08 = 0;
	m_e0c = 0;
	m_e10 = 0;
	m_e14 = 0;
	m_e18 = 0;
	m_e1c = 0;
	m_e20 = 0;
	m_e24 = 0;
	m_e28 = 0;
	m_e2c = 0;
	m_e30 = 0;
	m_cf0 = 0;
	m_cf1 = 0;
	m_cf2 = 1;
	m_cf4 = 1;
	m_cf5 = 0;
	m_db6 = 0;
	m_cf6 = 0;
	m_cf7 = 0;
	m_cf8 = 0;
	m_d84 = 0;
	m_d85 = 0;
	m_d86 = 0;
	m_d88 = 0;
	m_d87 = 0;
	m_d08 = 0;
	m_d0c = 0;
	m_cf3 = 1;
	m_d0d = 0;
	m_d18 = 5;
	m_d58 = 0;
	m_d60 = 5;
	m_d1c = 0;
	m_d24 = 5;
	m_d28 = 0;
	m_d30 = 5;
	m_d05 = 0;
	m_d04 = 0;
	m_cf9 = 0;
	m_cfa = 0;
	m_cfb = 0;
	m_cfc = 0;
	m_d94 = 0;
	m_d98 = 0;
	m_d9c = 0;
	m_da0 = 0;
	m_da4 = 0;
	m_da8 = 0;
	m_dac = 1;
	m_d89 = 0;
	m_d8a = 0;
	m_d8b = 0;
	m_db4 = 1;
	m_dbc = 1;
	m_dbd = 0;
	m_dc8 = 0x3f800000;
	m_dcc = 0;
	m_dcd = 0;
	m_db5 = 0;
	m_8f = 0;
	m_8e = 1;
	m_90 = 0;
	m_a7c = 0;
	m_bc5 = 0;
	m_18 = 1;
	m_19 = 0;
	m_1a = 1;
	m_1b = 1;
	m_1c = 0;
	m_1d = 1;
	m_1e = 0;
	m_1f = 1;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_29 = 0;
	m_2c = 0x400;
	m_30 = 0x300;
	m_3a = 1;
	m_3b = 1;
	m_34 = 0;
	m_38 = 0;
	m_39 = 1;
	m_3c = 0;
	m_44 = 0;
	m_45 = 0;
	m_46 = 0;
	m_48 = 0;
	m_4c = 0;
	m_4d = 0;
	m_4e = 0;
	m_40 = 1;
	m_4f = 0;
	m_60 = 0;  // TODO: non-constant register value, needs re-derivation
	m_54 = 8;
	m_5c = 0;
	m_58 = 0;  // TODO: non-constant register value, needs re-derivation
	m_59 = 0;  // TODO: non-constant register value, needs re-derivation
	m_61 = 0;
	m_62 = 0;
	m_63 = 0;
	m_64 = 0;
	m_65 = 0;
	m_68 = 0;  // TODO: non-constant register value, needs re-derivation
	m_6c = 0;
	m_70 = 0;  // TODO: non-constant register value, needs re-derivation
	m_a90 = 0;
	m_a91 = 0;
	m_a92 = 0;
	m_a93 = 0;
	m_a94 = 0;  // TODO: non-constant register value, needs re-derivation
	m_a95 = 0;  // TODO: non-constant register value, needs re-derivation
	m_a96 = 0;
	m_a97 = 0;
	m_a98 = 1;
	m_a9c = 0;
	m_a9d = 0;
	m_a9e = 0;
	m_a9f = 0;
	m_aa0 = 0;
	m_ab0 = 0;  // TODO: non-constant register value, needs re-derivation
	m_b64 = 0x3f800000;
	m_b68 = 0x3f800000;
	m_b6c = 0x3f800000;
	m_74 = 0;
	m_78 = 0;
	m_7c = 0;
	m_80 = 0;
	m_84 = 0;
	m_88 = 0;
	m_98 = 0;
	m_8c = 0;  // TODO: non-constant register value, needs re-derivation
	m_8d = 0;
	m_c50 = 0;
	m_ac = 0;
	m_bc = 0;
	m_cc = 0;
	m_dc = 0;
	m_ec = 0;
	m_fc = 0;
	m_10c = 0;
	m_11c = 0;
	m_12c = 0;
	m_13c = 0;
	m_14c = 0;
	m_15c = 0;
	m_16c = 0;
	m_180 = 0;
	m_1f0 = 0;
	m_204 = 0;
	m_208 = 0;
	m_210 = 0;
	m_214 = 0;
	m_21c = 0;
	m_220 = 0;
	m_221 = 0;
	m_222 = 1;
	m_223 = 1;
	m_1bc = 0;
	m_1e8 = 0x3f800000;
	m_1ec = 0x3f800000;
	m_1c0 = 0;
	m_1c4 = 0;
	m_1c8 = 0;
	m_1cc = 0;
	m_1d0 = 0;
	m_1d4 = 0;
	m_1dc = 0;
	m_1d8 = 0;
	m_1e4 = 0;
	m_1e0 = 0;
	m_9bc = 0;
	m_9c0 = 0;
	m_9c4 = 0;
	m_9e0 = 0;
	m_9e4 = 0;
	m_9e8 = 0;
	m_a28 = 0x3f800000;
	m_a5c = 0;
	m_a60 = 0;
	m_a64 = 0;
	m_a68 = 0;
	m_a6c = 1;
	m_a6d = 1;
	m_a6e = 1;
	m_a6f = 1;
	m_a70 = 1;
	m_a71 = 1;
	m_a72 = 0;
	m_a73 = 1;
	m_a74 = 0;
	m_a75 = 1;
	m_a76 = 0;
	m_a77 = 0;
	m_a44 = 0x200;
	m_a48 = 0x200;
	m_a4c = 0x200;
	m_a50 = 0x200;
	m_a54 = 0x3f000000;
	m_a7f = 1;
	m_a84 = 0;
	m_ab4 = 0x3f800000;
	m_ac0 = 0;
	m_acc = 0;
	m_ad8 = 0;
	m_ae4 = 0;
	m_af0 = 0;
	m_afc = 0;
	m_b08 = 0;
	m_50 = 0;
	m_b8c = 0;
	m_a88 = 0;
	m_a8c = 0;
	m_a80 = 1;
	m_a81 = 0;
	m_a8d = 1;
	m_a8e = 1;
	m_a8f = 1;
	m_190 = 0;
	m_194 = 0x3f800000;
	m_198 = 0;
	m_19c = 0x3f000000;
	m_1a4 = 0x3f000000;
	m_1a8 = 0x3f000000;
	m_1b0 = 0x3f000000;
	m_1b8 = 0;
	m_b10 = 0;
	m_b2c = 0;
	m_b30 = 0;
	m_b34 = 0;
	m_b38 = 0;
	m_b3c = 0;
	m_b40 = 0;
	m_b44 = 0;
	m_b48 = 0;
	m_b4c = 0;
	m_b54 = 0;
	m_b58 = 0;
	m_b60 = 0;
	m_b5c = 0;
	m_be0 = 5;
	m_be4 = 0x3f000000;
	m_bf0 = 0x3f000000;
	m_bf4 = 0;
	m_bfc = 0x3f800000;
	m_c10 = 0x3f000000;
	m_c14 = 0x3f800000;
	m_c30 = 0x3f800000;
	m_c34 = 0;
	m_c38 = 0;
	m_a7d = 0;
	m_a7e = 0;
	m_c78 = 0x3f800000;
	m_c7c = 0x3f800000;
	m_c80 = 0x3f800000;
	m_c84 = 0xff;
	m_c85 = 0x7f;
	m_c86 = 0;
	m_c88 = 0x3f800000;
	m_c8c = 0x3f800000;
	m_c90 = 0x3f800000;
	m_ca0 = 0x80;
	m_c64 = 5;
	m_c68 = 0x3f800000;
	m_c00 = 0;
	m_c04 = 1;
	m_c05 = 0;
	m_c09 = 0;
	m_c06 = 0;
	m_c07 = 0;
	m_c08 = 0;
	m_b14 = 0;
	m_b18 = 0;
	m_b1c = 0;
	m_b20 = 0;
	m_c0a = 0;
	m_c0b = 0;
	m_c0c = 0;
	m_c0d = 0;
	m_c58 = 0;
	m_c59 = 0;
	m_c6c = 0x1e;
	m_ecc = 0;
	m_ed0 = 0;
	m_ed1 = 1;
	m_ed8 = 0;
	m_ca4 = 0x1e;
	m_cb0 = 0xa;
	m_cb4 = 0xa;
	m_dbe = 0;
	m_dbf = 0;
	m_b7d = 0;
	m_b88 = 0;
	m_b98 = 0x3f800000;
	m_b9c = 0x3f800000;
	m_ba0 = 0x3f800000;
	m_ba4 = 0x3f800000;
	m_a2c = 0x3f800000;
	m_a30 = 0x3f800000;
	m_a34 = 0x3f800000;
	m_a38 = 0x3f800000;
	m_a3c = 0x3f800000;
	m_a40 = 0x3f800000;
	m_ba8 = 0x3f800000;
	m_b94 = 0;
	m_bb4 = 1;
	m_bb5 = 0;
	m_bb6 = 1;
	m_2a = 0;
	m_bb7 = 0;
	m_bb8 = 0;
	m_bb9 = 0;
	m_bbc = 0x3f800000;
	m_bc0 = 0x3f800000;
	m_b7c = 1;
	m_bac = 0x3f800000;
	m_bc4 = 1;
	m_bc8 = 0;
	m_bd0 = 0;  // TODO: non-constant register value, needs re-derivation
	m_c70 = 0;
	m_c74 = 0;  // TODO: non-constant register value, needs re-derivation
	m_aac = 0;
	m_dd4 = 0xa;
	m_e34 = 0;
	m_e40 = 0;
	m_e3c = 0;
	m_e50 = 0x80;
	m_e4c = 0x80;
	m_e54 = 0;
	m_e55 = 1;
	m_e5c = 0;
	m_e68 = 0x3f800000;
	m_e6c = 0;
	m_e60 = 0;
	m_e70 = 0x3c;
	m_e78 = 0xa;
	m_e80 = 0x64;
	m_e84 = 0x12c;
	m_e88 = 0x64;
	m_e8c = 0x12c;
	m_e90 = 0x50;
	m_e98 = 0x50;
	m_ea0 = 0x3c;
	m_ea4 = 0x50;
	m_eac = 0x3c;
	m_ec8 = 0;
	m_11ec = 0;
	m_11f0 = 0;
	m_11fc = 1;
	m_1220 = 0x3f800000;
	m_126c = 1;
	m_1270 = 0;
	m_1224 = 1;
	m_1228 = 1;
	m_122c = 1;
	m_1230 = 1;
	m_1234 = 1;
	m_1238 = 1;
	m_123c = 1;
	m_1240 = 1;
	m_1244 = 1;
	m_1248 = 1;
	m_124c = 1;
	m_1250 = 1;
	m_1254 = 1;
	m_1258 = 1;
	m_125c = 1;
	m_1260 = 1;
	m_1264 = 1;
	m_1268 = 1;
	m_1278 = 0;
}

// ?finishSpecialPower@SpecialPowerModule@@QAEXI@Z
// partial score=0.9851 date=2026-09-29
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ###########################################################################
// # THIS FILE IS ABI-WRONG. DO NOT LAND IT. BUILD FROM                    #
// # targets/game/reverse/attempts/0x00269c50-constref-abi.cpp INSTEAD.    #
// #                                                                      #
// # Its higher byte score (16 vs 23 differing non-relocation bytes) comes #
// # from declaring BfmeObjectReferenceStore::configure's second parameter   #
// # as `Int key` BY VALUE, which makes VC7.1 emit `mov edx,[esi+0x1dc]`   #
// # and push that VALUE, where retail pushes the ADDRESS of the field:     #
// #                                                                      #
// #   +019a 81 c6 dc 01 00 00   add esi, 0x1dc                            #
// #   +01a0 56                  push esi                                  #
// #                                                                      #
// # The callee proves the signature. tools/dis_retail.py 0x0039B6D0        #
// # (?configure@BfmeObjectReferenceStore@@QAEXHABHPBVObject@@ABVAsciiStrin #
// # g@@H@Z, a MATCHED row in functions.csv) shows:                        #
// #   +000d 8b 4c 24 10          mov ecx, dword ptr [esp + 0x10]          #
// #   +0014 8b 11                mov edx, dword ptr [ecx]                 #
// #   +001e 89 57 18             mov dword ptr [edi + 0x18], edx          #
// #                                                                      #
// # i.e. it DEREFERENCES its second stack argument, so argument 2 is a    #
// # `const int&` and the mangled name's `ABH` says the same. This file     #
// # scores better only by pushing a value that coincidentally matches the  #
// # LENGTH of retail's address push. It cannot be landed.                  #
// ###########################################################################
//
// 2026-09-29 session 5 (space-bunny-free, high): fifth pass, plateau intact.
// tools/probe.py on this stash: ours=1073 retail=1073, 46 relocs, 16
// non-reloc diffs, shape 0.994, 2 structural, first at +0xc8. The
// ABI-correct form (0x00269c50-constref-abi.cpp) re-measures at 23.
// *** THE RESIDUE SITES NEED OPPOSITE CORRECTIONS, NOW QUANTIFIED. ***
// MSVC 7.1 hands out EAX/ECX/EDX round-robin in program order
// (targets/game/reverse/analysis/allocation_residue.md). Scoring every
// site against that order gives:
//   +0xc7  ours EDX, retail ECX -> ours is ONE STEP AHEAD
//   +0x181 ours ECX, retail EDX -> ours is ONE STEP BEHIND
//   +0x1ea (const-ref form only) ours EDX, retail EAX -> ONE STEP BEHIND
// So the fix is NOT one perturbation: the +0xc7 block needs ONE FEWER
// temp allocated in +0x23..+0xc7, and the +0x181 block needs ONE MORE
// temp allocated in +0xc7..+0x181. The two blocks inherit the rotation
// pointer from DIFFERENT predecessors (the bfmeDoRY call block vs the
// fx/store/kind block), which is why no single toggle and no
// rotation_sweep pair can ever move both. Earlier notes in this file
// called the sites "one consistent transposition"; that is wrong, and
// the by-value form is the direct proof: its extra `mov reg,[esi+0x1dc]`
// key-value load adds exactly one temp after +0x181, and that alone makes
// +0x1ea byte-exact while leaving +0xc7 and +0x181 untouched.
// Closed this session, do not re-run (all 23 on the const-ref base, or
// 16 on this one, or structurally worse):
//  tools/eh_levers.py + tools/shape_search.py on the ABI-CORRECT base
//   (6 choices, 128 combinations, 9 trials): no improving output. Prior
//   sessions only ran these on the by-value base.
//  tools/shape_family_levers.py over all ten families on the ABI-CORRECT
//   base: "no applicable source-level family lever".
//  THE REFERENCE/POINTER AXIS IS NOW CLOSED DEFINITIVELY. On the const-ref
//   base, declaring argument 2 as `const Int *key` and passing
//   `&data->m_key1dc` produces BYTE-IDENTICAL output to `const Int &key`
//   with `data->m_key1dc`; so does `*(const Int *)&data->m_key1dc`, and so
//   does making the field `const Int`. Retail's `add esi,0x1dc; push esi`
//   is therefore a property of the ARGUMENT EXPRESSION, not of whether the
//   parameter is a reference or a pointer, and session 3's "+7 bytes" for
//   the pointer spelling came from its `const void*` variant, not from the
//   pointer itself. Do not re-test reference vs pointer here.
//  34 further spellings, all inert: nested `if` for the
//   `frames != -1 && scale > 0.0f` conjunction; `const Player *player`
//   and `Player *const player`; `Bool hasValue = (v != 0)`; a second
//   `location` local for the first two calls; re-reading
//   `data->m_frames1fc` at the bfmeDoRY call; recomputing `delta` inline
//   there; `name` through a `(const void *)` cast; `fx` re-read twice
//   instead of cached; `0.0f < data->m_scale200` (+8, worse);
//   setDisabledUntil's frame parameter as `Int`; `const Int delta`;
//   `const Coord3D *const location`; `m_object` as the direct receiver;
//   `m_field208 != 0`; `UnsignedInt kind`; the fx `if` inside its own
//   block; the whole configure call inside its own block; the store as a
//   `const BfmeObjectReferenceStore *` local. Only one of the 34 moved at
//   all, and it moved the wrong way: rewriting the kind chain as two
//   independent `if`s gives 22 diffs but the first divergence jumps back
//   to +0x15d, i.e. a different shape, not a phase improvement.
// WHAT THE NEXT WORKER SHOULD DO: the two corrections are independent, so
// they can be attacked in either order and each is worth 1 byte at +0xc8 or
// 5+14 bytes downstream. The +0x1ea fix is the cheapest to look for: it
// needs ONE more scratch temp allocated somewhere in +0x181..+0x1e5 (the
// hasValue/name test block), and the by-value key load proves such a temp
// exists and lands there when the configure call is by value. The +0xc7 fix
// needs ONE FEWER temp in +0x23..+0xc7, i.e. in the aboutToDoSpecialPower /
// createViewObject / subtract / ftol2 prefix, which no spelling tried in
// five sessions has been able to remove. Neither is reachable by reordering
// a pushed load, so do not spend a session on rotation_sweep again.
// SCORE NOTE: 0.9851 is tools/probe.py's own measure of this file, not an
// estimate. The row is deliberately NOT improved by this session: the body
// did not get closer to retail, only better understood.
//
// BANKED, NOT BYTE-EXACT (2026-09-29 session 3): 1073 compiled bytes = retail
// 1073, 16 differing non-relocation bytes, 3 runs, down from session 2's 23
// bytes and 7-byte insert, by correcting ONE CALLEE SIGNATURE: BfmeObject-
// ReferenceStore::configure takes `Int key` BY VALUE, not `const Int &key`
// (see the session-3 note at the bottom). A structural insert remains, smaller
// than before; the body is still not byte-exact and is NOT landable.
// Identity: the pinned ILT ?finishSpecialPower@SpecialPowerModule@@QAEXI@Z
// (0x000251AD -> 0x00269C50) is what the matched doSpecialPower* callers call;
// the body is the BFME expansion of ZH SpecialPowerModule::triggerSpecialPower
// (aboutToDoSpecialPower, createViewObject, recharge, ...), and the
// Rva0026A190 -0x10 adjustor tail enters it from the interface.
// Remaining residue is pure register choice in three spots:
//  +0xc7   TheGameLogic loaded into ecx (retail) vs edx (ours);
//  +0x181  configure() args: retail value/player in edx, name in ecx and the
//          player push after the store load; ours swaps ecx/edx and pushes
//          player before loading the store;
//  +0x1ea  Coord3D copies: retail eax/edx, ours edx/eax.
// Tried without effect: inline getFrame(), a frame local, delta+frame order,
// Coord3D::set(), eh_levers+shape_search (21 trials), flag_sweep (90 variants).
//
// 2026-09-29 session (space-bunny-free, high): re-verified the 23/1073 diffs
// and confirmed a hard plateau. rotation_sweep.py over all 37 toggles: every
// one byte-identical to the bank (23 diffs, +0). shape_family_levers.py
// reports "no applicable source-level family lever"; eh_levers + shape_search
// (13 trials) found nothing. Hand-written spellings, all 23 diffs:
//  the whole-function parameter typed `const Coord3D *` (removes the int-to-
//  pointer cast; only the mangled name changes, bytes identical);
//  getFrame() vs m_frame; a const/non-const GameLogic accessor;
//  UnsignedInt for frames/delta; reload data->m_frames1fc per branch;
//  an until local in its own block; explicit DisabledType/UnsignedInt casts;
//  an asBfmeItemRY() accessor instead of the C-style cast (BfmeItemRY made a
//  direct Object base breaks the build at 1081 B, so the cast stays);
//  owner/key/name/value locals and a store local for configure();
//  dropping the (const Object*) cast on the owner (needs Player -> Object);
//  fx read twice with a scoped local; a hoisted modData local;
//  a const spTemplate; frames as const; startPowerRecharge through the
//  interface base; the Coord3D copy as src-select / field-by-field /
//  getPosition() returning a reference (the last three all shrink to
//  1050-1071 B, so retail's copy really is `pos = *ptr` in a branch).
// Conclusion: the residue is a compiler-internal temp-allocation phase, not a
// reachable source spelling. Do not re-run these; the lever would be upstream
// of the body or in the MSVC codegen.
//
// 2026-09-29 session 2 (space-bunny-free, high): confirmed the plateau again
// and closed the levers the previous session had left open.
// Re-verified with tools/probe.py: 1073 B = retail 1073, 23 non-reloc diffs,
// shape 0.997, first divergence +0xc7, 2 structural diffs at +0x193.
// tools/alloc_residue.py refuses the body (shape is not identical) precisely
// because of that +0x193 insert, so the scratch-only class is not reachable
// here and the residue is mixed, not pure scratch.
// NEW, all landing on the same 23 bytes (so do not re-run):
//  accessor definition site moved out of the class body for each of
//   getObject, getSpecialPowerModuleData, Object::getTemplate,
//   Object::getPosition, SpecialPowerTemplate::getFO,
//   Overridable::friend_getFinalOverride, GameLogic::getFrame
//   (build/acc.py, 7 cases): all 23 diffs, identical run list;
//  TheGameLogic::m_frame vs getFrame(), an until local in its own block, an
//   Object* receiver local, a GameLogic* local, an explicit UnsignedInt cast
//   on the sum, UnsignedInt frames/delta, frames != (UnsignedInt)-1, a Bool
//   local for m_field208, a getObject() local for the bfmeDoRY receiver, a
//   non-const data pointer, a modData local hoisted above the first call;
//  the store expression: TheBfmeObjectReferenceStore(), a direct
//   (BfmeObjectReferenceStore *)g_bfmeModeGF cast, a g_bfmeModeGF re-declared
//   as the store, and a BfmeObjectReferenceStore* local: all 23 diffs, so the
//   inline accessor and the global are interchangeable here;
//  configure() argument spelling: a const Object* owner local, a const
//   AsciiString& name local, a const Int& key local, a value local, and all
//   five as locals at once: all 23 diffs. A key local DOES move code (55
//   diffs, first at +0x15d) but not toward retail, so retail really does
//   pass data->m_key1dc directly;
//  kinds: an if/else-if/else chain instead of `kind = 1` first, and a nested
//   ternary: both restructure to 1070 B / 607 diffs, worse;
//  the FX block: dropping the static doFXPos/doFXObj helpers for direct
//   isEmpty()+member calls is 1065 B / 675 diffs, worse (the helpers are
//   load-bearing and the stash header is right to keep them);
//  the Coord3D copy: source = location ? location : getPosition() and a const
//   reference source are both 1050 B / 637 diffs, worse;
//  hasValue as an Int instead of a Bool: 1072 B / 514 diffs, worse.
//
// The one asymmetry worth keeping: at +0xc7 retail loads TheGameLogic into
// ECX and reads [ecx+0x3c] from it, while at +0x181 retail puts the
// configure() value and the player in EDX and the name in ECX. So the two
// sites are not one rotation in the same direction: fixing +0xc7 alone would
// need the pointer one step the OTHER way from +0x181. That is why every
// single-site toggle lands on the same 23 bytes, and it is the reason to stop
// treating this as one phase shift. The +0x193 insert (ours pushes the player
// before loading the store, retail loads the store first) is a scheduling
// difference inside one call, not a rotation.
// Levers that got here from the 0.13 bank: real filter classes (pinned global
// vtables) declared rj/relationship/alive/object in unwind order; ZH
// inline-recursive const+non-const friend_getFinalOverride; __real literals
// 5.0f and 0.0f (retail 0x01075344/0x01075350 are compiler float constants);
// ZH-style static FXList::doFXPos/doFXObj helpers; the reference store read
// per branch; hasValue as an if; the filter/result tail in its own block so
// the result takes the dead location parameter slot and the frame is 0x4c.
// Landing needs two pins (not added yet, evidence below):
//  ?aboutToDoSpecialPower@SpecialPowerModule@@IAEXPBUCoord3D@@@Z at ILT
//    0x00046C13 (body 0x00268CB0, ledger-misnamed as a module-data dtor): ZH
//    call order plus its TheScriptEngine notify with the controlling player's
//    index at +0x24;
//  an address-derived name for ILT 0x0001F505 -> dump 0x00269780 (thiscall,
//    one BfmeWideResult* argument, ret 4).
//
//
// 2026-09-29 session 4 (space-bunny-free, high): re-verified the 16-byte bank
// (1073 B = retail, 46 relocs, 16 non-reloc diffs, shape 0.994, 2 structural,
// first at +0xc7) and CORRECTED the session-3 ABI claim below.
//
// *** The by-value `Int key` spelling is ABI-WRONG. Do not treat it as a
// candidate landing. The pinned retail callee
//   ?configure@BfmeObjectReferenceStore@@QAEXHABHPBVObject@@ABVAsciiString@@H@Z
// (functions.csv 0x0039B6D0, matched) decodes argument 2 as `const int&`
// (`ABH`), and the landed body dereferences it:
//   *(int *)(m_pad2) = value;
// (game/GameEngine/Source/GameLogic/Object/Update/BfmeObjectReferenceStoreClear.cpp).
// Retail's own call site agrees: `add esi,0x1dc; push esi` pushes the ADDRESS
// of data->m_key1dc. So the correct declaration is
//   void configure(Int mode, const Int &value, const Object *player,
//                  const AsciiString &name, Int trailingValue);
// (equivalently a `const Int *key` + `&data->m_key1dc`; both emit the same code).
// The 16-byte by-value form scores better only because it accidentally
// reproduces the instruction LENGTH of retail's address push with a VALUE push.
//
// Measured, both at extent 1073 = retail:
//   `Int key` by value   : 16 diffs, runs +0c8 +0ce +182 +187 +189 +18d +192
//                               +194 +1a0  (the run at +194 is a real
//                               push-the-wrong-thing, not just a register)
//   `const Int &value`   : 23 diffs, runs +0c8 +0ce +182 +187 +189 +18d +192
//                               +1eb +1ee +1f1 +1f5 +1f8 +1fc +202 +205
//                               +207 +20b +20e +212 +215
// The reference form is EXACT from +0x194 to +0x1a2 (retail's
// `mov ecx,[store] / push edx / add esi,0x1dc / push esi / push eax` all
// match) and pays instead with 14 bytes of Coord3D-copy register mirror at
// +0x1eb..+0x215 that the by-value form gets right. So the residue MOVES
// between the two forms: fixing the signature moves 9 bytes out of the
// configure() call and 14 bytes into the Coord3D copies. The remaining work
// is the same ECX/EDX scratch transposition in both cases, and the two
// sites (+0xc7 wants ECX, +0x181 wants EDX) are a single consistent
// transposition of one register pair, not two opposite rotations.
//
// Closed this session on BOTH forms, do not re-run (all 16 or all 23, or
// structurally worse):
//  tools/shape_family_levers.py over all ten families: "no applicable
//   source-level source-level lever" on the 16-byte base.
//  tools/eh_levers.py + shape_search, 9 trials, on the 16-byte base (the
//   earlier sessions only ran these on the 23-byte base): all identical,
//   no new shape.
//  13 call-site and argument spellings on the 16-byte base (store local,
//   owner local, key-as-const-ref local, all five args as locals, the call
//   in its own nested block, kind as a switch/ternary (both 1070 B/607),
//   the frame sum in a local, getFrame(), explicit UnsignedInt casts,
//   an `Object *object` local spanning both calls (1070 B/787)):
//   all 16.
//  14 early-function spellings aimed at shifting the whole-function scratch
//   rotation counter before the first divergence: a discarded `TheGameLogic`
//   and `data->m_frames1fc` read, an `Int spare` that is written, the
//   location copied into a nested block for each of the two first calls, a
//   `recharge` call wrapped in its own block, the module data hoisted into a
//   `pre` local, the subtract template through a `md` local: all 16.
//  12 mirror spellings on the reference form (store local for both uses,
//   owner local, all five args as locals, key as a `const Int &` local, the
//   key re-read through a cast, the call in its own block, the frame sum
//   through getFrame()): all 23.
//  8 Coord3D spellings on the reference form, aimed at the +0x1eb..+0x215
//   regression the reference form introduces: a `const Coord3D *src` ternary
//   and a ternary initialiser (both 1050 B/637), field-by-field copies
//   (1071 B/471), and three compile failures: all worse or inert.
//  Modelling m_name1d0 as a real `AsciiString` member instead of a byte
//   array plus a C-style cast: 16, so the cast spelling is inert.
// CONCLUSION: with the signature now settled by the pinned callee, the
// residue is one ECX/EDX transposition visible at three sites, and it is
// not reachable by any source spelling, rotation toggle, parameter type or
// mechanical lever in this repo. The remaining lever is above the
// source-level tools here.
//
// 2026-09-29 session 3 (space-bunny-free, high): BROKE the 23-byte plateau.
// The lever was the CALLEE SIGNATURE, not a source spelling.
// BfmeObjectReferenceStore::configure's second parameter is `Int key` BY
// VALUE, not `const Int &key`. Retail emits `add esi, 0x1dc; push esi`, which
// pushes the ADDRESS of data->m_key1dc, and VC7.1 only reaches that schedule
// from a by-value Int: with `const Int &key` it emitted an extra
// `mov edx, [esi+0x1dc]` and reordered the `this` load after the player push.
// Changing that one parameter: 23 -> 16 differing non-relocation bytes, the
// extent stays exactly 1073 B, and the 7 recovered bytes are the
// `mov edx,[esi+0x1dc]` key load, the extra `push ecx`, and the four bytes of
// the old +0x194..+0x19b run.
// CORRECTION to an earlier reading of this file: the +0x193 "structural
// insert" is NOT gone. probe still reports two structural differences, now as
// a two-instruction insert (O +0x193 `mov edx,[esi+0x1dc]` and O +0x199
// `push ecx`) against one delete. So this session reduced the residue and
// shrank the insert, it did not remove the insert. What did change is that
// the insert is now the same shape as retail's `add esi,0x1dc; push esi` --
// ours loads the key VALUE where retail computes the key ADDRESS -- so the
// remaining question is why VC7.1 folds the by-value argument to an address
// in retail. Read together with the pointer-key result below, the evidence
// says the by-value form is right (a pointer spelling costs 7 bytes
// elsewhere), and the last step is the operand form of the key expression.
// Remaining 16 bytes, all register-mirror, in three runs:
//   +0xc8, +0xce  TheGameLogic into EDX where retail uses ECX (2 bytes)
//   +0x182..+0x192  configure() args: retail value/player in EDX and name in
//                   ECX; ours swaps them (5 bytes)
//   +0x194..+0x1a0  the `this` load still lands after the player push in ours
//                   and retail loads it first (9 bytes)
// Closed this session, do not re-run:
//  tools/rotation_sweep.py --pairs (704 toggles) on the 23-byte bank AND on
//   the new 16-byte bank AND on the pointer-key variant (667 toggles): every
//   single toggle and every pair is byte-identical to its own base. The
//   scratch-rotation lever is inert at this offset in all three forms.
//  A 17-case sweep of configure()'s five parameter types (build/decls.json),
//   every kind/key/name/value/owner spelling including UnsignedInt, by
//   reference, by const&, by pointer, static and non-static: `Int key` by
//   value is the unique winner; `const Int &key` is +7, `const Int &value` is
//   +1, `const Int &kind` grows the body to 1086 B, `static` shrinks it to
//   1070 B, `const Object *const &owner` grows it to 1081 B. The name
//   parameter is insensitive: AsciiString&, AsciiString*, void*, char*, Int&
//   and Int* are all byte-identical, so do not spend a session on it.
//  A pointer key (`const Int *key` + `&data->m_key1dc`, and `const void *`)
//   reproduces retail's `add esi,0x1dc; push esi` exactly but costs 7 bytes
//   elsewhere, so the address in retail comes from the by-value form, not
//   from a pointer parameter. Do not re-try the pointer spelling.
//  14 configure() call-site spellings (build/site1.json): owner local, store
//   local for one or both uses, value/key/name/kind locals, all five as
//   locals, a direct global cast instead of the accessor, the call in its own
//   nested block, a switch for kind, an `!= 0` field test: all byte-identical
//   at 16. Only reordering the m_field20a/m_field20b tests moves (+4, worse).
//  12 spellings of the +0xc7 TheGameLogic frame sum (build/site2.json): an
//   UnsignedInt `until` local, getFrame(), the commuted sum delta + m_frame,
//   a GameLogic* local, explicit UnsignedInt/Int casts on either operand or
//   both, a frame local, an Object* receiver local: all byte-identical.
//  12 more (build/site3.json): the store as a static accessor reference, a
//   store local over both uses, spTemplate inlined, getFrame/getFO moved out
//   of the class, a padding change, UnsignedInt delta, UnsignedInt frames with
//   -1u, UnsignedInt kind, m_scale200 re-read: all byte-identical. `>= 0.0f`
//   is +1; getFO out of line shrinks the body to 1049 B.
// CONCLUSION: the 16-byte residue is three independent register mirrors plus
// one push/load order inside the configure() call, and no spelling, rotation
// toggle, or parameter type reaches it. The remaining lever is a change to
// what the compiler knows about live ranges at those three sites, which is
// above the source-level tools this repo has.

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#include <vector>
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class Matrix3D;
class AsciiString;

enum DisabledType
{
	DISABLED_HELD = 3
};

enum KindOfType
{
	KINDOF_0x6C = 0x6c
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(void *subobject, void *extra, Bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	void *m_subobject;
	void *m_extra;
	Bool m_match;
};

struct BfmeWideResultItem
{
	Object *m_object;
	UnsignedInt m_distance;
};

struct BfmeWideResultPayload
{
	std::vector<BfmeWideResultItem> m_items;
	BfmeWideResultItem *m_cursor;
	Int m_refCount;
};

struct Rva009F3C70Result
{
	BfmeWideResultPayload *m_value;
	void append(Int, Int);
};

struct BfmeWideResult : public Rva009F3C70Result
{
	~BfmeWideResult()
	{
		BfmeWideResultPayload *&payload = m_value;
		--payload->m_refCount;
		if (payload->m_refCount == 0)
			delete payload;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int, Int, Int, Int, Int);
};

class PartitionManager : public BfmeWideForwardC
{
};

extern PartitionManager *ThePartitionManager;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *getFinalOverride();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled[0xd4 - 8];
	UnsignedInt m_fieldD4;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}

	unsigned char m_unmodelled[0x20 - 8];
	Int m_field20;
};

class FXList
{
public:
	Bool isEmpty() const;
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx = 0,
		Real primarySpeed = 0.0f, const Coord3D *secondary = 0) const;
	void doFXObj(const Object *primary, const Object *secondary = 0) const;

	static void doFXPos(const FXList *fx, const Coord3D *primary)
	{
		if (fx && !fx->isEmpty())
			fx->doFXPos(primary);
	}
	static void doFXObj(const FXList *fx, const Object *primary)
	{
		if (fx && !fx->isEmpty())
			fx->doFXObj(primary);
	}
};

class Rva000C98C0
{
public:
	void subtract(Int);
};

class BfmeItemRY
{
public:
	void bfmeDoRY(void *, void *);
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Rva001BFE20Interface : public BfmeVirtualSlots<60>
{
public:
	virtual void collectObjects(std::list<Object *> *out) = 0;
};

class Thing
{
public:
	virtual ~Thing();
	Bool isKindOf(KindOfType kind) const;

protected:
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	void *unidentified_001BFE20() const;
	ThingTemplate *getTemplate() const
	{
		ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}

};

class GameLogic
{
public:
	unsigned char m_unmodelled[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class BfmeObjectReferenceStore
{
public:
	void clearObjectEntries();
	// ABI NOTE: the REAL signature, proven by the pinned matched callee
	// ?configure@BfmeObjectReferenceStore@@QAEXHABHPBVObject@@ABVAsciiString@@H@Z
	// (functions.csv 0x0039B6D0), takes argument 2 as `const int&` and the
	// body dereferences it. Retail's call site pushes the ADDRESS
	// (`add esi,0x1dc; push esi`), which only a reference/pointer parameter
	// can produce. The by-value form below scores 16 differing bytes instead
	// of 23, but it pushes a VALUE where retail pushes an ADDRESS, so it is
	// ABI-wrong and must NOT be landed. See the session-4 note in the header.
	void configure(Int kind, Int key, const Object *owner,
		const AsciiString &name, Int value);
};

class BfmeModeGF;
extern BfmeModeGF *g_bfmeModeGF;
inline BfmeObjectReferenceStore *TheBfmeObjectReferenceStore()
{
	return (BfmeObjectReferenceStore *)g_bfmeModeGF;
}


struct SpecialPowerModuleData
{
	unsigned char m_unmodelled00[8];
	SpecialPowerTemplate *m_specialPowerTemplate;
	Bool m_updateModuleStartsAttack;
	unsigned char m_unmodelled0d[0x1d0 - 0x0d];
	unsigned char m_name1d0[4];
	Int m_range1d4;
	Bool m_field1d8;
	unsigned char m_pad1d9[3];
	Int m_key1dc;
	unsigned char m_pad1e0[4];
	Bool m_field1e4;
	unsigned char m_pad1e5[3];
	Int m_value1e8;
	Bool m_field1ec;
	Bool m_field1ed;
	Bool m_field1ee;
	unsigned char m_pad1ef[0x1f4 - 0x1ef];
	const FXList *m_fx;
	unsigned char m_pad1f8[4];
	Int m_frames1fc;
	Real m_scale200;
	unsigned char m_pad204[4];
	Bool m_field208;
	unsigned char m_pad209;
	Bool m_field20a;
	Bool m_field20b;
};

class BehaviorModuleBase
{
public:
	virtual ~BehaviorModuleBase();

protected:
	const SpecialPowerModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled0c[4];
};

class SpecialPowerModuleInterface : public BfmeVirtualSlots<16>
{
public:
	virtual void startPowerRecharge() = 0;
};

class SpecialPowerModule : public BehaviorModuleBase, public SpecialPowerModuleInterface
{
public:
	void finishSpecialPower(UnsignedInt arg);

protected:
	void aboutToDoSpecialPower(const Coord3D *location);
	void createViewObject(const Coord3D *location);
	void rva00269780(BfmeWideResult *result);

	Object *getObject() const { return m_object; }
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
};

void SpecialPowerModule::finishSpecialPower(UnsignedInt arg)
{
	const Coord3D *location = (const Coord3D *)arg;
	aboutToDoSpecialPower(location);
	createViewObject(location);

	if (!getSpecialPowerModuleData()->m_updateModuleStartsAttack)
		startPowerRecharge();

	Player *player = getObject()->getControllingPlayer();
	if (player)
	{
		SpecialPowerTemplate *spTemplate = getSpecialPowerModuleData()->m_specialPowerTemplate;
		((Rva000C98C0 *)player)->subtract(spTemplate->getFO()->m_field20);
	}

	const SpecialPowerModuleData *data = getSpecialPowerModuleData();
	Int frames = data->m_frames1fc;
	if (frames != -1 && data->m_scale200 > 0.0f)
	{
		Int delta = (Int)(data->m_scale200 * 5.0f);
		((BfmeItemRY *)getObject())->bfmeDoRY((void *)frames, (void *)delta);
		if (data->m_field208)
			getObject()->setDisabledUntil(DISABLED_HELD, TheGameLogic->m_frame + delta);
	}

	const FXList *fx = data->m_fx;
	if (fx)
	{
		if (location)
			FXList::doFXPos(fx, location);
		else
			FXList::doFXObj(fx, getObject());
	}

	if (data->m_field1e4)
	{
		if (data->m_field1ee)
		{
			TheBfmeObjectReferenceStore()->clearObjectEntries();
			return;
		}
		Int kind = 1;
		if (data->m_field20b)
			kind = 2;
		else if (data->m_field20a)
			kind = 3;
		TheBfmeObjectReferenceStore()->configure(kind, data->m_key1dc, (const Object *)player,
			*(const AsciiString *)data->m_name1d0, data->m_value1e8);
		return;
	}

	Bool hasValue = false;
	if (data->m_value1e8)
		hasValue = true;
	const Int *name = *(const Int *const *)data->m_name1d0;
	if ((name == 0 || *(const unsigned short *)((const char *)name + 4) == 0) && !hasValue)
		return;

	Object *object = getObject();
	Coord3D pos;
	if (location)
		pos = *location;
	else
		pos = *object->getPosition();

	Int relationship = 4;
	if (data->m_field1ec)
		relationship = 1;
	if (data->m_field1ed)
		relationship = 7;
	else if (data->m_field1ee)
		relationship = 5;
	else if (hasValue)
		relationship = (relationship != 1) ? 1 : 4;

	Rva00265150RJFilter rjFilter((void *)&data->m_key1dc,
		object->getControllingPlayer(), true);
	PartitionFilterRelationship filterTeam(object, relationship, false);
	Rva0025ED50RootFilter aliveFilter;
	Rva0025ED50ObjectFilter objectFilter(object);
	rjFilter.link(filterTeam.link(&aliveFilter));
	if (!(object->getTemplate()->m_fieldD4 & 0x4000000))
		rjFilter.link(&objectFilter);

	{
	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(Int)&pos, data->m_range1d4, 0, (Int)&rjFilter, 1);
	if (data->m_field1d8)
	{
		if (object->isKindOf(KINDOF_0x6C))
		{
			Rva001BFE20Interface *extra =
				(Rva001BFE20Interface *)object->unidentified_001BFE20();
			if (extra)
			{
				std::list<Object *> objects;
				extra->collectObjects(&objects);
				for (std::list<Object *>::iterator it = objects.begin();
					it != objects.end(); ++it)
				{
					if (*it)
						result.append((Int)*it, 0);
				}
			}
		}
		else
			result.append((Int)object, 0);
	}
	rva00269780(&result);
	}
}

// ?bfmeDoBESE@BfmeHostESE@@QAEXPAVBfmeThingESE@@PAX@Z
// partial score=0.5698 date=2026-09-29
// THIRD PASS (current): findings H-J at the bottom.  The body below now compiles
// to 82 bytes with the registration frame and ZERO state stores, against the
// 94-byte / one-state-store spelling of the second pass.  Trust the tool's
// score, not a hand estimate: re_log measured 0.5698 (I had submitted 0.75).
//
// Second pass: the frame is no longer the open question, the NULL cleanup action
// is.  Findings A-G at the bottom of this header are all tool-measured.
// Reconstruction of retail 0x002C4910 (86 bytes) -- NOT byte-exact, banked as a
// partial.  Home for a landed body: game/GameEngine/Source/Common/BfmeConv1969.cpp
// (the matched caller ?bfmeStepESE@BfmeHostESE@@QAEXPAVBfmeThingESE@@PAX@Z lives
// there and already calls this symbol).
//
// IDENTITY: proven.  The ILT thunk at 0x000376C8 is pinned to
// ?bfmeDoBESE@BfmeHostESE@@QAEXPAVBfmeThingESE@@PAX@Z (pin_consistency --symbol
// reports "consistent", extent 86), and the byte-true caller at 0x002C51B0 is
// BfmeConv1969.cpp.  `ret 8` at +0x53 proves the 86-byte extent.
//
// RESIDUE (one instruction, 8 bytes).  probe.py reports ours=94 retail=86,
// 22 non-relocation bytes, shape 0.966, 1 structural difference.  The first 63
// bytes are byte-exact apart from the three masked relocations (FuncInfo push at
// +0x02, call rel32 at +0x1C, call rel32 at +0x3F).  At +0x3F we emit
//     c7 44 24 18 00 00 00 00   mov DWORD PTR __$EHRec$[esp+36], 0
// where retail goes straight into the call.  That is the VC7.1 EH *state* store
// for the scope that owns the local.
//
// 2026-09-29, THIRD PASS -- THE "NULL ACTION" PREMISE BELOW IS WRONG.  See
// section H: the compiled FuncInfo of this very file is ALREADY (nState=1,
// nTry=0, one NULL action), byte-identical in shape to retail's FuncInfo
// 0x00E03430.  A destructor-bearing local reproduces retail's exact unwind map;
// NULL versus non-NULL action was never the blocker, and the ~60-construct
// search recorded in findings D/E below was chasing the wrong invariant.  The
// unwind table lives in .rdata and is NOT part of the 86 compared bytes anyway.
//
// The 8 extra bytes then push the two argument loads one register over
// (edx/ecx instead of eax/ecx), which is the other half of the 22 diff bytes.
// Delete the state store and this body is exact.
//
// WHAT IS PROVEN ABOUT THE SHAPE
//   * The 4-byte local lives in the saved-`this` slot at [esp+4] (the .cod
//     listing prints `_f$NNN = -16; size = 4` for it), which is why the object
//     must be declared in a nested block.
//   * Its inlined constructor carries the null-guarded store: retail's
//     `test eax,eax / je +4 / mov [esp+4],eax` at +0x2B is `if (p) m_p = p;`.
//   * The local's destructor must not be provably empty, or VC7.1 deletes the
//     object and the whole frame with it (~C(){} -> 36 bytes, frameless).
//
// LEVERS ALREADY TRIED AND REFUTED (do not repeat)
//   throw() on bfmePrivateCommand38 / on unidentified_001BFE20 / on the function:
//     MSVC then believes no call can throw, drops the scope entirely and the
//     frame with it -> 36 bytes.  Over-corrects.
//   throw() on the destructor, throw() on the constructor: no change (94/22).
//   Empty user destructor ~C(){}: object deleted, 36 bytes.
//   Destructor with an inlined no-op call rva_nop(0): object deleted, 36 bytes.
//   Destructor reading m_p (if (m_p) m_p = 0;), clearing m_p, or referencing a
//     global: all give 94/22 -- the state store is invariant.
//   volatile member (plain or in a struct), a bare volatile pointer local, and a
//   separate memberless dtor object: the store is removed or relocated, 36-80 B.
//   Nested block that closes before the command call: object deleted, 36 B.
//   Function-scope local: 94 B but the state store lands at the top and the
//     frame grows.
//   virtual destructor: 104 B (vptr store).  Two-member object: 96 B.
//   Unconditional member store instead of the ctor's guarded store: 90 B.
//   `throw 1;` in statically dead code: 36 B, no frame.  __try/__except: 121 B.
//   tools/eh_levers.py on this source: its 5 choices are exactly the refuted
//     throw() and /EHsc- levers above (32 combinations, all worse).
//
// ---------------------------------------------------------------------------
// 2026-09-29, second pass.  The frame itself is no longer the open question; the
// NULL cleanup action is.  Everything below was measured with the project's own
// VC7.1 toolchain (cl /O2 /GR- /EHsc /FA, build/w9/bat*.cpp in the worktree that
// ran it), not reasoned from the manual.
//
// A. THE FUNCINFO LAYOUT IS NOW VERIFIED, NOT ASSUMED.  Scanning every
//    FuncInfo-shaped structure in the retail image (8514 of them, rdata
//    0x00A00000-0x00F00000) gives {magic 0x19930520, nState, pUnwindInfo,
//    nTryBlocks, pTryBlockMap, magic2}: 8464 have nTry=0/pTryMap=0 and the ~50
//    that do not carry a nonzero count with a map pointer, which is what fixes
//    offset 0x0C as the try-block count.  Retail 0x002C4910 (FuncInfo 0x00E03430)
//    therefore really has zero try blocks and no function-level try -- the
//    earlier "no try block" claim was inferred, now it is measured.
//
// B. THE STATE STORE HAS TWO FORMS, AND BOTH ARE 8 BYTES IN THE SAME ENCODING.
//    A scope ENTRY is `mov DWORD PTR __$EHRec$[esp+N], 0`; a scope EXIT is
//    `mov DWORD PTR __$EHRec$[esp+N], -1` (c7 44 24 k8 ffffffff).  Measured in
//    `void f(void*a,int*b){ if (a) { LateEmpty t(a); { LateEmpty u(a); } } g(); *b=1; }`:
//    the -1 store lands INSIDE the `if (a)` guard, at exactly the offset where
//    retail has its `mov [esp+4],eax`, and the raise to 0 then lands where
//    retail has its call.  So a probe diff that reports "an 8-byte store at
//    +0x3F" may be either form, and a worker must not assume it is the raise.
//    Retail has NEITHER form anywhere in the body.
//
// C. "NO STATE STORE" DOES NOT MEAN "OBJECT-FREE SCOPE".  MSVC 7.1 emits the
//    registration frame with no store at all whenever a destructor-needing
//    local's scope contains no throwing call.  Both
//      void f(void*a){ LateEmpty t(a); { LateEmpty u(a); } }
//      void f(void*a,int*b){ g(); LateEmpty t(a); { LateEmpty u(a); } nt(); *b=1; }
//    give frame + no raise + nState=1 + a NON-NULL action.  What distinguishes
//    retail is the NULL action, not the missing store.
//
// D. THE UNWIND TABLE IS FRONT-END DATA AND IS NOT REVISITED BY THE OPTIMIZER.
//    In the nested-block spelling above the object's constructor store is gone
//    from the generated code while the funclet `lea ecx,[slot]; jmp ~X` stays
//    in the unwind row.  And a scope whose objects are all trivially
//    destructible produces neither a state nor a frame -- measured with a plain
//    class, a base-subobject constructor, a member-subobject constructor, a
//    wrapper struct, and a placement new of a class with an out-of-line copy
//    constructor.  So within this family the two outcomes are:
//        destructor-bearing object  => frame AND a non-NULL action
//        object-free scope          => no frame at all
//    and retail (frame, NULL action, live payload) sits in the gap.  Fifty-odd
//    constructs were built and none reached it.
//
// E. RETAIL'S STORE IS DEAD AND MSVC KEPT IT.  Nothing reads [esp+4]: the
//    epilogue reads [esp+0] (`pop esi`) and [esp+0x08] (`mov ecx,[esp+8]`, the
//    saved fs:0) and nothing else.  Yet MSVC 7.1 deletes every dead store to a
//    stack local I could produce -- POD local, guarded store, base/member
//    constructor store, bare `volatile void*` local, and `volatile` *member*
//    when the class is trivially destructible.  The one spelling that keeps a
//    store (a `volatile` member in a class with a non-trivial destructor) forces
//    both a raise and a non-NULL action, i.e. it is exactly our 94-byte shape.
//
// F. CALLS NEVER PRODUCE A FRAME BY THEMSELVES.  Measured with a direct call, a
//    virtual call, a call through a function pointer and a call through a
//    member-function pointer, each followed by a store: no frame in any case.
//    A nested block, a do/while, a while, an if-with-declaration and three
//    levels of braces around the same throwing call: still no frame.  A
//    `throw()`-declared callee or an `extern "C"` callee after the object
//    deletes the object AND the frame (36 B, frameless), which re-confirms the
//    refutation of the throw() levers.
//
// G. THE FAMILY IS EIGHT BODIES AND NONE IS LANDED.  All-NULL unwind maps:
//    0x00149470 (1943 B, nState 1), 0x001B9D00 (972 B, 1), 0x002C4910 (86 B, 1),
//    0x003C7D20 (37 B, 2), 0x004C6A70 (37 B, 2, `mov al,1`), 0x004C6AA0 (51 B, 3),
//    0x004DAFA0 (206 B, 1), 0x0072EAA0 (35 B, 1).  Only 0x004C6AA0 is a close
//    structural relative: 51 bytes, a live payload, nState=3, all-NULL actions,
//    NO state store, and NO locals at all -- it reads as
//    `void f(void (*fp)()) { g1 = 0; g2 = 0; fp(); }`.  Three scopes in a
//    function with no locals is the cleanest instance of the shape anywhere in
//    the image and is unexplained by anything in A-F; whoever cracks it should
//    start there rather than here.
//
// NEXT LEVER.  Not another destructor spelling: A-F close that family.  The
// remaining candidates are (i) whatever makes MSVC allocate three scopes in a
// local-free function like 0x004C6AA0, and (ii) whatever keeps a store to a
// stack slot that nothing reads.  Both need a construct outside the
// "local object with a destructor" model that four prior sessions explored.
//
// ---------------------------------------------------------------------------
// 2026-09-29, THIRD PASS.  Findings H-J.  All tool-measured with the project's
// own VC7.1 (harness build/w11/: mat.py compiles a scratch TU, ehr.py reads the
// FuncInfo and unwind table out of the .obj by following the __ehhandler stub's
// relocations, mat.py counts state stores in BOTH encodings -- C7 44 24 d imm32
// and the 4-byte register form 89 <reg> 44 24 d, which two earlier passes of
// this file missed).  The detector is validated against retail itself (0 stores)
// and against the 94-byte spelling below (1 store).
//
// H. THE "NULL CLEANUP ACTION IS THE BLOCKER" PREMISE IS FALSE, AND IT NEVER
//    COULD HAVE BEEN.  The unwind table lives in .rdata; it is not among the 86
//    bytes the byte gate compares.  Measuring the COMPILED object settles it:
//    the plain local-object spelling at the bottom of this file already emits
//    FuncInfo (nState=1, nTry=0, single row {previous=-1, action=NULL}) --
//    byte-identical in shape to retail's 0x00E03430.  Findings D and E above
//    therefore describe a distinction the gate cannot see, and the ~60-construct
//    destructor search they motivated was chasing the wrong invariant.
//
// I. THE MISSING STATE STORE IS REMOVABLE, AND THE LEVER IS AN EXPLICIT
//    DESTRUCTOR CALL.  Declaring the destructor `throw()` and then CALLING it
//    explicitly at its use site
//        ~Rva002C4910OwnerSlot() throw() { m_p = 0; }
//        ...
//        Rva002C4910OwnerSlot ownerSlot(p);
//        ownerSlot.~Rva002C4910OwnerSlot();
//        this->bfmePrivateCommand38(...);
//    compiles to 82 bytes with the registration frame present and ZERO state
//    stores, FuncInfo still (1, 0, [None]).  Measured with probe.py against
//    retail: ours=82, 29 non-relocation diffs, first divergence at +0x25, i.e.
//    the 21-byte prologue and the first call are exact.  This refutes the
//    second-pass claim that "no spelling emits the frame with no state store",
//    and it is strictly better than the 94-byte bank: the state store is gone,
//    not merely relocated.
//
//    Why it works, as measured rather than reasoned: MSVC emits a state store
//    only when a potentially-throwing operation can be reached while an object
//    is live.  An explicit destructor call ends the object's lifetime BEFORE
//    the command call, so the command call is reached with nothing live and no
//    state is needed -- yet the front end has already registered the scope, so
//    the frame and its FuncInfo remain.  The same effect is reachable without
//    an explicit call by giving the destructor a `throw()` body, but only the
//    explicit-call form also drops the store (measured: implicit `~S() throw()`
//    with the command inside the scope still emits one store, 94 B).
//
// J. WHAT IS STILL MISSING AT 82 BYTES, AND WHY IT IS NOW A NARROW QUESTION.
//    Retail is 86.  The 4-byte and 11-byte deltas are one thing: the
//    destructor's `m_p = 0` lets MSVC prove the saved-this slot's final value
//    is 0, so it drops (a) the `owner->m_b` reload at +0x25/+0x28 and (b) the
//    ctor's `test eax,eax; je` guard at +0x2B/+0x2D, emitting
//    `mov ecx,[esp+0x18]; xor eax,eax; mov [esp+4],eax` where retail has the
//    reload, the guard and `mov [esp+4],eax` of the live pointer.  The next
//    lever is therefore a destructor that is throw() and non-empty, whose body
//    provably cannot throw, and which does NOT give MSVC a constant final value
//    for the ctor's slot.  Measured and still open: a dtor writing a separate
//    member (`int m_x`), a volatile member, a `void**` member, `m_p = m_p`, a
//    static/global store, a `throw()`-declared callee, and an out-of-line
//    destructor ALL reintroduce the state store or drop the frame.  Only a store
//    to the ctor's own slot with a constant keeps both the frame and the store
//    count at zero -- and that constant is exactly what costs the guard.
//
//    Do NOT re-run the destructor-spelling search of findings A-G: H shows the
//    invariant it was searching for does not exist.  Start from the explicit
//    destructor call and attack the constant.
//
// The identity (BfmeHostESE::bfmeDoBESE, pinned ILT 0x000376C8, matched caller
// at 0x002C51B0) and the 86-byte extent (ret 8 at +0x53) are unchanged and
// remain proven.

// The relative include reaches the header from the banked stash directory
// (targets/game/reverse/attempts/).  In its home TU, game/GameEngine/Source/
// Common/, it is "../GameLogic/command_source_type.h".
// cl: /DNDEBUG /MD /EHsc

#include "../../../../game/GameEngine/Source/GameLogic/command_source_type.h"

class BfmeStateESE
{
public:
	virtual void bfmeSlot00ESE();
	virtual void bfmeSlot01ESE();
	virtual void bfmeSlot02ESE();
	virtual void bfmeSlot03ESE();
	virtual void bfmeSlot04ESE();
	virtual float bfmeSlot05ESE();
};

class BfmeThingESE
{
public:
	unsigned char m_bfmeHeadESE[0x74];
	int m_bfme74ESE;
	unsigned char m_bfmeMidESE[0x188];
	BfmeStateESE *m_bfmeStateESE;
};

// The owner at BfmeHostESE+0x08.  unidentified_001BFE20 is the address-derived
// name already pinned at 0x0000D3B9 (Object+0x1FC accessor); the +0x04 member is
// unnamed because nothing in the body proves what it is.
class Object
{
public:
	void *m_rva001bfe1c;
	void *m_rva001bfe20;
	void *unidentified_001BFE20() const;
};

// Non-virtual on purpose: retail calls 0x0000BA2D, a __cdecl ILT thunk that
// jumps to the matched body at 0x002734B0, not a vtable slot.
class AIUpdateInterface
{
public:
	void bfmePrivateCommand38(void *first, CommandSourceType commandSource);
};

class BfmeHostESE
{
public:
	void bfmeStepESE(BfmeThingESE *thing, void *ctx);
	void bfmeDoAESE(BfmeThingESE *thing, void *ctx);
	void bfmeDoBESE(BfmeThingESE *thing, void *ctx);

	unsigned char m_bfmeHeadESE[8];
	void *m_bfme08ESE;
	unsigned char m_bfmeMidESE[0x340];
	int m_bfme34cESE;
};

// The 4-byte local whose destructor forces the registration frame.  Its name
// stays address-keyed: the body proves a 4-byte object with one pointer member
// and a destructor the compiler cannot empty, nothing more.
//
// The throw() destructor and the EXPLICIT destructor call are the measured
// mechanism of finding I above: together they give the registration frame with
// ZERO state stores, which is what retail has.  Do not "simplify" the explicit
// call away -- without it MSVC re-emits the 8-byte state store (94 bytes).
struct Rva002C4910OwnerSlot
{
	void *m_p;

	Rva002C4910OwnerSlot(void *p) { if (p) m_p = p; }
	~Rva002C4910OwnerSlot() throw() { m_p = 0; }
};

void BfmeHostESE::bfmeDoBESE(BfmeThingESE *thing, void *ctx)
{
	if (((Object *)m_bfme08ESE)->unidentified_001BFE20() != 0)
	{
		Rva002C4910OwnerSlot ownerSlot(((Object *)m_bfme08ESE)->m_rva001bfe20);
		ownerSlot.~Rva002C4910OwnerSlot();

		((AIUpdateInterface *)this)->bfmePrivateCommand38(thing, (CommandSourceType)(int)ctx);
	}
}

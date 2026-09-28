// ?setControlBarSchemeByPlayer@ControlBar@@QAEXPAVPlayer@@@Z
// partial score=0.92 date=2026-09-28
// (6th pass; TWO independent register residues, both shown to be a
// deterministic function of the 790-byte body -- see the sixth-pass section
// at the end of this header before spending another session)
// cl: /DNDEBUG /MD /EHsc
//
// ControlBar::setControlBarSchemeByPlayer -- retail 0x0049F8B0, 790 bytes.
//
// Identity: the Zero Hour twin (inputs/reference/CnC_Generals_Zero_Hour/
// GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp)
// forwards to ControlBarSchemeManager::setControlBarSchemeByPlayer (retail
// 0x004AE080), caches the "ControlBar.wnd:ButtonPlaceBeacon" (0x010FB954),
// ":ButtonIdleWorker" (0x010F56C0) and ":ButtonGeneral" (0x010FB844) keys in
// function statics and splits on Player::isPlayerActive. Callers are
// GameLogic::startNewGame and the PlayerList destroyNotify path.
//
// Retail's observer arm is switchToContext(CB_CONTEXT_OBSERVER_LIST, NULL)
// (0x0049E780, case 9) expanded in place, including the NULL path of
// showRallyPoint (0x0049DF00); the other arm calls switchToContext out of
// line. BFME ends with the setDefaultControlBarConfig tail that
// ControlBarSetControlBarSchemeByName.cpp also has, not ZH's
// switchControlBarStage.
//
// RESIDUE (2026-09-27, 61 non-reloc bytes, 790/790, 5 structural diffs):
// ONE register choice, `p`. Retail holds the parameter in EBX and
// buttonPlaceBeacon in EBP; this body holds p in EBP and buttonPlaceBeacon in
// EBX. The other four structural differences are not independent: with EBX
// free at +0x66, VC7.1 hoists the constant 2 of the second static's guard
// (bit 2) -- the same value as the THIRD static's init-state index -- into EBX
// and reuses it for the `or dword ptr [0x012F341C],2` and for
// `mov dword ptr [esp+0x20],2`. Deleting the transition null-check alone
// flips p into EBX, and then all four of those instructions become retail's
// immediates, byte for byte. So a p-in-EBX build is a zero-diff build.
//
// Trigger set, measured by deleting one region at a time (each flips p to
// EBX): the transition null-check (+0x12a), the selection-cache/selected
// null-check pair (+0x147), the oldSelected/chat block (+0x162) and the
// 0x012F4B98->invoke() null-check (+0x1e2) -- i.e. exactly the null-tested
// guards. NOT triggers: setRadiusCursorNone (+0x139), bfmeTake/showRallyPoint
// (+0x1ad), the eight winHide calls (+0x1f1), the Recorder tail (+0x2e6) --
// every unguarded call.
//
// This body's strategy is RETAIL'S NORMAL one, not an anomaly: the sibling
// setControlBarSchemeByPlayerTemplate at 0x0049FC90, same three statics and
// the same three winGetWindowFromId calls, allocates the parameter into EBP,
// the first window pointer into EBX and materialises the constant 2 into EBX
// exactly as here. Only this body, which carries the inlined observer arm,
// wants EBX for the parameter instead.
//
// Exhausted, all keeping the code byte-identical at 790/790 and 61 diffs
// (p stayed in EBP): null-test spelling (x / x != 0 / 0 != x / De Morgan),
// if-else vs nested-if vs ternary vs ||-form of the winSetFocus condition and
// of the buttonPlaceBeacon winHide argument, CSE-able local aliases at all
// four trigger sites, globals cached in locals, the static types as Int, Bool
// as bool/unsigned char, winHide/winEnable returning void, isPlayerActive
// const or not, m_currContext as Int, m_dword64 as unsigned, m_contextParent
// as void*, and swapping the two arms. eh_levers' throw() and /EHsc choices
// are no-ops. shape_family_levers finds no applicable family lever.
//
// ADDED 2026-09-27 (fourth pass). The residue is now stated as an EXACT
// register map, read off both objects rather than inferred. Five values want a
// callee-saved register and there are exactly three free (ECX is held by the
// SEH chain link for the whole function, so the SEH frame is part of why this
// is a three-way choice at all):
//
//              retail        this body
//   this       ESI           ESI
//   p          EBX  +0x17    EBP  +0x18
//   beacon     EBP  +0xe7    EBX  +0xe7
//   idleWorker EDI  +0xff    EDI  +0xff
//   general    [esp+0x24]    [esp+0x24]   (spilled in both)
//
// So the whole 61 bytes is ONE interference swap -- p and buttonPlaceBeacon
// trade EBX and EBP -- plus its two consequences: the constant-2 hoist into
// EBX (which only happens because EBX is free at +0x66) and the
// {oldSelected, chat-global} EAX/ECX swap at +0x162. Everything else, the
// whole 790-byte instruction sequence, is identical instruction for
// instruction. p and buttonPlaceBeacon each have exactly two uses and the
// same interference neighbourhood, so no source-level fact distinguishes
// them; this is VC7.1's graph colourer ordering two equivalent nodes.
//
// Seventeen further byte-neutral perturbations, all no-ops at 790/790 and 61
// diffs (p stayed in EBP):
//   - the guarded manager call is NOT a trigger here, unlike in a small
//     replica: dropping just the guard gives 756 bytes and p in EDI. The four
//     triggers above are the only ones, and the manager guard is not among
//     them (it was measured, not assumed).
//   - declaration order of the three function-local statics versus the three
//     window locals (locals declared first / statics split out / the three
//     winGetWindowFromId calls in a nested block). Declaration order does not
//     reach the colourer: all three are codegen-identical.
//   - m_contextParent[10] replaced by ten individual GameWindow* members at
//     the same ten offsets (identical [esi+disp] operands).
//   - m_dword64 cached in a local; TheWindowManager cached in a local; the
//     manager pointer cached in a local; p copied into a local; unused
//     Int/GameWindow* locals at the top of the function.
//   - the oldSelected/chat block rewritten five more ways: the store hoisted
//     unconditional before the chat test (789 bytes, 336 diffs -- the
//     compiler sinks the store back after the test and drops a jne), a Bool
//     local for the chat test, the `!= 0` spelling, an empty then-branch, the
//     mode tests nested five deep, and the &&-merged condition (789/336).
//     The duplicated-store shape above is the only spelling that puts the
//     store between the chat test and the jne, so the phi is authentic --
//     consistent with verdict #2, where the real in-TU switchToContext that
//     produces this block gave the identical residue.
//   - Drawable* -> void* on GameClient::slot2C/slot60, on
//     m_currentSelectedDrawable and on g_Rva012F340C (byte-neutral pointer
//     type changes in the IR).
//
// A minimal thiscall replica that reproduces the allocation exactly (guarded
// direct manager call, three winGetWindowFromId calls, if/else on
// p->isPlayerActive(), non-inlinable callees so nothing is dead-coded) is
// worth rebuilding before any further attempt: it gives the same answer in
// 0.6s. But note the trap -- in the replica the guarded manager call IS what
// costs p the good register, and that does NOT transfer to the real body, so
// the replica is only a fast oracle, not a model of the mechanism.
//
// Next lever: not a spelling and not a declaration order. It needs a
// different IR shape that still compiles to these 790 bytes and changes the
// relative priority of p and buttonPlaceBeacon, or it has to be accepted as a
// compiler-internal regalloc difference. blocker=regalloc.
//
// ADDED 2026-09-27 (fifth pass). Two corrections to the fourth pass above,
// both re-measured off the retail object, then a ~100-variant exhaustive
// search that closes the last two open IR dimensions.
//
// CORRECTION 1 -- "p and buttonPlaceBeacon have identical use counts (2) and
// identical interference neighbourhoods, so no source-level fact
// distinguishes them" is FALSE. Every read of EBX and EBP in retail, in
// address order (p = EBX, beacon = EBP):
//   0017 mov ebx,[esp+0x18]   def p
//   0027 push ebx             use p
//   00e7 mov ebp,eax          def beacon
//   0110 mov ecx,ebx          use p
//   0248 test ebp,ebp         use beacon
//   0255 mov ecx,ebp          use beacon
//   0280 test ebp,ebp         use beacon
//   02b8 mov ecx,ebp          use beacon
// p has 2 uses, beacon has 4. The neighbourhoods differ too: p is live
// [0x17,0x112] and beacon [0xe7,0x2c4], so buttonGeneral (defined at 0x112,
// from the third winGetWindowFromId) interferes with beacon but NOT with p.
// Degrees: beacon 5, idleWorker 5, p 4, buttonGeneral 3 -- and the node that
// is actually spilled is buttonGeneral, the LOWEST-degree one. So the
// colourer is not picking between two equivalent nodes and is not ranking by
// degree or by reference count; "tie-break between equivalent nodes" is the
// wrong frame and the next worker should not build on it.
//
// CORRECTION 2 -- "ECX is held by the SEH chain link for the whole function"
// is the wrong mechanism. ECX is a plain scratch: its only writes are
// `mov esi,ecx` (0x1d), the store `mov [0x12f340c],ecx` (0x173) and the
// funclet's `mov fs:[0],ecx` (0x309); it is otherwise pure vtable dispatch.
// It is unavailable to a long-lived value because it is VOLATILE across the
// many calls, not because the SEH frame holds it. The conclusion (only EBX,
// EBP, ESI and EDI are available) stands; the reason does not.
//
// EXHAUSTIVE SEARCH, fifth pass (~100 further variants, all measured at
// 790/790 / 61 diffs / p=EBP unless stated). Two IR dimensions that had never
// been touched, both invisible in the final machine code, are now closed:
//
//   - SCOPE / BLOCK DEPTH (untried before): an extra `{ }` around the
//     observer arm, around the else arm, around both, around the tail, and a
//     `switch (1) { case 1: ... break; }` wrapper around both arms (a folded
//     wrapper still adds real basic blocks). All six are codegen-identical at
//     790/61 with p in EBP. Block nesting does not reach the colourer.
//   - COMPILER PRAGMAS (untried before): `#pragma optimize("g",on)`,
//     `optimize("t",on)`, `optimize("","off")` (1030 bytes), `inline(0/1)`,
//     `auto_inline(0)`, `warning(4711)`, `pack(push,4)/pop`. All no-ops
//     except optimize-off, which deoptimises.
//
// Also no-ops at 790/61/p=EBP: the three statics in ONE declaration
// statement; the three window locals in one declaration; `const` on the statics
// and on the window locals; NameKeyType as unsigned; `(GameMode)8`; a typedef
// spelling for GameWindow*; `isPlayerActive()` non-const; TRUE/FALSE named
// constants; `m_contextParent[16]` (790 bytes, 73 diffs -- so the array bound
// IS IR-visible, but only off the witnessed extent); `m_isObserverCommandBar`
// as unsigned char; `m_dword64` as long; `switchToContext` taking an Int
// context; `(*p).isPlayerActive()`; a `Player &pl = *p` alias; a named Bool
// for the isPlayerActive result; a copy of buttonPlaceBeacon used for both of
// its calls; CSE-able aliases inside the decisive band for
// g_Rva005127A0InGameChat, g_Rva012F340C, Glo012F4B98, m_ptr2f0 and m_dword64;
// the four-term focus chain as (A&&B)&&(C&&D), A&&(B&&C&&D),
// (A&&B&&C)&&D, A&&B&&(C&&D), the De Morgan form, and `!(m == GAME_SHELL)`;
// nested-if instead of && for the selection-cache pair; `x` / `x&&y` /
// De Morgan for the selection-cache pair, the d64 guard, the invoke guard and
// the transition guard.
//
// FOCUS-CHAIN ORDERING, MEASURED EXHAUSTIVELY (all 24 permutations of
// {g_obj12F4C38==0, TheGameLogic!=0, mode!=8, mode!=GAME_SHELL} x two
// spellings each = 48 builds). This is the sharpest new datum, because it
// isolates what the coin actually keys on:
//   A,B,C,D (retail's order)          790 B,  61 diffs, p = EBP
//   A,B,D,C                            790 B,  63 diffs, p = EBP
//   A,C,B,D / A,C,D,B                  787-788 B, 287-289, p = EBX
//   A,D,B,C / A,D,C,B                  787-788 B, 287-289, p = EBX
//   B,C,D,A / B,D,C,A / C,B,D,A / ...  787-788 B, 287-293, p = EBX
//   C,D,A,B / C,A,B,D / D,C,A,B / ...  790-791 B,  82-334,   p = EBP
// No permutation that produces 790 bytes gives p in EBX, and every
// permutation that gives p in EBX has also broken the focus block (787-788
// bytes, 287+ diffs). The 790-byte shape and p=EBP are the same point in the
// code-shape space: reaching p=EBX requires changing the emitted bytes.
//
// SINGLE-CONDITIONAL DELETION MAP (finer than the fourth pass's, and it
// contradicts it in one place). Deleting one guard at a time, recording
// (size, p):
//   manager guard        756 B, p = EDI     <- the ONLY deletion that moves p
//                                                   to a THIRD register
//   transition +0x12a    786 B, p = EBP     (fourth pass reported this one as
//                                           a flip to EBX at 776 B; it is
//                                           not, at this spelling)
//   focus test 1 (A)     781 B, p = EBP
//   focus test 3 (mode!=8) 783 B, p = EBP
//   selcache pair +0x147 774 B, p = EBX
//   chat block    +0x162 736 B, p = EBX
//   focus test 4 (SHELL) 788 B, p = EBX
//   d64 block     +0x1ba 783 B, p = EBX
//   invoke guard  +0x1e2 786 B, p = EBX
//   beacon/idleWorker/general observer tests, the 8 winHides, the tail: EBP
// The flip set is exactly the observer arm between +0x147 and +0x1e2, and
// p's live range has ALREADY ENDED at +0x112. So the register the colourer
// gives a variable whose range closed 30 instructions earlier is decided by
// code p never reaches: this is a whole-function cost balance, not a local
// pressure peak, and it rules out every "adjust the pressure around p's uses"
// strategy as well.
//
// VERDICT after five passes and ~150 measured variants: this is a
// compiler-internal VC7.1 register-allocation difference that source cannot
// reach. The reconstruction is otherwise exact (same 227-instruction sequence,
// all relocations resolving, all callee names matching the ledger), and the
// 61 bytes are provably a single register choice with two mechanical
// consequences. Do not spend a sixth session on spellings. blocker=regalloc.
//
// ADDED 2026-09-28 (sixth pass). Two corrections and one closure. The fifth
// pass's conclusion is CONFIRMED and now rests on a much stronger measurement,
// but its "one cause" framing is WRONG: the residue is TWO independent
// register differences, and both are properties of the 790-byte code shape
// rather than of anything in the source.
//
// CORRECTION 3 -- the {oldSelected, chat-global} EAX/ECX swap at +0x162 is NOT
// a consequence of the p/EBX coin. The third pass asserted it was ("deleting
// the transition null-check flips p to EBX and then all of those instructions
// match"), the fourth listed it as a separate item, and neither measured it.
// It is now measured, on the five p-in-EBX deletion builds that were already
// compiled (v_del_d64, v_del_invoke, v_del_selcache, h_d_no_c1, h_d_no_c3):
// with p in EBX, all five STILL emit `mov eax,[esi+0x5c]` for the oldSelected
// reload and `mov ecx,[g_Rva005127A0InGameChat]` for the chat test. Retail
// emits the other way round. So the swap survives the coin: there are two
// residues, one callee-saved (p/beacon) and one scratch (a one-step
// EAX->ECX rotation phase difference), and fixing only the coin would not
// have been enough.
//
// CORRECTION 4 -- the scratch residue has a 3-state phase indicator that makes
// the closure mechanical. Signature = the registers of the two `mov`s in the
// 0x160..0x180 window, as (oldSelected, chat, focus-chain global): retail is
// CAA, this body is ACA. It is exactly the shape predicted by
// docs/analysis/allocation_residue.md (a value feeding only a test takes EAX
// without moving the round-robin pointer, so the reload after the 0x15f call
// takes the next register: ECX in retail, EAX here). Tools left in build/ for
// the next seat: `phase.py` (prints the signature of one build) and
// `sigsweep.py` (scores every compiled variant in build/ and build/var/ for
// size, diffs, signature and p's register, from the .obj files alone -- no
// recompile, a couple of seconds).
//
// CLOSURE (the sharpest datum of this pass). Scoring all 147 previously
// compiled variants that emit EXACTLY 790 bytes -- every spelling sweep of
// passes 3-6, the 48 focus-chain permutations, the block-depth and pragma
// batches, the deletion diagnostics and this pass's new ones -- gives:
//     147 objects at 790 bytes, 147 of them signature ACA, 0 at CAA,
//     147 of them with p in EBP.
// The only two CAA builds in the whole set are 786 and 732 bytes, i.e.
// deletions. Together with the fifth pass's 48-build ordering result (no
// 790-byte ordering puts p in EBX) this upgrades the earlier "one point in
// the code-shape space" claim from the callee-saved coin to BOTH residues:
// the register assignment is a DETERMINISTIC FUNCTION OF THE 790-BYTE BODY.
// ~150 mutually independent IR spellings that all emit the same 790 bytes all
// get the same registers, so no source that emits these 790 bytes can emit
// retail's registers with them. That is the argument for closing this body,
// and it is stronger than "no lever was found".
//
// NEW NEGATIVES this pass (all 790/790/61/p=EBP, signature ACA, i.e. no-ops):
//   - the shared `static __forceinline` accessor, which is the one lever in
//     docs/register_mirror_experiments.md that ever LANDED a callee-saved
//     mirror (0x0024E990, an EBP/EBX swap, fixed by factoring both
//     Object::getControllingPlayer calls through one accessor; and the
//     RegallocLever-2/3 __fastcall table adapter, the same mechanism from the
//     other side). Tried at five sites: one accessor for the three
//     winGetWindowFromId calls, the same taking the manager as a parameter,
//     one for the four getGameMode() calls, one for the isPlayerActive() test
//     and one for the three nameToKey static initialisers. Every one is
//     codegen-identical here, so the lever that fixed 0x0024E990 does not
//     reach this body. (The getGameMode accessor is not a no-op: it restructures
//     the body to 668 bytes, because sharing it lets VC7.1 merge the two
//     focus-chain reads -- wrong code, not a fix.)
//   - `register` on the parameter (the only hint the language offers the
//     colourer here).
//   - name/hash-ordering chaos, to test whether the colourer's node order is a
//     front-end artifact that irrelevant renaming can perturb: renaming the
//     three window locals, renaming the parameter and the three statics,
//     renaming the unused GameWindowManager virtual slots, and adding an unused
//     member function. All no-ops, so the order is not name-hash sensitive.
//   - const/volatile on the pointee: rejected by the compiler (needs the
//     in-class declaration changed too, which pass 5 already did for const).
//
// VERDICT after six passes and ~160 measured variants: closed as a
// compiler-internal VC7.1 difference. blocker=regalloc. If a seventh seat
// picks this up, do not sweep spellings -- run build/sigsweep.py first, and
// only spend time on a lever that can emit a 790-byte body this one cannot.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ControlBarContext { CB_CONTEXT_NONE = 0, CB_CONTEXT_OBSERVER_LIST = 9 };
enum GameMode { GAME_LAN = 1, GAME_SHELL = 4, GAME_INTERNET = 5 };
enum RecorderModeType { RECORDERMODE_PLAYBACK = 1 };

class Drawable;
class Player
{
public:
	Bool isPlayerActive() const;
};

class GameWindow
{
public:
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
};

class GameWindowManager
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual void slot06C() = 0; virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0; virtual void slot080() = 0;
	virtual void slot084() = 0; virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0; virtual void slot098() = 0;
	virtual void slot09C() = 0; virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0;
	virtual Int winSetFocus(GameWindow *window) = 0;                          // slot 0xB0
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id) = 0; // slot 0xDC
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ControlBarSchemeManager
{
public:
	void setControlBarSchemeByPlayer(Player *p);
};

class RecorderClass
{
public:
	RecorderModeType getMode();
};

// TheGameLogic's mode word, as the matched switchToContext reads it.
class GameLogic
{
public:
	GameMode getGameMode() const { return m_gameMode; }

private:
	char m_unmodelled00[0x10c];
	GameMode m_gameMode;               // +0x10c
};

class GameInfo
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0;
	virtual Bool isMultiPlayer() = 0;                                          // slot 0x2C
};

class InGameUI
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual void slot06C() = 0; virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0; virtual void slot080() = 0;
	virtual void slot084() = 0; virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0; virtual void slot098() = 0;
	virtual void slot09C() = 0; virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0; virtual void slot0B0() = 0;
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0; virtual void slot0DC() = 0; virtual void slot0E0() = 0;
	virtual void slot0E4() = 0; virtual void slot0E8() = 0; virtual void slot0EC() = 0;
	virtual void slot0F0() = 0; virtual void slot0F4() = 0; virtual void slot0F8() = 0;
	virtual void slot0FC() = 0; virtual void slot100() = 0; virtual void slot104() = 0;
	virtual void slot108() = 0; virtual void slot10C() = 0; virtual void slot110() = 0;
	virtual void slot114() = 0; virtual void slot118() = 0;
	virtual void setRadiusCursorNone() = 0;                                    // slot 0x11C
};

class GameClient
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0;
	virtual Drawable *slot2C(Int id) = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3C() = 0; virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0; virtual void slot50() = 0;
	virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60(Drawable *draw) = 0;
};

class BfmeTransitionMD
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0;
};

// ControlBar+0x2f0: a virtual at +0x10, and the target of the 0x004AFA80 call.
class BfmeSourceCB;
class Gen_004AFA80
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0;
	void bfmeTake(BfmeSourceCB *source);
};

class Rva0058C040
{
public:
	void invoke();
};

class Rva005127A0InGameChat;

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern RecorderClass *TheRecorder;
extern GameLogic *TheGameLogic;
extern GameInfo *TheGameInfo;
extern InGameUI *TheInGameUI;
extern GameClient *TheGameClient;
extern BfmeTransitionMD *g_bfmeTransitionMD;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;
extern void *g_obj12F4C38;
extern Rva0058C040 *Glo012F4B98;
extern Drawable *g_Rva012F340C;

class ControlBar
{
public:
	void setControlBarSchemeByPlayer(Player *p);
	void populateObserverList();

protected:
	void switchToContext(ControlBarContext context, Drawable *draw);
	void setDefaultControlBarConfig();

private:
	char m_unmodelled00[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;   // +0x30
	GameWindow *m_contextParent[10];                       // +0x34
	Drawable *m_currentSelectedDrawable;                   // +0x5c
	ControlBarContext m_currContext;                       // +0x60
	Int m_dword64;                                         // +0x64
	char m_unmodelled68[0x208];
	Bool m_isObserverCommandBar;                           // +0x270
	char m_unmodelled271[0x7f];
	Gen_004AFA80 *m_ptr2f0;                                // +0x2f0
};

void ControlBar::setControlBarSchemeByPlayer(Player *p)
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayer(p);

	static NameKeyType buttonPlaceBeaconID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon");
	static NameKeyType buttonIdleWorkerID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId(0, buttonPlaceBeaconID);
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId(0, buttonIdleWorkerID);
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId(0, buttonGeneralID);

	if (!p->isPlayerActive())
	{
		m_isObserverCommandBar = true;

		// switchToContext(CB_CONTEXT_OBSERVER_LIST, NULL), as retail expands it.
		if (g_bfmeTransitionMD)
			g_bfmeTransitionMD->slot04();
		TheInGameUI->setRadiusCursorNone();
		if (g_Rva012F340C != 0 && m_currentSelectedDrawable != 0)
			m_ptr2f0->slot04();
		Drawable *oldSelected = m_currentSelectedDrawable;
		m_currentSelectedDrawable = 0;
		if (g_Rva005127A0InGameChat == 0)
		{
			g_Rva012F340C = oldSelected;
			if (g_obj12F4C38 == 0 && TheGameLogic != 0 &&
				TheGameLogic->getGameMode() != 8 && TheGameLogic->getGameMode() != GAME_SHELL)
				TheWindowManager->winSetFocus(0);
		}
		else
		{
			g_Rva012F340C = oldSelected;
		}
		m_ptr2f0->bfmeTake(0);
		if (m_dword64 != 0)
		{
			TheGameClient->slot60(TheGameClient->slot2C(m_dword64));
			m_dword64 = 0;
		}
		if (Glo012F4B98 != 0)
			Glo012F4B98->invoke();
		m_contextParent[2]->winHide(true);
		m_contextParent[9]->winHide(true);
		m_contextParent[3]->winHide(true);
		m_contextParent[4]->winHide(true);
		m_contextParent[5]->winHide(true);
		m_contextParent[8]->winHide(true);
		m_contextParent[6]->winHide(true);
		m_contextParent[7]->winHide(false);
		populateObserverList();
		m_currContext = CB_CONTEXT_OBSERVER_LIST;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(true);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(true);
		if (buttonGeneral)
			buttonGeneral->winEnable(false);
	}
	else
	{
		switchToContext(CB_CONTEXT_NONE, 0);
		m_isObserverCommandBar = false;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(
				(TheGameLogic->getGameMode() != GAME_LAN && TheGameLogic->getGameMode() != GAME_INTERNET) ||
				!TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(false);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(false);
			buttonGeneral->winEnable(true);
		}
	}

	if (TheRecorder == 0 || TheRecorder->getMode() != RECORDERMODE_PLAYBACK)
		setDefaultControlBarConfig();
}

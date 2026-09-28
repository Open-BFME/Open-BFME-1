// ?init@InGameUI@@UAEXXZ
// partial score=0.93 date=2026-09-27
// Attempt body for ?init@InGameUI@@UAEXXZ @ 0x00440B40, 1091 bytes.
//
// THE BODY IS ALREADY IN PLACE at
// game/GameEngine/Source/GameClient/InGameUI.cpp (the `void InGameUI::init( void )`
// marked `// ?init@InGameUI@@UAEXXZ present-unmatched`, with the TU-local
// BfmeInit* views immediately above it).  This file records the measured
// residual and the levers that are now closed, so the next attempt starts from
// the measurements instead of rediscovering them.
//
// ---------------------------------------------------------------------------
// IDENTITY IS SETTLED AND IS NOT createReplayControl.  The lift's name is
// wrong; the body is InGameUI::init:
//   * inputs/reference/shims/sweep/Common/SubsystemInterface.h:10 records the
//     retail SubsystemInterface vtable as "0 ~SubsystemInterface 1 init
//     2 loadIniFilesFromLegend 4 reset 5 update", so slot 1 is init.
//   * game/GameEngine/Source/Common/System/subsystem_interface.h:10 says the
//     same ("1 init 2 loadIniFilesFromLegend 4 reset 5 update").
//   * InGameUI's vtable 0x010F5B38 (installed by ctor 0x0044B800) slot 1
//     (+0x004) is the ILT thunk 0x00425027, and
//     game/gen_small/thunks_017.cpp:816 is `void j_00025027() { b_00440b40(); }`
//     -- that thunk routes to 0x00440B40.
//   * The body then does exactly InGameUI::init: the INI subsystem load, the
//     eight TheGlobalLanguageData font triples, the tactical view, the inlined
//     createControlBar and createReplayControl, new ControlBar, and
//     m_windowLayouts.clear().
// The ledger row still carries the lift's name; re-home it on landing.
//
// ---------------------------------------------------------------------------
// MEASURED STATE, 2026-09-27 (tools/probe.py, MSVC 7.1 under wine).  THIS IS
// THE CURRENT STATE; everything below it is history.
//   size    ours=1091  retail=1091     exact
//   diffs   2 non-reloc bytes, and only 2: the immediate of the `push` at
//           +0x332, `push 0x2F8` (retail) vs `push 0x32C` (ours).  Byte
//           offsets 0x333 and 0x334, both inside that one 5-byte push.
//   shape   1.000 -- every instruction in the body now has retail's form.
//   The scoped gate `./build.sh game/GameEngine/Source/GameClient/InGameUI.cpp`
//   reports the same one blocker and nothing else: 68 of 69 rows verify, the
//   only failure being ?stopCameoMovie@InGameUI@@UAEXXZ, which fails
//   identically BEFORE any of this session's edits (measured by reverting them
//   and re-running the gate), so it is pre-existing and out of scope here.
//
// CLOSED THIS SESSION (residual A and B of the history below are now done):
// 7. The winCreateFromScript receiver-load scheduling (history's residual A)
//    is resolved in the tree as it stands -- the two call sites at +0x2E8 and
//    +0x312 now emit retail's instruction multiset, vtable reload included.
//    Do not re-open it.
// 8. m_windowLayouts.clear() (history's residual B) is FIXED WITHOUT touching
//    the shared stlport header, and the fix is worth stating as a rule:
//      * `BFME_PARTICLE_LIST_NODE_TAIL` (stlport/_list.h:79) is NOT a defect
//        and must stay.  Retail's own
//        ??0?$list@PAVSuperweaponInfo@@...QAE@ABV01@@Z at 0x0076F640 allocates
//        its sentinel with `push 0x2C`, and that row is landed from THIS TU,
//        so turning the macro off regresses it (measured: 3 -> 2 diffs here but
//        `FAIL ??0?$list@PAVSuperweaponInfo@@...` in the gate).
//      * The two retail node sizes come from two different retail translation
//        units, and this file is a merge of both, so one macro cannot serve
//        both.  init therefore clears the list itself, over a TU-local node
//        view with retail's 12-byte node, using the SAME pinned deallocator
//        clear() reaches:
//          _STL::allocator<BfmeInitWindowLayoutListNode>().deallocate(cur, 1)
//        The idiom is the one removeSuperweapon already uses for the
//        superweapon list in this file.
//      * THREE SPELLINGS MATTER, each one measured, and getting any of them
//        wrong costs 20 bytes and a prolog `push ebx`:
//        (a) The head must be a VALUE LOADED FROM MEMORY, not the address of
//            the list.  m_windowLayouts is the list object at this+0x10 and
//            stlport's head sits in _STLP_alloc_proxy::_M_data, which is at
//            offset 0 because that proxy's only base, _MaybeReboundAlloc, is
//            empty.  So this+0x10 holds the head POINTER.  Spelling the head
//            as `&m_windowLayouts` lets MSVC hoist `lea edi,[esi+0x10]` into
//            a callee-saved register, which costs a prolog push and loses
//            retail's `mov eax,[esi+0x10]` at +0x373, +0x38C, +0x396, +0x39B.
        (b) The head must be re-read in the LOOP CONDITION, not hoisted into
//            a local before it.  The deallocator call is opaque, so a
//            re-loaded head is what makes MSVC re-materialise it after the
//            call; a local `head` is kept in a callee-saved register instead.
        (c) Advance the cursor BEFORE the deallocate, exactly as
//            _list.c's _List_base::clear() does:
                _List_node<_Tp>* __tmp = __cur;
                __cur = (_List_node<_Tp>*)__cur->_M_next;
                this->_M_node.deallocate(__tmp, 1);
            Reading `next` into a separate local and assigning `cur = next`
            after the deallocate instead makes MSVC carry the cursor in eax
            and emit a trailing `mov eax,edi` inside the loop.  The stlport
            order carries it in edi and matches retail byte for byte.
//      * Both link resets are needed: `head->next = head` and
//        `head->prev = head`, each spelled with a fresh head load, which is
//        what puts retail's `mov eax,[esi+0x10]` / `mov [eax],eax` /
//        `mov eax,[esi+0x10]` / `push 0x30` / `mov [eax+4],eax` run at
//        +0x396..+0x3A0.  Writing only the first store lets MSVC sink it
//        past the following `push 0x30`.
//
// ---------------------------------------------------------------------------
// RESIDUAL, exactly as measured
// ONE instruction, two bytes, and it is a SHARED-LAYOUT blocker:
//   +0x332  retail `push 0x2F8`   ours `push 0x32C`
// That is the allocation size of `NEW ControlBar`, i.e. retail's
// sizeof(ControlBar) is 0x2F8 and the class this TU compiles against is
// 0x32C -- 0x34 too long.  The ctor call, the null test, the EH state store
// and the store-after-construct order around it all already match, so this is
// purely the immediate.
//
// It cannot be fixed from this body, and the reason is now measured rather
// than assumed.  `NEW ControlBar` is the only spelling that can size the
// allocation (it is the only one that emits the null test and the EH state
// store; a placement-new or explicit-operator-new spelling does not), and the
// immediate it pushes is sizeof(ControlBar) from the class declaration.  So
// the class has to be right.
//
// HOW WRONG THE CLASS IS (measured by appending offsetof() probes to a copy of
// this exact TU, so the real preprocessor state applies, and reading the
// negative-subscript errors; do not re-measure this the cheap way -- a probe
// in a scratch TU that only includes PreRTS.h and ControlBar.h gives DIFFERENT
// offsets, because the layout constants such as NUM_CONTEXT_PARENTS are not
// all visible there):
//   sizeof(ControlBar)          tree 0x32C   retail 0x2F8
//   m_animateWindowManager              0x00C          0x00C   agrees
//   m_animateWindowManagerForGenShortcuts 0x010         0x010   agrees
//   and then EVERY one of the 25 remaining members `tools/name_oracle.py
//   --class ControlBar` witnesses from retail's own FieldParse table is at a
//   DIFFERENT offset in the tree -- the first divergence is
//   m_defaultControlBarPosition, retail +0x18.  Nothing after +0x010 in this
//   class declaration can be trusted, so there is no local patch: BFME's
//   ControlBar is a genuinely different class and reconstructing it is its own
//   job.  Two existing declarations are both wrong in the same direction:
//     inputs/reference/CnC_Generals_Zero_Hour/.../GameClient/ControlBar.h  0x32C
//     inputs/reference/shims/controlbarlayout/GameClient/ControlBar.h      0x33C
//   and this TU's include path uses the first (the shim directory is not on
//   InGameUI.cpp's `// cl:` line; only ControlBar.cpp and
//   ControlBarProcessCommandTransitionUIThunk.cpp pull the shim in).
//   A per-TU shim directory on InGameUI.cpp's include path would be the
//   mechanical shape of the fix, but it has to carry a real 0x2F8 member list,
//   which is exactly the research that is missing.  Inventing padding to reach
//   0x2F8 would make the immediate right and the class wrong, so it is not
//   done here.
//
// ---------------------------------------------------------------------------
// HISTORY -- earlier attempts.  Superseded by the sections above; kept because
// re-measuring them is expensive.  Nothing here should be re-tried.
// ---------------------------------------------------------------------------
// LEVERS CLOSED, EARLIER ATTEMPTS
// 1. The 0x1-byte prolog cascade is GONE.  The earlier 676-diff state came
//    from `sub esp,8` + `push esi` where retail has `push ecx; push esi;
//    push edi`; a one-byte-longer prolog shifted everything after it.  The
//    cause was the missing BFME-only tail (below), not the frame: adding the
//    tail gave MSVC 7.1 the same live ranges and the prolog now matches.
// 2. Read TheGlobalLanguageData per field use, never into a local (kept from
//    the previous attempt).  Retail reloads 0x12F1484 before every access,
//    including three consecutive loads with no intervening call, because it
//    cannot prove a store through `this` does not alias the global.
// 3. militaryCaption sits at this+0x884, right after militaryCaptionTitle at
//    +0x878 -- no pad between them (kept from the previous attempt).
// 4. VTABLE ENTRIES COST THE OBJECT NOTHING.  Only the vtable POINTER takes
//    four bytes, so the data part of a class view starts at +4, NOT at the
//    offset of its last vtable slot.  This was the single biggest silent error
//    and it is worth stating as a rule: a view padded to slot N still needs
//    `pad[Ntarget - 4]`, not `pad[Ntarget - N]`.
//      BfmeInitSelfView  0x13A4 - 0x1B8 -> 0x13A4 - 4   (store was at 0x11F0)
//      BannerUI          0x44   - 12    -> 0x44   - 4
//      Gen_00587D40      0x30   - 4     -> 0x30   - 4   AND it needs a
//        declared virtual, or it has no vtable pointer at all (was 0x2C).
//    Verified with a `template<int N> struct SizeQuery;` error trick on a
//    scratch TU: sizeof(ControlBar)=812=0x32C, a 3-virtual BannerUI=60=0x3C,
//    a virtual-free Gen=44=0x2C.
// 5. The by-value AsciiString argument must be passed as a BARE LITERAL
//    (`winCreateFromScript( "ControlBar.wnd", NULL, NULL )`), not as a
//    `BFMERetailAsciiString(...)` temporary.  Retail's +0x2E8..+0x2F8 is
//    MSVC 7.1 reserving the three argument slots, then constructing the
//    parameter IN PLACE in the first slot with the one out-of-line converting
//    constructor:
//        push 0 / push 0 / push ecx        ; the three slots
//        mov [esp+0x14], esp               ; record the argument block for EH
//        mov ecx, esp                     ; this = the first slot
//        push 0x10F575c                   ; the layout name
//        call ??0BFMERetailAsciiString@@QAE@PBD@Z
//    A temporary instead builds the string in a frame slot and copies it in.
// 6. Declaring no destructor on BFMERetailAsciiString is right: a
//    user-provided destructor, even an empty one, makes MSVC materialise the
//    temporary.  stopCameoMovie calls releaseBuffer() explicitly, so it does
//    not need one.  (A temporary plus an empty destructor was the state the
//    timed-out attempt left in the tree; it is not the cause of the residual.)
//
// ---------------------------------------------------------------------------
// RESIDUAL AS IT STOOD THEN (0 bytes now: A and B are closed by items 7 and 8
// above, C is the one residual that is left)
// A. 0x2E8 and 0x312, the two winCreateFromScript call sites -- 8 bytes net.
//    Ours hoists the receiver's vtable load ABOVE the by-value argument's
//    construction and keeps it in the callee-saved edi across the ctor call;
//    retail loads it after the construction, in a caller-saved register:
//      ours   +02e8 mov ecx,[TheWindowManager] / mov edi,[ecx]
//             +02f0 push 0 / push 0 / push ecx / mov ecx,esp
//             +02f7 mov [esp+0x14],esp / push lit / call ctor
//             +0305 mov ecx,[TheWindowManager] / call [edi+0x68]
//      retail +02e8 push 0 / push 0 / push ecx / mov [esp+0x14],esp
//             +02f1 mov ecx,esp / push lit / call ctor
//             +02fd mov ecx,[TheWindowManager] / mov edx,[ecx]
//             +0305 call [edx+0x68]
//    and symmetrically at the second site (retail `mov eax,[ecx]` where ours
//    has none).  The instruction multiset is otherwise IDENTICAL, including the
//    `mov [esp+0x14],esp` EH argument-block record and the second site.  The
//    cause is MSVC 7.1 evaluating the object subexpression before the argument
//    block: with the load before the ctor call, the vtable is live across a
//    call and must go in a callee-saved register, which is what the extra
//    `push ecx` (a different register than retail's) also shows.
//    DISPROVED: `throw()` on the constructor (no change at all); a
//    `(const BFMERetailAsciiString)"literal"` cast (reintroduces the copy);
//    hoisting TheWindowManager into a named local (worse -- MSVC then also
//    saves ebx, 15 structural differences, 0.952).
//    NOT YET TRIED: making the receiver expression something MSVC 7.1
//    schedules after the arguments; a two-class spelling so CSE cannot merge
//    the two receiver loads; the per-call-site absolute-slot route the earlier
//    attempt rejected on C2109.
// B. +0x382 `push 0xc` vs ours `push 0x2c` -- 1 byte, m_windowLayouts.clear().
//    CLOSED by item 8 above.  One correction to the reasoning here, because it
//    sent the earlier attempt down the wrong path: the macro is not merely
//    inconvenient, it is REQUIRED here -- retail's own list copy constructor
//    allocates a 0x2C sentinel from this same TU -- so "the shim needs a
//    per-type opt-in" is the wrong fix.  Writing the clear out over a node
//    view of the retail size was the right one, and it needs no header edit.
// C. +0x33E `push 0x2f8` vs ours `push 0x32c` -- 2 bytes, `NEW ControlBar`.
//    Measured sizeof(ControlBar) against the vendored Zero Hour
//    GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h is 0x32C;
//    retail allocates 0x2F8.  tools/name_oracle.py --class ControlBar lists 36
//    retail-witnessed members with m_radarAttackGlowWindow last at +0x2E8, so
//    retail's object really is about 0x2F8 and the Zero Hour declaration is
//    0x34 too long.  inputs/reference/shims/controlbarlayout/GameClient/
//    ControlBar.h is the existing corrected-layout shim; it is 0x10 LONGER
//    still (0x33C) because it adds BFME's NeededUpgrade/BuildUpgrades, so
//    neither declaration gives 0x2F8.  The ctor is pinned as
//    ??0ControlBar@@QAE@XZ (0x0049D660, reached through the ILT thunk
//    0x0001CA58), i.e. a CONSTRUCTOR, so the allocation can only be sized by
//    `NEW ControlBar` -- a placement-new or AllocationGuard spelling (the
//    pattern in game/GameEngine/Source/GameClient/InGameUIConstructor.cpp:79)
//    does not reproduce retail's null test, EH state store and store-after-
//    construct order.  This needs a decision about the shared ControlBar
//    layout, so it is the parent's to schedule.
//
// NOT LANDED, and deliberately: functions.csv and
// game/GameEngine/Source/GameClient/InGameUICreateReplayControlThunk.cpp are
// untouched, so both remain truthful -- the row still points at the naked
// __emit copy under the lift's wrong name, and no re-homing has been claimed
// without a byte-verified landing.

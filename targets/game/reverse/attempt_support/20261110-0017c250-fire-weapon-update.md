# 0x0017C250 AIAttackFireWeaponState::update (979 B) -- EXACT

Best candidate: `build/wf/0017c250/final.cpp` (probe: 979/979, 37 relocs,
`result EXACT (modulo relocation slots)`). Defines
`?update@AIAttackFireWeaponState@@UAE?AW4StateReturnType@@XZ`.
cl: `/DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object`
(bank flags; only the Coord3D include dir changed to the canonical header).

## What fixed the 24-byte residue (+00B2..+01E6)

Diagnosis: all differing temps were one step ahead in MSVC 7.1's EAX->ECX->EDX
round-robin (allocation follows source order, so the else-block copy at +010F
precedes the m_28 block at +00B2). Retail's Coord3D copy is x=EAX, y=ECX, z=EDX
(natural x,y,z order; the load emitted first is whichever got ECX, so retail
shows the y load first). The bank's hand-written Y-X-Z copy constructor was a
compensation for the wrong phase.

Fix (two changes, both needed):
1. Canonical `Lib/Coord3D.h` struct; copy field by field
   (`pos.x = victim->getPosition()->x; ...`, BFME 2 donor 2bac16a65
   `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter_Unresolved.cpp`
   AIAttackFireWeaponState::update, its row 0x0034AAC8 matched in BFME 2).
   Struct assignment `= *getPosition()` / `= m_cachedPos` emits a `lea` block
   copy (981 B, wrong).
2. The flag-0x533 test reads the template through an inline accessor:
   `weapon->getTemplate()->flag533()` (donor: `weaponTemplateIs16B(weapon->getTemplate())`,
   which is also EXACT here). That accessor adds the one rotation step retail has.
   The goal-object id must stay `m_machine->m_20` (the donor's
   `getMachine()->m_goalObjectID` spelling removes a step at +002D: 11 diffs).

640-combo sweep (sweep.py/sweep.log): EXACT iff id=direct AND f533 via
getTemplate(); owner/goal accessor spellings, getAI()/m_ai, getCurLocomotor()/m_curLocomotor,
getPosition()->x / m_cachedPos.x are all neutral.

## Trials ruled out (this session)
- canonical struct copy `= *victim->getPosition()` / `= victim->m_cachedPos`: 981 B, lea block copy.
- canonical field copy alone (v3): 28 diffs (phase one ahead).
- rotation_sweep.py on v3: all 32 toggles +0.
- getMachine()->m_20 / machine local copy (v4): 11 diffs (+002D..+0039, +0074).
- direct `weapon->m_04->m_533`: 30; `weapon->getTemplate()->flag529()` too: 3 diffs.
- ai != 0, getAI(), getCurLocomotor(), nested ifs, ai declared at top, kind2 De Morgan,
  bool atPosition init/else-first/late store, int atPosition: no gain or worse.

## Landing notes (read-only checks; not landed)
(a) `tools/ilt_oracle.py check` on the symbol at 0x17C250: CONFIRMED (p_false 1.17e-03).
(b) No helper the TU emits has its own ledger row (COMDATs: PartitionFilter/
    PartitionFilterSameMapStatus/Rva0016A9F0FunctorValueWrapper ctors, dtors, ??_G,
    inline accessors). Retail inlines all three filter constructions and dtors.
(c) Globals by address: 0x01085DD0 `??_7PartitionFilterSameMapStatus@@6B@` (dir32),
    0x01097144 `??_7Rva0016A9F0FunctorValueWrapper@@6B@` (dir32; the bank's
    Rva0016A9F0PlayerFilter was renamed to this recorded name, also used by
    LargeGroupBonusUpdate_update.cpp), 0x01083B5C `??_7PartitionFilter@@6B@` (dir32),
    0x012ED5B8 `?ThePartitionManager@@3PAVPartitionManager@@A` (data_rows/dir32),
    0x01075350 `__real@00000000` (dir32). "Ram" literal at 0x0109A0AC has NO
    dir32/data_rows record (may need `dir32_record.py`). 0x01005C88 is the EH FuncInfo.
    Callees: all bound to ledger/pin names; `fireCurrentWeapon` now uses the
    ledger name `?fireCurrentWeapon@BfmeHostETB@@QAEXPAVBfmeArgETB@@@Z` (0x1CDA40)
    through a cast view (still EXACT).
    OPEN: the call at +0311 (ILT 0x0001960F -> 0x00149E60) is retail's
    constructor of the possible-to-attack filter (body stores vptr 0x010956C4,
    m_next=0, +8=obj, +0xC=cmdSource, +0x10=attackType, returns this, ret 0xC;
    no vptr store precedes the call and EH state 1 is set after it). The ledger
    names that body `?set@Rva00149E60@@QAEAAV1@HHH@Z` (Rva00149E60Set.cpp); the
    candidate references `??0Rva00149E60@@QAE@HHH@Z`, which has no row or pin.
    A member-call `set` spelling cannot reproduce the code (it needs a prior
    inline ctor). Needs either a ctor rename of row 0x00149E60 (constructor
    semantics, ZH PartitionFilterPossibleToAttack(attackType,obj,cmdSource)
    field order) or an ILT pin `??0Rva00149E60@@QAE@HHH@Z,0x0001960F` route=0x00149E60.
(d) TU: replace the naked lift in
    `game/GameEngine/Source/GameLogic/AI/AIAttackFireWeaponStateUpdateThunk.cpp`
    (current row) with final.cpp via add_match --replace-existing; no visible
    helper body needs another home.

## Landing (2026-11-10)

Landed in `AIAttackFireWeaponStateUpdateThunk.cpp`, replacing the naked lift.

The possible-to-attack filter constructor at 0x00149E60 matches Zero Hour's `PartitionFilterPossibleToAttack(AbleToAttackType, const Object*, CommandSourceType)` in field order, and `ilt_oracle` CONFIRMS that exact decoration at 0x00149E60. However, functions.csv already gives that name to the 32-byte body at 0x004C12B0 (PartitionManager.cpp; vtable 0x010FD964, no m_next), and the oracle CONTRADICTS the name there.

Pinning the name at 0x00149E60 would create a two-candidate name, which the pin-delta gate refuses. So the class here is address-named `Rva00149E60` with Zero Hour's parameter types. Follow-up: correct the 0x004C12B0 row's identity, then rename this pin to the Zero Hour constructor name.

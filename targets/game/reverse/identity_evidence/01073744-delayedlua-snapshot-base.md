# VA 0x01073744 is the Snapshot base vtable: Inner01073744 -> BfmeSnapshotBase

Four DelayedLuaEventList TUs spelled their polymorphic base `Inner01073744`
(address-derived placeholder for the vtable at VA 0x01073744). The base is the
Snapshot base, and the TUs are corrected to `BfmeSnapshotBase`, the name the
kept copy already uses.

## Evidence

- dir32 row 1268 records `??_7BfmeSnapshotBase@@6B@` at `0x01073744`.
- symbols.csv pin note 5152 (on `??1DelayedLuaEventList@@UAE@XZ` at
  `0x000EDC40`) assigns the ctor/destructor pair and states the destructor
  body "destroys same array then writes Snapshot vptr".
- Team_notifyTeamOfObjectDeath.cpp already declares `class BfmeSnapshotBase`
  with an inline-empty virtual destructor and a `__declspec(novtable)`
  `DelayedLuaEventList` derived class for the same VA, with a comment citing
  the dir32 record. The corrected TUs mirror that declaration exactly.
- All seven `??1DelayedLuaEventList@@UAE@XZ` COMDAT copies are byte-identical
  (77 bytes); they differed only in the base-vtable reloc symbol.
  `tools/link_census.py keep_rule` over current objects in census link order
  reports 0 losers after convergence (was 6: four Inner01073744 spellings in
  Rva002BCEE0DelayedLuaDispatch.cpp, GameLogicSendObjectCreated.cpp,
  AIWaypointPathStates.cpp, FlameCleanup00293E50.cpp, plus two BfmeBaseVUQ
  spellings in Rva002E7410BfmeThingDispatch.cpp and BfmeOwnerBRGo7530.cpp,
  which need no correction entry since Bfme* is already a placeholder).
- Layout and codegen are unchanged: vptr-only base, inline-empty derived
  destructor, same member offsets. Six scoped `./build.sh` verifications still
  match all 8 parent rows.

## Scope

Private per-TU base-class views only; no ledger row, pin, or dir32 record is
renamed. The `??_7BfmeSnapshotBase@@6B@` vtable itself keeps three
pre-existing losers in unrelated TUs (go-dup-base, w3dterra x2), untouched
here.

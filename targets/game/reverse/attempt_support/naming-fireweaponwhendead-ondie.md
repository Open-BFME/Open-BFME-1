# Naming review: FireWeaponWhenDeadBehaviorOnDie.cpp (name-lane queue)

Queued with 4 member + 1 local placeholders. No renames made (lane rule);
this is the evidence record for future blind votes. Model note: this review
was done by Muse Spark (Meta), which `name_lane.py` does not accept as a
voting identity, so no vote was submitted — proposals below await
cross-vendor votes.

## New evidence: the full INI table (retail, RVA 0xC8B468)

Dumped from the baseline EXE (note: `symbols.csv` stores this pin's address
as an RVA, 0x00C8B468; the loaded VA is 0x0108B468). Five entries:

| key | parser | +off |
|---|---|---|
| StartsActive | parseBool | 0x70 |
| ActiveDuringConstruction | parseBool | 0x71 |
| DelayTime | parseReal | 0x74 |
| DeathWeapon | parseWeaponTemplate | 0xB0 |
| WeaponOffset | parseCoord-ish | 0x78 |

`DelayTime` is new: no prior note names the +0x74 float. It is a Real
(seconds), and the ctor sets
`m_deferCount88 = maxOf(ModuleData->m_field74, 1)` when `> 0.0f`, while
`onDie` defers while `m_deferCount88 > 0`.

## Per-placeholder verdicts

- `m_field74` (ctor-thunk view only; inside OnDie's `m_unreconstructed72`):
  PROPOSE `m_delayTime` — exact EA key→member convention of its neighbours
  (`StartsActive`→`m_initiallyActive`, `DeathWeapon`→`m_deathWeapon`).
- `m_deferCount88` (behavior +0x88): KEEP — defer-count semantics now doubly
  evidenced (DelayTime derivation in ctor + `> 0` deferral test in onDie).
  No EA/Upstream name exists for a behavior member; do not strip the
  descriptiveness.
- Local `d`: KEEP — identical convention in the sibling
  (`FireWeaponWhenDeadBehavior.cpp:124` uses `d` the same way).
- `m_skipStatus2Check71` / `m_weaponOffset78`: KEEP offset-named — INI keys
  (`ActiveDuringConstruction`, `WeaponOffset`) are BFME-own with no upstream
  member to adopt, per the ctor-thunk policy note; the descriptive prefixes
  match witnessed use.
- `m_unreconstructed*` gaps: KEEP — no member evidence at those offsets.
- `m_initiallyActive` (+0x70): already EA's own (oracle 1.00 + INI table).

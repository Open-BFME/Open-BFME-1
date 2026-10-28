# 0x001E8720 `?reloadWithBonus@Weapon` (371B) — blocked, near-miss banked

- Status: blocked. Closest bank: `0x001E8720-20261028-reloadwithbonus-stash.cpp.txt`
  (this directory), 247-line real C++ reconstruction.
- What matches: early/provider blocks, all 10 call sites via ILTs
  (0x413B2 bfmeQueryERT, 0x1F253 findObjectByID, 0x1BD74, 0x3C8E9
  getWeaponInWeaponSlot, 0x40589 rebuildScatterTargets, `__ftol2`), prologue.
- Remaining diff: x87 delay-math FPU order (retail evaluates reload-`fild`
  first; MSVC 7.1 evaluates the store side first in every probed spelling)
  plus loop-tail register allocation. Needs a fresh codegen idea, not more
  of the same variants.
- Identity: solid. Ledger rows the name at this RVA (thunk); disassembly
  proves Weapon reload logic; sibling callers agree (ZH call sites
  `+0x6F`/`+0x12C` match). Not a misidentified body.
- Donors (rev `beed8a16`): ZH GeneralsMD `Weapon.cpp` `reloadWithBonus` is
  the semantic donor; BFME1 deltas are the ammo-provider early checks,
  guarded status store, x87 delay math, direct shared-reload fan-out.
  BFME2 `WeaponReloadWithBonus.cpp` is a BFME1-donated port but diverged
  (164B vs 371B) — not portable. BFME2's own `blocked` verdict on its
  0x001E8720 is its own binary's `LocomotorSet::DoXfer` range, inapplicable.
- Rename lead for the name lane (NOT landed: a unilateral pin here would
  over-claim row 54677 `?get@Rva001EB140@@QAE_NXZ`, matched 17B in
  `R2GuardedFieldGetters.cpp`, "identity not recovered"): the body reads
  like `?isSharedReloadTime@WeaponSet@@QBE_NXZ` — 17B null-checked flag
  read (`m_curWeaponTemplateSet+4`, flag `+0xE8`); the two retail call
  sites `0x001E8720+0x6F`/`+0x12C` sit where ZH calls
  `sourceObj->isReloadTimeShared()` (ZH `WeaponSet.h:243` declares it;
  `WeaponSet.cpp:1039` already defines it present-unmatched).
- Next step: beat the x87 order problem (consult `docs/shape_levers.md`
  x87 entries and BFME2 recipes); loop-tail regalloc after that.

# 0x00454EF0 `?update@WaypointMap` (366B) — triage, not attempted

- Claimed and released with no reconstruction (worker time went to 0x001E8720).
- Donor lead, uncompared: ZH GeneralsMD `MapUtil.cpp` `ln::update`. No
  BFME2 counterpart found (`rg` over donor ledger and `Code/` empty).
- Next step: run `brief.py`, `callees.py`, compare against the ZH lead,
  then attempt normally.

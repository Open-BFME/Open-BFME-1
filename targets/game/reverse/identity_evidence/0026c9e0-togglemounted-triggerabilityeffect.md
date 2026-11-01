# 0x0026C9E0 ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect (406 B)

Target facts (BFME 1 retail):
- Boundary: EH prologue at 0x0026C9E0, single RET at +0x195.
- Identity: `tools/ilt_oracle.py check ?triggerAbilityEffect@ToggleMountedSpecialAbilityUpdate@@MAEXXZ 0x0026C9E0`
  -> CONFIRMED (exact, p_false 3.9e-04); the UAE/EAE spellings are CONTRADICTED.
- The first call (ILT 0x0003FA30 -> 0x002A9850) is the base:
  `ilt_oracle check ?triggerAbilityEffect@SpecialAbilityUpdate@@MAEXXZ 0x002A9850` -> CONFIRMED
  (exact). That body's ledger row (??1WeaponSetSpecialAbilityUpdate@@UAE@XZ) and pins are
  address-derived or wrong; this TU calls it through the existing pin
  ?callAt002A9850@Rva0025EF90Owner@@QAEXXZ and does not rename it.
- Offsets from the body: owner +0x08, module data +0x04 (byte +0x259), state +0x24; object
  flag words +0x128/+0x130 bit 0x800, contain +0x1FC (slots 64 and 37), AI +0x204 (slots 96
  and 127), Object slot 10 drawable, drawable byte +0x3AC, TheControlBar +0x24.
- Other callees keep their ledger names (callees.py): Object::notifyModelConditionChanged,
  Object::findModule, NameKeyGenerator::nameToKey, 0x001C9AC0/0x001BEF00/0x001C9A10/0x001BEEE0,
  0x00267D00; literal "SpecialDisguiseUpdate".

Donor facts (Open BFME 2 45afcff3 ToggleMountedSpecialAbilityUpdate.cpp, byte-matched there
at 0x004ADF0B): the gates and the dismount/mount arms. BFME 1 lacks the donor's mounted-
template branch and its flag8C store; it tests object flag words where the donor tests kinds.
Lever: the branch test reads the flag word volatile so the mount arm re-reads it like retail.
Verification: probe EXACT 406/406 modulo relocations.

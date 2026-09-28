# 0x0017BA90 banked rewrite: two names corrected in the stash

The banked stash for the AIAttackAimAtTargetState per-frame worker
(retail 0x0017BA90) was rewritten from retail. Two names from the old stash
are replaced.

1. **`WeaponTemplate::m_range` (+0x24) -> `m_field24`.**
   - At retail +0x236..+0x265 the body tests `weapon->m_template[+0x24] > 0`
     and then calls `normalizeAngle(relAngle - [+0x24])`, where `relAngle` is
     `Thing::bfmeRelativeAngleTo`'s result. The value is an angle offset
     subtracted from a relative angle, not a range.
   - `name_oracle.py --class WeaponTemplate --offset 0x24` reports the offset
     as not witnessed. So the old name is refuted, and no replacement is
     proven: the offset name stands.
2. **`Object` -> `Rva001BE100` (the pairing is false).**
   - The old stash reached ILT 0x00048B80 -> 0x001BE100 as a guessed
     `Object::hasAnyWeapon` through a linker alternatename.
   - The ledger's matched name for that body is `?has@Rva001BE100@@QAE_NXZ`,
     and the new stash calls it through a view of that receiver so the call
     links. `class Object` itself is still modelled in the file.

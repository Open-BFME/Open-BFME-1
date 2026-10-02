# FreeLifeBody::internalChangeHealth at 0x002134E0

The 344-byte body at 0x002134E0 was matched as
`?apply@TimedHealthRestore002134E0@@QAEXMPAUDamageInfo@@@Z`, an address-derived
placeholder. It is FreeLifeBody's override of BodyModuleInterface slot 32,
`internalChangeHealth(Real, DamageInfo*)`.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

- ILT stub 0x000318E5 is `E9 F6 1B 1E 00`, a jump to 0x002134E0.
- Stub VA 0x004318E5 appears once in data: at 0x010A8420, slot 32 (+0x80) of the
  table at VA 0x010A83A0.
- That table is installed at object +0x10 by both FreeLifeBody special members:
  - `??0FreeLifeBody@@QAE@PAVThing@@PBVModuleData@@@Z` (0x00213390) at 0x002133B4:
    `C7 46 10 A0 83 0A 01` (`mov [esi+0x10], 0x010A83A0`)
  - `??1FreeLifeBody@@UAE@XZ` (0x002132B0) at 0x002132BD:
    `C7 41 10 A0 83 0A 01` (`mov [ecx+0x10], 0x010A83A0`)
  FreeLifeBody's class identity is independent of this body: its
  `getModuleNameKey` (0x002132F0) and literal name getter (0x002132D0) return the
  string `FreeLifeBody`, and slot 0 of the same table is the matched
  `?attemptDamage@FreeLifeBody@@UAEXPAVDamageInfo@@@Z` (0x00213690).
- Slot 32 of the sibling body tables:

  | table VA | installed by | slot 32 VA | resolves to |
  |---|---|---|---|
  | 0x010A7718 | `??0ActiveBody` 0x00211A50 | 0x00435337 | 0x002103A0 `?internalChangeHealth@ActiveBody@@UAEXMPAVDamageInfo@@@Z` |
  | 0x010A87E8 | `??0ImmortalBody` 0x00213990 / `??1ImmortalBody` 0x002139E0 | 0x004048E5 | 0x00213AD0 `?internalChangeHealth@ImmortalBody@...` |
  | 0x010A90D0 | `??0RespawnBody` 0x00214650 / `??1RespawnBody` 0x002146A0 | 0x00430BBB | 0x002147E0 (dump; RespawnBody's override) |
  | 0x010A83A0 | `??0FreeLifeBody` / `??1FreeLifeBody` | 0x004318E5 | 0x002134E0 (this body) |

  Five other body tables (0x010A8010, 0x010A85F0, 0x010A8BA8, 0x010A8E18,
  0x010A9320) inherit 0x002103A0 in slot 32 unchanged.
  ILT 0x00035337 is independently pinned in `symbols.csv` as ActiveBody's
  internalChangeHealth thunk called by ImmortalBody's override, matching Zero
  Hour, where ImmortalBody overrides `ActiveBody::internalChangeHealth`.
- The body's fall-through calls ILT 0x00030BBB (`E9 20 3C 1E 00` -> 0x002147E0),
  the slot-32 entry of RespawnBody's table, and FreeLifeBody's constructor calls
  RespawnBody's constructor (0x00214650) as its base. An override that defers to
  its direct base's version of the same slot is the usual
  `RespawnBody::internalChangeHealth(delta, info)` shape.
- The argument shape agrees with slot 32 elsewhere: float delta plus
  `DamageInfo*` (`ret 8`), entered with ECX at the +0x10 interface subobject
  (object at this-8, module data at this-12), like the ActiveBody override.

## Conclusion

A virtual slot keeps its name across overrides, so the override of slot 32 in
FreeLifeBody's table is `FreeLifeBody::internalChangeHealth`. The mangled form
follows the existing ActiveBody row: `?internalChangeHealth@FreeLifeBody@@UAEXMPAVDamageInfo@@@Z`.

The same table evidence names the fall-through callee: 0x002147E0 is the slot-32
override in RespawnBody's table, so the source calls
`RespawnBody::internalChangeHealth` and a pin
`?internalChangeHealth@RespawnBody@@UAEXMPAVDamageInfo@@@Z,0x002147E0` is added.
Its body stays the `?d_002147e0` dump; the older address-derived pin
`?apply@Rva002147E0Owner@@QAEXMPAUDamageInfo@@@Z` is still used by
DelayedDeathBody.cpp and is left alone.

Not claimed: member names inside the body (`fieldD4`.. and the slot 4/21
virtuals stay shape names).

## Independent re-derivation (sol/w5 aad9fc1d90)

A separate session reached the same identity. Facts it adds:

- The constructor 0x00213390 also stores primary table 0x010A8538 and
  Snapshot+0x0C table 0x010A8470. The factory `friend_newModuleInstance`
  (0x0011F940) allocates 0xF4 bytes and calls it.
- ActiveBody's interface table 0x010A7718 has slot 31 = 0x0020E870 and
  slot 33 = `ActiveBody::setMaxHealth` (0x00210690). The matched
  `ActiveBody::attemptHealing` (0x0020FBC0) calls slot 32 as
  `internalChangeHealth(float, DamageInfo*)`.
- Interface fields +0xD4/+0xD8/+0xDC/+0xE0 are complete-object
  +0xE4/+0xE8/+0xEC/+0xF0, which the constructor initializes.
- Extent: `ret 8` at 0x0021361C and 0x00213635, INT3 at 0x00213638 (344 bytes).
- The fall-through callee 0x002147E0 reads the float at ESP+4, then the
  DamageInfo pointer's +8 field (VA 0x00614850), and forwards both arguments
  to `ActiveBody::internalChangeHealth` through ILT 0x00035337 at VA
  0x0061488E. Its exits are `ret 8` (0x00214921, 0x00214947, 0x00214967),
  with INT3 at 0x0021496A (394 bytes).

# DamageModuleInterface slot 2: onBodyDamageStateChange

## Witness and owner

Retail SHA-256 and the full factory/constructor/primary-getter proof for
FireWeaponWhenDamagedBehavior are recorded in the sibling evidence file
`damagemodule-slots0-1-callbacks.md`. All facts were independently read from
the retail executable with pefile/Capstone. Addresses below are RVAs unless
marked VA.

Factory 00116F30 calls ILT 0002A379 -> constructor 001FB5D0. Its store at
001FB666 installs VA 010A3DD4 at object +0x28, after seating the abstract
three-pure-virtual DamageModuleInterface table VA 010A1BFC at that offset.
Primary table VA 010A3F04 slot 2 -> getter 001FB1E0 returns the registered
`FireWeaponWhenDamagedBehavior` literal VA 010909A4, independently naming
the owner. This proof does not rely on any old constructor alias claim.

Slot 0 of the damage table is ILT 00008C8D -> matched onDamage at 001FB930;
slot 1 is 0001FB81 -> 001FB230; **slot 2 is 0001FD11 -> 001FB240**. The
latter is an E9 stub, and its VA appears as a dword exactly once in the
complete mapped retail image, at VA 010A3DDC. A zero dword follows the
three-entry table. This is the owner's own override, not a shared base body.

GeneralsMD DamageModule.h declares, in order, onDamage, onHealing, then
onBodyDamageStateChange. The named nontrivial BoneFXDamage callback in the
same slot (00250940) independently anchors that order. GeneralsMD
FireWeaponWhenDamagedBehavior.h:128 explicitly supplies this class's empty
public virtual override:

```
void onBodyDamageStateChange(const DamageInfo*, BodyDamageType, BodyDamageType)
```

The method is non-const, returns void, and has three four-byte arguments.
Retail 001FB240 is precisely `C2 0C 00` (`ret 12`), with INT3 immediately
at 001FB243. Its proven extent is three bytes. The class DamageInfo and enum
BodyDamageType mangling agree with the named BoneFXDamage sibling:
`?onBodyDamageStateChange@FireWeaponWhenDamagedBehavior@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z`.

Replace the three-unsigned-int placeholder `?slot@Rva001FB240@@QAEXIII@Z`
without changing its extent; remove its obsolete class/body from
Rva001FAdjacentTinyBodies.cpp. Use the already-defined types and class view
in FireWeaponWhenDamagedBehavior_onDamage.cpp, adding only the two witnessed
virtual declarations and empty bodies. Verify its existing onDamage too.

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

## OpenContain: introducing owner and misplaced claim correction

The complete sixteen-constructor table/chain census in
`damagemodule-slots0-1-callbacks.md` proves that OpenContain introduces the
shared damage callbacks. Its own registered constructor 002277A0 installs
abstract damage table VA 010A1BFC at +0x2C, then concrete VA 010AC004. Its
primary slot-2 literal getter independently names OpenContain. Slot 2 of its
damage table is ILT 0001AA5A -> **00219450**; twelve containing-family tables
reuse that same stub in slot 2. All twelve uses are accounted for by the
registered constructor census, and the introducing owner is OpenContain,
not one of its subclasses.

GeneralsMD OpenContain.h:127-129 explicitly defines this empty public virtual
non-const method with const DamageInfo* and two BodyDamageType arguments.
The retail bytes are C2 0C 00, immediately followed by INT3, for an exact
three-byte body and twelve-byte argument cleanup. Its full decorated name is
`?onBodyDamageStateChange@OpenContain@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z`.

The existing same-name row at **006CF660** is wrong: its only justification
is `icf-owner=?Scale@RenderObjClass@@UAEXMMM@Z`. Retail has no identical-COMDAT
folding, and the actual OpenContain table points to the separate body 00219450,
not the ILT 0003AB25 -> 006CF660. The common `ret 12` byte shape never proved
that misplaced identity. Retire only OpenContain's 006CF660 row with a tombstone;
this correction makes no new assertion about the other old names on 006CF660.
Then replace the opaque 00219450 ret12 row with the witnessed method and
same three-byte extent. The existing OpenContain.cpp source remains unchanged.
This preserves the real method spelling while correcting its retail address;
no descriptive-to-opaque rename is involved.

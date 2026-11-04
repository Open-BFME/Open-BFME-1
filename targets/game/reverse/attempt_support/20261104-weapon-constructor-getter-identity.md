# Weapon duplicate constructor: the preserved getter twins are not the BFME field

Queue #40, census aafdf413e9, key0xF46298FD. Read the prior0x001E52D0
linking outcome (re_attempts.log44461) first: it retained the broad constructor
because removing it loses authored getter aliases. Native ctor extent158B
and empty direct-callee inventory were rechecked.

New exact deletion test: remove only the unmatched
Weapon::Weapon(const WeaponTemplate *,WeaponSlotType) from Weapon.cpp,
retaining WeaponConstructor.cpp and the factory. Normal joint build fails
exactly three of55 rows: dup_000c8c40, dup_0047a320 and dup_005c3090,
all borrowing object-symbol
`?getSuspendFXDelay@WeaponTemplate@@QBEIXZ`. The other52 rows survive.

Attempted natural-provider repair (no synthetic anchor): extend the existing
WeaponTemplate forward declaration in WeaponConstructor.cpp into a narrow
view with the independently measured+0x518 suspend field, define the native
const getter there, and rehome the existing aliases with normal add_match.
name_oracle reports WeaponTemplate+0x518 m_suspendFXDelay with confidence1.00;
the actual158B BFME constructor independently reads that same+0x518 field.

The first normal add_match rehome was REFUSED and restored its row:

```
retail0x000C8C40: 8b 81 c8 01 00 00 c3  // mov eax,[ecx+0x1C8];ret
truthful BFME getter:8b 81 18 05 00 00 c3 // mov eax,[ecx+0x518];ret
```

Independently reading all three native7B extents confirms that0x0047A320
and0x005C3090 also read+0x1C8. Their native direct-callee inventories are
empty. Their prior byte match used the Zero Hour header view's getter at
+0x1C8, not the BFME WeaponTemplate suspend field. Equal bytes therefore
establish neither that class nor that member role at these addresses.

This is the new prerequisite: establish the three native helpers' true
identity/owner (or preserve them honestly under address-derived definitions)
before deleting the wrong broad constructor. Do not define a BFME
WeaponTemplate accessor at the contradicted+0x1C8 merely to retain aliases,
and do not add an emission anchor to keep an unrelated source alive.
The original three rows/banks and both production sources are restored
byte-for-byte. No ledger row or pin changed, and no failed source remains.
The restored provider/consumer scoped gate is recorded in the commit.

Donor:f6d845ecd439374ef476ce04c992a2b848eb2c99,
Code/GameEngine/Source/GameLogic/Object/Weapon.cpp and WeaponCtor.cpp,
commits95820483ad3 and9ae57e840be. BFME2 removed unrowed Zero Hour bodies;
its remaining helper anchor/provider choices concern its own ledger and
ABI. Its member-pointer emission anchor was explicitly ruled out here.
Code maps to BFME1game; none of its fields/flags/headers were imported.
No relevant donor source delta exists between revieweda9286ede andf6d845ec.

This is new failed-repair/identity evidence, not a recovered body or completed
linking task. Historical queue258B are not claimed as newly linked bytes;
the available olde9a5ae5b4c census cannot prove current linking.

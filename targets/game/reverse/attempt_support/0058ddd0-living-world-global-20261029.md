# Resource-bar global binding

Checked 2026-10-29 at upstream `34991a9a`; donor snapshot
`b5a7b8290a0c4c20b03a3664609d434904e228eb`.

The resource-bar update at RVA `0x0058DDD0` read VA `0x012F1028` through
`Glo012F1028Type *Glo012F1028`. Nothing defines that decorated global.
The existing data owner is `LivingWorldLogic *TheLivingWorldLogic` in
`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp`.
Its data row and source document the GameEngine initialization literal,
the storing initSubsystem specialization, constructor and class-name string.
That is BFME 1 identity evidence, independent of the donor.

Declare that existing global and cast it to this unit's existing field view.
The view's offsets, function identities and callee declarations are unchanged.
No second datum, pin, import alias or guessed class identity is introduced.

The reviewed BFME 2 LivingWorldLogic unit and data ledger likewise use one
typed owner, at that game's VA `0x00DFEF10`. That is corroborating donor
context, not evidence for a BFME 1 address or layout. No donor body is copied.

Validation:

- Scoped build: both functions exact, 71 + 872 = 943 bytes; the existing
  provider's four-byte data row is exact. All 14 direct callees are rowed.
- `find_declared_unmatched.py`: every emitted definition is matched.
- Before, `link_check.py --census-only` reports the unresolved old name.
- After, the ordinary current-object preview is UNKNOWN: the downloaded
  `ea2916a82d` census lacks 22,719 current ledger objects on this host.
  Provider and consumer bytes were checked, but global selection could not
  be established. No new census or increase in linked bytes is claimed.

Carry this changed data-reference scope into the next normal census.

# Remaining animation-sound global consumers

The existing four-byte pointer at VA 0x012F10D0 has one verified owner:
`?TheAnimationSoundModuleManager@@3PAVAnimationSoundModuleManager@@A` in
`game/GameEngine/Source/GameClient/AnimationSoundModuleManager.cpp`.
Its target identity, factory allocation, lifecycle and consumer routes are
documented in `pointer-globals-012f10d0.md`. That proof is retained; no data
row, pin or private class identity is added or renamed.

Two source consumers still referenced obsolete spellings of that cell:
GameClient initialization at RVA 0x0042F5A0 used
`?g_animationSoundClientBehaviorGlobal@@3PAVAnimationSoundClientBehaviorGlobal@@A`,
and the animation-sound updater at 0x006059F0 used the same identifier
decorated with `BfmeResetSubsystem *`. Both names' existing DIR32 records
point to the owner's same four-byte cell. Change their declarations and
references to the owner, retaining explicit local-view casts at subsystem
initialization and notification calls. The initializer's new allocation,
its constructor name and all call contracts remain unchanged.

The BFME 2 reference f6c3838e7b source
`Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`
likewise defines and uses `AnimationSoundModuleManager *TheAnimationSoundModuleManager`,
including local-view projections at animation-sound notification sites.
This supports the single-owner repair pattern; the BFME 1 address and type
identity come from its existing target proof, not the donor's different RVA
or class layouts.

Private before/after object comparisons retain all 2,666 initializer bytes
and 903 updater bytes, with 196 and 23 relocations respectively. Only the
two obsolete global-reference names become the existing owner name.
The complete external definition/reference sets are otherwise unchanged.
The native paired owner/consumer gate verifies 3/3 function rows, the one
data row, twenty string references and eighty DIR32 references.
The source sweep finds no remaining use of any of the five old spellings
listed in `pointer-globals-012f10d0.md`.

The native before census preview at 2026-11-14 12:41 / 1a248a7b47 reports
LINKED 0 -> 0 bytes for both consumers, with further translator, container,
cleanup and selected-provider blockers. This binding repair does not prove
a complete link, runtime behavior, or a crash/memory fix.
The staged native preview is UNKNOWN after its 45-second deadline for
both consumers and their provider. No linked-byte gain is claimed.

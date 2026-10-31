# Spell-store update: use the existing Palantir singleton

Base `daddaf108`; claimed RVA `005999B0`, complete 1,175-byte
`Rva005999B0Screen::frameUpdate`. The census queue at `afbe8bafb6`
reports its sole unresolved global as `Screen005999B0`.

## BFME 1 facts and repair

Native `005999C8` loads the pointer at VA `012F4B98` and the following
instructions null-test it. The existing data row assigns that exact four-byte
datum to `AptPalantir *TheAptPalantir` in `AptPalantirConstructor.cpp`.
The native factory `006FC330` allocates the object, invokes its constructor
route and stores EAX to this address at `006FC36D`. Retail contains four zero
bytes there. This is a pointer to the Palantir, not a new spell-store object.
The data row's callback strings and factory evidence establish its existing
identity independently of this consumer's unchanged bytes.

Replace only the bodyless `void *Screen005999B0` declaration and its null
test with the existing typed global. No second definition, pin, alias, new
name, class layout, shared header or data row is introduced. A related-unit
search finds no remaining use of the old spelling in `game/`; historical
banks remain unchanged.

Normal verification of the consumer and existing data owner passes 5/5 rows,
one data row, 24 DIR32 references, 12 literals plus an empty-string reference,
and the body guards. The consumer's full 1,175 raw bytes are identical.
Of its 90 relocations only DIR32 at +25 changes, from the obsolete global
to the existing owner. All 12 other external code definitions and their
relocations are identical; none is added or removed. Frozen definitions pass.

## BFME 2 donor review

Reviewed pinned donor `b5a7b8290a0c4c20b03a3664609d434904e228eb`:
`Code/GameEngine/Source/GameClient/GUI/parseSpellIndex_Thunk.cpp` explicitly
uses `RadarWindowOverrideSource *theRadarWindowOverrideSource` for BFME 2's
analogous singleton. Its provider in
`Code/GameEngine/Source/Common/System/RadarWindowOverride.cpp` has different
layout and behavior; those are not imported. The existing canonical-global
ownership pattern in `Code/GameEngine/Source/Common/Rva005EEA20Find.cpp`
and its data row is applicable. `ControlBar_Rva0035B03E.cpp` in the donor's
GUI/ControlBar directory supplies additional shared-source naming context,
not independent proof of this BFME 1 datum. Native BFME 1 accesses and its
existing data owner above establish the actual repair. The automated global
proposal found no unambiguous typed rewrite for the old `void *` spelling;
this manual change relies on the explicit native/ledger evidence instead.

## Linking evidence and limits

Fetched the official daily index into a new ignored directory, preserving
the previous cache: `afbe8bafb6`, 2026-10-31 12:37, workflow 41192765101.
Against this frozen selection the consumer changes from unresolved/0 to
LINKS/1,169 authored bytes. The unchanged data-owner unit remains blocked by
its existing `BFMERetailAsciiString` destructor duplicate and selected
`AptPalantir` destructor; these are not cleared by this consumer repair.

The current-selection check is UNKNOWN: 22,717 newer/missing ledger objects
are unavailable locally. Thus 1,169 bytes is a frozen-index prediction,
not a new census measurement or a current/full-image linking guarantee.
No runtime result is claimed. Original objects, native disassembly, build
logs, relocation comparison and both previews are retained under ignored
`build/continuation-no-qwen-20261031-153050` and the matching create-only
diagnostic run at `W:/OpenBFME/diagnostics/`.

Qwen and other local inference models were not started. Scoped verification
used the shared ten-worker build limit; no Unreal process was changed.

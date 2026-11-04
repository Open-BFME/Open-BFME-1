# Overridable::deleteOverrides: remove three wrong Zero Hour emitters

Queue #29, census aafdf413e9. Native identity/39B boundary are independently
established in identity_evidence/000e6cc0-overridable-deleteoverrides.md.
Before writing, regenerated callees.py: sole recursive call is ILT32D1C.

The queue lists consumers, not the offending emitters. Private probes of
ScienceStoreReset and ThingFactory_reset both produce the exact39B provider
modulo the same recursive relocation. The old indexe9a5ae5b4c identifies
wrong copies in Locomotor.cpp, ControlBar.cpp and GameLogic.cpp; all three
read Zero Hour Common/Overridable.h, whose inline uses deleteInstance()
through pool glue instead of native global deleting-destructor dispatch.
Their matched reset callers already live in separate native TUs.

The repair applies the existing TU-local inline-hiding technique before
PreRTS, which already includes Overridable transitively. The signature uses
`deleteOverrides(void)` but its recursive call uses `deleteOverrides()`;
a token-paste dispatch redirects only the former definition to unused
zhInlineDeleteOverrides while declaring the real method out of line. All
macros are undefined before the rest of the TU. A placement after PreRTS
was measured ineffective and corrected before publication.

Actual final normal COFF for each of the three modified sources contains
`?deleteOverrides@Overridable@@QAEPAV1@XZ` only as section0 (undefined), and
contains no zhInlineDeleteOverrides symbol. No wrong copy remains in these
three objects. Their calls bind to the existing independently matched39B
provider in Bfme5DropAndHandOver.cpp. No alias or pin is introduced.

Normal scoped verification:171/171 code rows plus3 data rows in the three
emitters;5/5 existing owner and queue-consumer rows in four further TUs.
All strings/constants/DIR32/body checks pass. Six ControlBar funclet labels
were naturally renumbered and verified by unwind-state discovery; native
bodies remain exact. find_declared_unmatched reports no unmatched definitions.
No shared header or compiler setting changes.

Donor context: reviewed latestBFME2a9286edec5374324e40c1f5dd29c3a8ab5582283
Code/GameEngine/Include/Common/Overridable.h and
Code/GameEngine/Source/Common/OverridableDeleteOverrides.cpp. It separates the
out-of-line declaration/provider and uses global delete. BFME1 layouts and
39B provider remain established by its own native proof; BFME2 flags/addresses
and absent-from-retail anchor are not imported. Mapping donorCode to localgame
is only source/evidence correspondence. Pinned build donor remains59e3f8f825.

Linking before: current preview UNKNOWN (22769 unreadable changed ledger
objects versus oldindexe9a5ae5b4c); after: bounded preview remains UNKNOWN.
The three wrong emitter removals are object-proven. The queue's329 historical
bytes are not claimed as newly linked bytes without a fresh complete census.

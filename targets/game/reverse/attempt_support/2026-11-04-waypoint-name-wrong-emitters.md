# Suppress three wrong Waypoint name accessor copies

Queue #47, claim F05B8157, census 77a8439ee4. The unchanged consumer
Rva007409A0Assign.cpp references the by-value Waypoint::getName through
ILT 0x0001026C -> 0x000EE6D0. The census contains three wrong copies
(digest 4115ce506ebc) from AIStates.cpp, ScriptActions.cpp and Team.cpp,
and retail copies (d53296c4119a) from TerrainLogic.cpp, GameLogic.cpp and
RailroadGuideAIUpdate.cpp. The selected wrong copy blocks the consumer's
249 historical authored bytes. No consumer respelling is needed.

In each wrong emitter, preload TerrainLogic.h's dependencies, then hide only
its inline getName definition with the existing declaration-plus-unused-method
technique. The original method stays declared with the same by-value return,
const qualification and class. The macro is undefined immediately after the
header. No header, class layout, call ABI, pin, alias or generated file changes.
Final normal COFFs in all three units contain the real accessor only as an
undefined external and contain no zhInlineWaypointGetName symbol. The existing
TerrainLogic object still defines the 32-byte accessor and fresh RetailTruth
independently judges it retail, including the StringBase copy relocation.
callees.py at 0x000EE6D0 confirms the direct 0x00887B60 copy-ctor call.

Normal scoped verification: AIStates 104/104; ScriptActions, Team, unchanged
consumer and TerrainLogic provider together 258/258 plus two data rows. String,
constant, DIR32 and body guards pass; find_declared_unmatched passes on all
three changed sources. Header inclusion naturally renumbers Team funclet labels;
eh_state_pins.py --source Team.cpp --fix repoints the one twin-proven stale
row (uw_00bfc0b8) with byte verification. Other unanchored state records are
not guessed or edited; the normal gate resolves their unchanged native bytes.

Before: census-only consumer preview 0 -> 0 linked bytes, selected wrong
Waypoint::getName. After: current bounded preview UNKNOWN due to the
pre-existing donor submodule/index mismatch and missing current dependency
objects. The three wrong copies are object-proven removed; no linked-byte
increase is claimed without a fresh complete census.

BFME 2 c8b988aae8f06e96b73717239e0bb8f1e7ec23d4 was reviewed via git grep
and Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp. Its corresponding
getName use returns const AsciiString&, unlike this BFME 1 by-value call.
That ABI is not transplanted. The BFME 1 census, its verified provider and
native consumer establish this cleanup independently. No donor adaptation.

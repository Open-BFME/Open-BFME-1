# Use canonical Coord3D in the pathfinder footprint test

Base `8fecf2c0213055c314c1417fb397367a1790bbd7`. Source `game/GameEngine/Source/GameLogic/AI/PathfinderRva003E5E40.cpp`; scope claimed before editing.

Use the registered twelve-byte coordinate in the footprint test. Preserve the original three-component copy in a TU-local inline helper. Keep the visible noinline radius/world-to-cell implementations and their existing bindings: the caller needs their no-escape analysis for its native frame. Existing wrong-provider debt is not repaired or hidden by this storage adoption. No donor layout/address is imported. The fresh59e3f8f825 donor reference and anchor cache were checked earlier today; no named getRadiusAndCenter counterpart is exposed by the narrow current Code search. The target copy/layout and all existing ILT calls are independently established here. The served RefHandle loser has unchanged prerequisites; its lease was released without repeating exhausted variants.

The normal byte gate preserves 1 matched row(s), with existing
extents 460 bytes. Actual COFF comparison
preserves 14 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
?set@Coord3D@@QAEXPBU1@@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/one-each-half-resources-20261101-1317/b1-01-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.

Bounded afbe8bafb6 (2026-10-31 12:37) preview preserves LINKED459->459 bytes. This is an unchanged indexed prediction, not current complete provider selection, a new census or authored-byte gain. The existing helper-provider debt remains documented; no full-image/runtime or memory-performance claim. Build cap14 and memory budget48GiB, within the user-authorized half-machine budget (28 logical processors,95.7GiB total); no local inference was needed.

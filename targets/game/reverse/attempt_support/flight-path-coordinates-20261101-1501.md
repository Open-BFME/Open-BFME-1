# Use canonical Coord2D storage in flight path coordinates

Base `b937bda6e696d46241de8a829225c68cd2b4e352`. Source `game/GameEngine/Source/GameLogic/AI/PathComputeFlightDistToGoal.cpp`; scope claimed before editing.

Use the existing registered coordinate storage. Preserve arithmetic/copy grouping through local helpers where required. Retain the existing caller interfaces, native field offsets and provider bindings. No donor address, new native identity or behavior is inferred. The unchanged RefHandle prerequisite was reviewed and its lease released without repeating exhausted trials.

The normal byte gate preserves 1 matched row(s), with existing
extents 244 bytes. Actual COFF comparison
preserves 3 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
?bfmeNormalizePathVector@Coord2D@@QAEXXZ.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-half-resources-20261101-1501/b1-04-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.

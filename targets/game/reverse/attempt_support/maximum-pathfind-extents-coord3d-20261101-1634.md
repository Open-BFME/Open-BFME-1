# Use canonical Coord3D storage in maximum pathfinding extents

Base `4adbb05f776747e44013a46d4e461f18eb8917bb`. Source `game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicMaximumPathfindExtent.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced.

The normal byte gate preserves 1 matched row(s), with existing
extents 127 bytes. Actual COFF comparison
preserves 4 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 6 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-half-resources-20261101-1634/b1-01-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.

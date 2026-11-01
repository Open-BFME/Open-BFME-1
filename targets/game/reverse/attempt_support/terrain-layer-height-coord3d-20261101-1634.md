# Use canonical Coord3D storage in terrain layer height

Base `f9b07b69b560c3e25e6a4688431affd1fae142b1`. Source `game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicGetLayerHeight.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced.

The normal byte gate preserves 1 matched row(s), with existing
extents 267 bytes. Actual COFF comparison
preserves 2 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 3 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-half-resources-20261101-1634/b1-02-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.

# Use canonical Coord3D storage in radar projection

Base `8f66566ea4e2e485be7a5658afdf98155c6e60e1`. Source `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarViewBoxRva006C0FA0.cpp`; scope claimed before editing.

Adopt the registered storage while preserving the existing target-specific offsets, interfaces, arithmetic, copy grouping and provider bindings. No inferred identity, layout change or new native row is introduced. All 13 non-debug sections remain identical after resolving compiler-local labels by section position. The registered eh_state_pins.py --fix tool uniquely maps the existing state-0 cleanup at 00C49C80 from stale label $L539 to $L540. Its native address, extent, identity and EH state are unchanged; the normal byte gate and a fresh EH-state check pass afterward.

The normal byte gate preserves 2 matched row(s), with existing
extents 19, 577 bytes. Actual COFF comparison
preserves 7 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 13 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/six-each-half-resources-20261101-1634/b1-05-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget48GiB, no Unreal process changed.

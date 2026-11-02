# Adopt canonical Coord3D in Weapon_isClearFiringLineOfSightTerrain_Object

Base `c4a7c4b2c9ebb2425a5498e6a5803f3e9b7258db`. Source `game/GameEngine/Source/GameLogic/Object/Weapon_isClearFiringLineOfSightTerrain_Object.cpp`; scope claimed before editing.

Replace only the exact private three-float POD definition with the existing registered12B struct. Preserve native fields, ABI, external code, data and all non-debug sections.

The normal byte gate preserves 1 matched row(s), with existing
extents 122 bytes. Actual COFF comparison
preserves 2 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 3 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, native-address pin, alias, data row, source path or baseline changes. No compiler flag changes. This BFME 1 accept version validates but does not retire historical queue entries; the queue is not hand-edited.

Final bounded previews are recorded with the batch. No current-selection, census, full-image or runtime claim is made.

Controls: ignored `build/up-to-eighteen-each-20261103-0008/b1-02-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.

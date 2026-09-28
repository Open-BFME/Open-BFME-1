# 0x000C1D10: `MapMetaDataMap` placeholder retired

The bank `targets/game/reverse/attempts/0x000c1d10.cpp` (partial 0.31, 2026-09-21)
named the body `??AMapMetaDataMap@@QAEAAVMapMetaData@@ABVAsciiString@@@Z`.
`MapMetaDataMap` was a TU-local class standing in for
`std::map<AsciiString, MapMetaData>`. It is not an identity:

- `rg MapMetaDataMap inputs/reference` finds nothing. In Zero Hour, `MapUtil.h`
  declares `class MapCache : public std::map<AsciiString, MapMetaData>`, which
  has no `operator[]` of its own.
- The bank's own header and its `re_attempts.log` row both say it means
  `std::map<AsciiString,MapMetaData>::operator[]`. That mangled name is already
  a matched ledger row at 0x0007DF70
  (`AsciiStringMapMetaDataMapOperatorThunk.cpp`). Retail was linked without
  identical-COMDAT folding, so a second body at 0x000C1D10 cannot carry the
  same identity. Its real instantiation or owner is still unproven.

Now that it is byte-exact (250 B), the body lands under the address-derived owner
`??ARva000C1D10MapCache@@QAEAAVMapMetaData@@ABVAsciiString@@@Z` in
`game/GameEngine/Source/GameClient/MapCacheIndex000C1D10.cpp`. The mapped type
`MapMetaData` and the key `AsciiString` are witnessed by the matched MapMetaData
ctor/copy-ctor/dtor and the AsciiString-keyed tree callees. Only the owning
class stays opaque.

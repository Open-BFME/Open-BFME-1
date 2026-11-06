# Partition distance-proc table at VA 0x012DBD60

The decorated identity `?g_rva00EDBD60DistanceProcs@@3PAP6AMPBX0H@ZA`
(C++ `BfmeDistanceProc1050 g_rva00EDBD60DistanceProcs[4]`, i.e. array of
`float (__cdecl *)(const void *, const void *, int)`) owns 16 bytes at VA
0x012DBD60 in retail `.data`: four dwords pointing at `0x009F4070`,
`0x009F4800`, `0x009F40A0`, `0x009F4860` (read via `reloc_ledger.Image.read`).

- Defined in
  `game/Libraries/Source/partitionmanager/BfmeP1050QuadtreeClosest.cpp`,
  the TU whose `PartitionManagerImpl::GetClosestObject` selects
  `g_rva00EDBD60DistanceProcs[distanceType]` with distanceType clamped to
  0..3 and calls it as `(source, candidate, 0)`.
- Pointees and their ledger rows, in order:
  - `?Rva009F4070DistanceSquared@@YAMPBUCoord2DBase@@PAVRva009F4070PositionProvider@@@Z`
    at 0x009F4070 (2D squared distance),
  - `?bfmeSignedEJ@@YAMPBVBfmePosEJ@@PAVBfmeObjEJ@@@Z` at 0x009F4800
    (signed squared planar clearance),
  - `?Rva009F40A0DistanceSquared@@YAMPBUCoord3DBase@@PAVRva009F40A0PositionProvider@@@Z`
    at 0x009F40A0 (3D squared distance),
  - `?distCalcProc_BoundaryAndBoundary_3D@@YAMPBUCoord3D@@PBVObject@@H@Z`
    at 0x009F4860 (boundary-3D distance procedure).
- The name is address-derived; no original EA identifier is established.
  All four symbols are referenced with `__identifier` so the emitted
  relocations resolve to exactly the retail targets
  (AudioManagerRva006B9A80.cpp precedent); each callee reads the prefix
  of the 3-argument contract its own signature declares.

## Extent and all users

`sizeof` 16 bytes at VA 0x012DBD60 as proven by the data gate. The next
retail dwords differ. Sole DIR32 consumer is `GetClosestObject` in
BfmeP1050QuadtreeClosest.cpp.

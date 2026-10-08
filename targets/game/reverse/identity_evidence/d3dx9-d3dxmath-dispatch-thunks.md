# d3dxmath.obj private dispatch thunks: eight generated `?ji_` rows re-pointed to their archive symbol

Library-version audit follow-up, 2026-10-08. Same proof shape as `d3dx-catmull-native-route.md`,
`d3dx-translation-native-route.md`, `d3dx-transformcoordarray-native-route.md` and
`D3DXMatrixScaling_009FB6F4.md`, applied by `add_match.py --replace-archive-import`, whose
`archive_import.verify` re-proves every item below on each gate run.

Each row is a six-byte `FF 25 <cell>` jump through a cell of `?g_D3DXFastTable@@3UD3DXFASTTABLE@@A`, the
private dispatch table of the statically linked Summer 2003 D3DX (`inputs/vendor/d3dx9/d3dx9.lib`, member
`obj\i386\d3dxmath.obj`). The table's home is recorded independently in `dir32_addresses.csv`; home plus
the thunk's own DIR32 addend equals the retail cell; the table's initializer for that field is the
`init_*` body whose archive row is already attached at the address the cell initially holds; the
initializer's REL32/DIR32 operands are bound independently against attached rows. Two opcode bytes plus
four independently bound address bytes, as the existing four routes record.

| rva | old row | archive symbol | cell (VA) | table field | initializer (attached archive row) |
|---|---|---|---|---|---|
| 0x009FA24E | `?ji_009fa24e@@YAXXZ` | `_D3DXVec3BaryCentric@24` | 0x012DBEC4 | +0xCC | `?init_D3DXVec3BaryCentric@@YGPAUD3DXVECTOR3@@PAU1@PBU1@11MM@Z` at 0x009FA208/47B |
| 0x009FA9BE | `?ji_009fa9be@@YAXXZ` | `_D3DXVec4BaryCentric@24` | 0x012DBED0 | +0xD8 | `?init_D3DXVec4BaryCentric@@YGPAUD3DXVECTOR4@@PAU1@PBU1@11MM@Z` at 0x009FA98F/47B |
| 0x009FB802 | `?ji_009fb802@@YAXXZ` | `_D3DXMatrixRotationX@8` | 0x012DBE70 | +0x78 | `?init_D3DXMatrixRotationX@@YGPAUD3DXMATRIX@@PAU1@M@Z` at 0x009FB7E6/28B |
| 0x009FB89E | `?ji_009fb89e@@YAXXZ` | `_D3DXMatrixRotationY@8` | 0x012DBE74 | +0x7C | `?init_D3DXMatrixRotationY@@YGPAUD3DXMATRIX@@PAU1@M@Z` at 0x009FB882/28B |
| 0x009FB9F7 | `?ji_009fb9f7@@YAXXZ` | `_D3DXMatrixRotationAxis@12` | 0x012DBEA0 | +0xA8 | `?init_D3DXMatrixRotationAxis@@YGPAUD3DXMATRIX@@PAU1@PBUD3DXVECTOR3@@M@Z` at 0x009FB9D7/32B |
| 0x009FCB4E | `?ji_009fcb4e@@YAXXZ` | `_D3DXQuaternionRotationYawPitchRoll@16` | 0x012DBE5C | +0x64 | `?init_D3DXQuaternionRotationYawPitchRoll@@YGPAUD3DXQUATERNION@@PAU1@MMM@Z` at 0x009FCB20/46B |
| 0x009FCFC0 | `?ji_009fcfc0@@YAXXZ` | `_D3DXQuaternionSlerp@16` | 0x012DBE84 | +0x8C | `?init_D3DXQuaternionSlerp@@YGPAUD3DXQUATERNION@@PAU1@PBU1@1M@Z` at 0x009FCF9C/36B |
| 0x009FD9A4 | `?ji_009fd9a4@@YAXXZ` | `?D3DXPSGPUpdateSkinnedMesh@@YGXPBUD3DXMATRIX@@0PAE1KKPAPAE2KKPAMH@Z` | 0x012DBF0C | +0x114 | `?init_D3DXPSGPUpdateSkinnedMesh@@YGXPBUD3DXMATRIX@@0PAE1KKPAPAE2KKPAMH@Z` at 0x009FD993/17B |

## Not re-pointed

The other generated six-byte rows in the window stay generated: for 18 of them the table initializer is a
13-byte `init_*` body that the ledger owns from game-compiled source (`GameEngineDevice/Source/W3DDevice/`
`D3DX*Init.cpp`), not from the archive, so the route has no independently attached initializer and
`archive_import` refuses it; three others (0x009F9AF0, 0x009F9B70, 0x009F9B76) jump through CRT import
cells, not the D3DX table. A ninth proven route, `_D3DXMatrixRotationZ@8` at 0x009FB93B, is
left as its generated row because `game/gen_asm/d_009148c0.asm` (a byte-true dump that may not
be hand-edited) calls it by the generated name `?ji_009fb93b@@YAXXZ`; re-point it when that dump
is converted. `quat.cpp` (`Fast_Slerp`) now declares `_D3DXQuaternionSlerp@16` directly, as
`CatmullRom003A14C0.cpp` did for its route.

- 0x009F9AF0 `?ji_009f9af0@@YAXXZ` cell 0x013596E0: no d3dxmath.obj FF25 thunk resolves to this cell
- 0x009F9B70 `?ji_009f9b70@@YAXXZ` cell 0x013596F4: no d3dxmath.obj FF25 thunk resolves to this cell
- 0x009F9B76 `?ji_009f9b76@@YAXXZ` cell 0x01359720: no d3dxmath.obj FF25 thunk resolves to this cell
- 0x009F9BD4 `?ji_009f9bd4@@YAXXZ` cell 0x012DBEDC: initializer `?init_D3DXFloat32To16Array@@YGPAUD3DXFLOAT16@@PAU1@PBMI@Z` is not an attached archive row (owned by D3DXFloat32To16ArrayInit.cpp)
- 0x009F9C76 `?ji_009f9c76@@YAXXZ` cell 0x012DBEE0: initializer `?init_D3DXFloat16To32Array@@YGPAMPAMPBUD3DXFLOAT16@@I@Z` is not an attached archive row (owned by D3DXFloat16To32ArrayInit.cpp)
- 0x009F9F56 `?ji_009f9f56@@YAXXZ` cell 0x012DBDF8: initializer `?init_D3DXVec2Transform@@YGPAUD3DXVECTOR4@@PAU1@PBUD3DXVECTOR2@@PBUD3DXMATRIX@@@Z` is not an attached archive row (owned by D3DXVec2TransformInit.cpp)
- 0x009F9F80 `?ji_009f9f80@@YAXXZ` cell 0x012DBE1C: initializer `?init_D3DXVec2TransformCoord@@YGPAUD3DXVECTOR2@@PAU1@PBU1@PBUD3DXMATRIX@@@Z` is not an attached archive row (owned by D3DXVec2TransformCoordInit.cpp)
- 0x009F9FCC `?ji_009f9fcc@@YAXXZ` cell 0x012DBE0C: initializer `?init_D3DXVec2TransformNormal@@YGPAUD3DXVECTOR2@@PAU1@PBU1@PBUD3DXMATRIX@@@Z` is not an attached archive row (owned by D3DXVec2TransformNormalInit.cpp)
- 0x009FA00B `?ji_009fa00b@@YAXXZ` cell 0x012DBE14: initializer `?init_D3DXVec3Normalize@@YGPAUD3DXVECTOR3@@PAU1@PBU1@@Z` is not an attached archive row (owned by D3DXVec3NormalizeInit.cpp)
- 0x009FA2BE `?ji_009fa2be@@YAXXZ` cell 0x012DBDFC: initializer `?init_D3DXVec3Transform@@YGPAUD3DXVECTOR4@@PAU1@PBUD3DXVECTOR3@@PBUD3DXMATRIX@@@Z` is not an attached archive row (owned by D3DXVec3TransformInit.cpp)
- 0x009FA437 `?ji_009fa437@@YAXXZ` cell 0x012DBE20: initializer `?init_D3DXVec3TransformCoord@@YGPAUD3DXVECTOR3@@PAU1@PBU1@PBUD3DXMATRIX@@@Z` is not an attached archive row (owned by D3DXVec3TransformCoordInit.cpp)
- 0x009FA4A3 `?ji_009fa4a3@@YAXXZ` cell 0x012DBE10: initializer `?init_D3DXVec3TransformNormal@@YGPAUD3DXVECTOR3@@PAU1@PBU1@PBUD3DXMATRIX@@@Z` is not an attached archive row (owned by D3DXVec3TransformNormalInit.cpp)
- 0x009FACAD `?ji_009facad@@YAXXZ` cell 0x012DBE04: initializer `?init_D3DXMatrixMultiply@@YGPAUD3DXMATRIX@@PAU1@PBU1@1@Z` is not an attached archive row (owned by D3DXMatrixMultiplyInit.cpp)
- 0x009FAFBA `?ji_009fafba@@YAXXZ` cell 0x012DBE8C: initializer `?init_D3DXMatrixTranspose@@YGPAUD3DXMATRIX@@PAU1@PBU1@@Z` is not an attached archive row (owned by D3DXMatrixTransposeInit.cpp)
- 0x009FBB0C `?ji_009fbb0c@@YAXXZ` cell 0x012DBE90: initializer `?init_D3DXMatrixRotationQuaternion@@YGPAUD3DXMATRIX@@PAU1@PBUD3DXQUATERNION@@@Z` is not an attached archive row (owned by D3DXMatrixRotationQuaternionInit.cpp)
- 0x009FCC3A `?ji_009fcc3a@@YAXXZ` cell 0x012DBE44: initializer `?init_D3DXQuaternionMultiply@@YGPAUD3DXQUATERNION@@PAU1@PBU1@1@Z` is not an attached archive row (owned by D3DXQuaternionMultiplyInit.cpp)
- 0x009FCDAC `?ji_009fcdac@@YAXXZ` cell 0x012DBEA8: initializer `?init_D3DXQuaternionInverse@@YGPAUD3DXQUATERNION@@PAU1@PBU1@@Z` is not an attached archive row (owned by D3DXQuaternionInverseInit.cpp)
- 0x009FCE70 `?ji_009fce70@@YAXXZ` cell 0x012DBED4: initializer `?init_D3DXQuaternionLn@@YGPAUD3DXQUATERNION@@PAU1@PBU1@@Z` is not an attached archive row (owned by D3DXQuaternionLnInit.cpp)
- 0x009FCEFE `?ji_009fcefe@@YAXXZ` cell 0x012DBED8: initializer `?init_D3DXQuaternionExp@@YGPAUD3DXQUATERNION@@PAU1@PBU1@@Z` is not an attached archive row (owned by D3DXQuaternionExpInit.cpp)
- 0x009FD211 `?ji_009fd211@@YAXXZ` cell 0x012DBE4C: initializer `?init_D3DXPlaneNormalize@@YGPAUD3DXPLANE@@PAU1@PBU1@@Z` is not an attached archive row (owned by D3DXPlaneNormalizeInit.cpp)
- 0x009FD37A `?ji_009fd37a@@YAXXZ` cell 0x012DBE28: initializer `?init_D3DXPlaneFromPointNormal@@YGPAUD3DXPLANE@@PAU1@PBUD3DXVECTOR3@@1@Z` is not an attached archive row (owned by D3DXPlaneFromPointNormalInit.cpp)

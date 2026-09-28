# 0x00100690 (2483 B): BuildAssistant location-clear check, name keeps the address

Banked as `?isLocationClearOfObjects00100690@BuildAssistant@@UAE_NPBUCoord3D@@PBVThingTemplate@@MPAVObject@@IPAVPlayer@@@Z`
(`targets/game/reverse/attempts/0x00100690.cpp`, probe shape 0.994).

## What the retail body proves

- It is virtual. Its only route is ILT 0x00014F1A, and the only pointer to that ILT in the image
  is the vtable slot at VA 0x01086104. The same table holds `buildObjectNow` (0x010860FC, matched
  `Rva00101820BuildObjectNow.cpp`) and `sellObject@BuildAssistant` (0x01086120), so the owner is
  BuildAssistant. Where the table starts has not been established.
- Six stack arguments (`ret 0x18`): worldPos, template, angle, builder object, options, player.
  It returns a byte (`xor al,al` / `mov al,1`), not Zero Hour's `LegalBuildCode`.
- The flow is Zero Hour `BuildAssistant::isLocationClearOfObjects` with BFME edits: an
  inlined `isRemovableForConstruction` (the out-of-line body is matched at 0x000FE5D0 and is
  called in the second loop), `options == 0x20` as NO_ENEMY_OBJECT_OVERLAP, INERT,
  BASE_FOUNDATION (103) and WALK_ON_TOP_OF_WALL (59) skips, IMMOBILE handling,
  `TheTerrainVisual` vtable +0x5C bib calls, then the STRUCTURE-kind range query and the
  factory-exit rectangles. ThingTemplate +0x3B4/+0x3B8 are `m_factoryExitWidth` and
  `m_factoryExtraBibWidth` (name_oracle, confidence 1.00), which is exactly what the ZH exit
  code reads. 30.0f (0x0108615C) is 3 * PATHFIND_CELL_SIZE_F.

## Why the bare Zero Hour name is not used

Counting slots from `buildObjectNow` in Zero Hour's declaration order, 0x01086104 falls where Zero
Hour declares `isLocationLegalToBuild`, not `isLocationClearOfObjects`. The behaviour matches the
second, and the neighbour slot 0x01086108 (0x000FEF90, five arguments) uses the same collide filter.
The vtable order in BFME is therefore not Zero Hour's, and the name keeps its address.

## Callee names used by the bank

- `rva0087E8D0` (pinned `?rva0087E8D0@GeometryInfo@@QBE_NXZ`) is true when the shape list holds
  exactly one GEOMETRY_BOX. It is not `getGeomType`, which is the separate 4-byte body at 0x001F5AD0
  (`?getGeomType@GeometryInfo@@QBE?AW4GeometryType@@XZ`, matched in AIPathfind.cpp). The earlier
  Zero Hour port's `getGeomType() == GEOMETRY_BOX` tests describe a different function.
- `setMajorRadius` / `setMinorRadius`: bodies 0x000FD030 and 0x000FD070 (ILTs 0x000424B5 and
  0x0002CA2F). Each one stores `[esp+4]` into shape 0 at +8 or +0xC when the shape vector is not
  empty, calls `calcBoundingStuff` (0x0087EE60) and returns with `ret 4`. The caller pushes a float
  with `push ecx; fstp [esp]`. That is Zero Hour's inline `setMajorRadius`/`setMinorRadius`
  compiled out of line. Their ledger names (`bfmeGoCJF`/`bfmeGoCJG`, `void*`) cannot take a float,
  so they need pins before this body lands.
- The major and minor getters are 0x0087DC20 / 0x0087DC30 (`fld [ecx+0x24]` / `fld [ecx+0x28]`),
  pinned as `BfmeGeometryInfo::boxMajorRadius`/`boxMinorRadius`.

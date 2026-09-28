# 0x003D6210 is Pathfinder::checkForPossible, not an 8-arg checkForAdjust

ILT 0x00018BE7 (`jmp 0x003D6210`) carried the pin
`?checkForAdjust@Pathfinder@@QAE_NPAVObject@@PBVLocomotorSet@@_NHHHPAUCoord3D@@2@Z`,
which came in with the matched caller `Rva003DEAB0Struct::checkCell`
(0x003DEAB0, PathfindAdjustDeab0.cpp). That caller reproduces retail's bytes
under any pointer-sized spelling of the first two arguments, so its match did
not prove the name. Three independent pieces of evidence name the body
`checkForPossible` and say what the arguments are.

## 1. The body is Zero Hour's checkForPossible

Retail 0x003D6210 (181 bytes, `ret 0x20`, eight stack arguments) follows Zero
Hour's `Pathfinder::checkForPossible` (AIPathfind.cpp) step for step:

- `getCell(layer = arg6, cellX = arg4, cellY = arg5)`; a null cell returns false.
- It rejects a cell whose layer bits (`(packed >> 6) & 0x3f`) differ from arg6, or
  whose type (`packed & 7`) is 4 or 5. This is Zero Hour's `IS_IMPASSABLE`.
- It computes `m_zoneManager.getEffectiveZone(arg1, cell->getZone())` at
  `this+0xC9C` (0x004033E0). When arg8 is set, it then computes
  `bfmeEffectiveTerrainZone(arg1, zone)` (0x00403390). This is Zero Hour's
  `if (startingInObstacle) zone2 = getEffectiveTerrainZone(zone2)`.
- If `arg2 == zone2`, it calls the 5-argument coordinate adjust (ILT
  0x000411D2) with `(cellX, cellY, center = arg3, dest = arg7, layer)` and
  returns true. This is Zero Hour's
  `adjustCoordToCell(cellX, cellY, center, *dest, layer); return true;`.

The first argument is dereferenced as the movement profile: `[arg1+5]` is
read, and arg1 is passed by address to `getEffectiveZone`
(`?getEffectiveZone@PathfindZoneManager@@QBEGABUPathfindMovementProfile@@G@Z`).
It is not an Object. The second argument is compared against a zone. It is not
a LocomotorSet.

## 2. Zero Hour's checkForAdjust is a different retail body

The real BFME `checkForAdjust` is already pinned at 0x003F0F40 as the 13-argument
`?checkForAdjust@Pathfinder@@QAEEPAVObject@@ABVLocomotorSet@@EHHHHEPAUCoord3D@@PBU4@MPAPAVPathfindCell@@H@Z`.
That pin rests on its float `originalZ` argument and on a verified
TightenPathCallbackInfo caller. The Zero Hour checkForAdjust takes an Object,
a LocomotorSet, a radius and a group destination. The 0x003D6210 body reads
none of these.

## 3. The aligned call sites in adjustToPossibleDestination

The matched `Pathfinder::adjustToPossibleDestination` (0x003EAC80, 1108 B,
PathfinderAdjustToPossibleDestination.cpp) calls ILT 0x00018BE7 at the four
places in the spiral where Zero Hour calls
`checkForPossible(isCrusher, zone1, center, locomotorSet, i, j, destinationLayer, dest, isObstacle)`.
Its pushes are, in order: `&profile` (the PathfindMovementProfile it just
built from the template and the locomotor set), `zone1`, `center`, `i`, `j`,
`destinationLayer`, `dest` and `isObstacle`. BFME folded Zero Hour's
isCrusher/locomotorSet pair into the profile pointer. The identity of
adjustToPossibleDestination is proven independently: the matched
OpenContain::exitObjectInAHurry (0x002289F0) and exitObjectViaDoor
(0x002284D0) call it through ILT 0x00011252 at Zero Hour's call site.

## Consequence for Rva003DEAB0Struct (0x003DEAB0)

checkCell passes the record's fields in checkForPossible's parameter order:
`[+0x04]` as the profile pointer, `[+0x08]` as the start zone, byte
`[+0x0C]` as center, `[+0x10]` as the layer, `&[+0x14]` as dest and byte
`[+0x20]` as startingInObstacle. The fields formerly named
`m_object`/`m_locomotorSet`/`m_isHuman` are therefore
`m_profile`/`m_fromZone`/`m_startingInObstacle`. No layout witness covers the
record: `name_oracle --class Rva003DEAB0Struct` has none. The new names are
the checkForPossible parameter names at those argument positions.

## Result

- PathfindAdjustDeab0.cpp calls
  `?checkForPossible@Pathfinder@@QAE_NABUPathfindMovementProfile@@H_NHHW4PathfindLayerEnum@@PAUCoord3D@@1@Z`.
  `./build.sh game/GameEngine/Source/GameLogic/AI/PathfindAdjustDeab0.cpp`
  stays exact (1/1 matched), with and without the old pin present.
- The old 8-argument checkForAdjust pin on 0x00018BE7 is retired.
  `pin_consistency --check` is OK.
- `reloc_names.csv` still lists the old spelling at 0x003D6210 until the next
  full gate regenerates it.

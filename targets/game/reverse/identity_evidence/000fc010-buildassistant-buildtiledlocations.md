# BuildAssistant::buildTiledLocations at 0x000FC010 (identity only)

The 519-byte body at 0x000FC010 is still the generated dump `?d_000fc010@@YAXXZ`.
Earlier sessions guessed the Zero Hour identity from the body, and a 0.51 bank
exists. They blocked because "no matched caller or vtable slot proves class
ownership". The slot is in BuildAssistant's own table. No ledger row changes.

## BuildAssistant's table 0x010860D8

`targets/game/reverse/identity_evidence/000febe0-buildassistant-update.md` shows
that 0x010860D8 is BuildAssistant's table. It is installed by the constructor
0x000FDA80 that GameEngine::init passes to `initSubsystem<BuildAssistant>` with
"TheBuildAssistant". Its slots after the SubsystemInterface block (0-8), with
each body's `ret` immediate from retail:

| slot | body | ret | ledger | Zero Hour counterpart | ZH args |
|---|---|---|---|---|---|
| 9 | 0x00101820 | 0x14 | `buildObjectNow` | buildObjectNow | 5 |
| 10 | 0x000FFE30 | 0x18 | dump | isLocationLegalToBuild (this body calls it, see below) | 6 |
| 11 | 0x00100690 | 0x18 | dump | isLocationClearOfObjects (by order; not proven here) | 6 |
| 12 | 0x000FEF90 | 0x14 | dump | none in ZH (BFME addition; not identified) | - |
| 13 | 0x000FF290 | 0x08 | dump | addBibs (by order and arg count) | 2 |
| **14** | **0x000FC010** | **0x1C** | dump | **buildTiledLocations** | **7** |
| 15 | 0x000FDB30 | 0 (4-byte getter) | `Rva000FDB30Dword::get` | getBuildLocations (inline virtual) | 0 |
| 16 | 0x000FE3C0 | 0x0C | dump | canMakeUnit (see the 000fe3c0 note) | 2 (BFME 3) |
| 17 | 0x000FDBF0 | 0x0C | dump | isPossibleToMakeUnit | 2 (BFME 3) |
| 18 | 0x001003C0 | 0x04 | `BuildAssistant::sellObject` | sellObject | 1 |

Slots 9 and 18 are anchored by matched names. BFME drops ZH's line-build
virtuals (`buildObjectLineNow`, `isLineBuildTemplate`). ILT 0x00015DD9 ->
0x000FC010 is referenced only from slot 14 (0x010860D8 + 0x38). Slots 10-13
are listed for orientation; only slot 10 is pinned down below.

## The body is ZH buildTiledLocations

ZH: `TileBuildInfo *buildTiledLocations( const ThingTemplate *thingBeingTiled,
Real angle, const Coord3D *start, const Coord3D *end, Real tilingSize, Int
maxTiles, Object *builderObject )`, 7 arguments; retail `ret 0x1C`.

- It compares the requested count against `[esi+0x0C]` (ZH `m_buildPositionSize`).
  If more are needed it frees `[esi+0x08]` (`m_buildPositions`) with
  `??_M`/`??_V` and allocates a new Coord3D array with `??_U`/`??_L` (the
  vector new/ctor iterator). It then stores the new size back to `[esi+0x0C]`.
  This is ZH's grow-the-position-buffer step.
- It converts the tile count with `__ftol2` and normalizes the direction
  (`Coord3D::normalize`, 0x000FB930). For each tile it takes the ground height
  from TheTerrainLogic (0x012EF4CC, vtable +0x18). It then calls `this`'s own
  slot 10 (`mov ecx,esi; call [edx+0x28]`) with six arguments:
  `&pos, thing, angle, 0x1F, builderObject, 0`. It stops on a non-zero result.
  That is ZH's `isLocationLegalToBuild(&pos, thingBeingTiled, angle,
  USE_QUICK_PATHFIND|TERRAIN_RESTRICTIONS|CLEAR_PATH|NO_OBJECT_OVERLAP|SHROUD_REVEALED,
  builderObject, NULL) != LBC_OK`, where the five flags are 0x1F.
- It writes the two fields of the static TileBuildInfo at 0x012ED840/0x012ED844
  and returns `mov eax, 0x012ED840`, ZH's `return &tileInfo;` (a function-local static).

## Conclusion

0x000FC010 is `BuildAssistant::buildTiledLocations`, a public virtual. Mangle
it from ZH's signature once the converted body confirms the argument types.
TileBuildInfo is nested in BuildAssistant, so the return type is
`BuildAssistant::TileBuildInfo *`. The ZH copy in
`game/GameEngine/Source/Common/System/BuildAssistant.cpp` is the natural home.

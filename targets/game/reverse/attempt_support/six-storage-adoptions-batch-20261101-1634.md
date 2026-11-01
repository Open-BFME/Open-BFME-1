# Six BFME1 storage adoptions: bounded batch evidence

Initial outgoing base `4adbb05f776747e44013a46d4e461f18eb8917bb`. Six claimed source units adopt the existing
registered Coord3D storage, removing six private copies. Normal gates preserve 7
existing native function/EH rows (4861 bytes of ledger extents) and 33
retained external code bodies and their resolved relocation targets.
No new native/authored-byte or matched-row gain is claimed.

- [Use canonical Coord3D storage in maximum pathfinding extents](maximum-pathfind-extents-coord3d-20261101-1634.md): 1 row(s), 127 bytes, 4 retained code bodies.
- [Use canonical Coord3D storage in terrain layer height](terrain-layer-height-coord3d-20261101-1634.md): 1 row(s), 267 bytes, 2 retained code bodies.
- [Use canonical Coord3D storage in terrain extents](terrain-extents-coord3d-20261101-1634.md): 1 row(s), 171 bytes, 5 retained code bodies.
- [Use canonical Coord3D storage in terrain line of sight](terrain-line-of-sight-coord3d-20261101-1634.md): 1 row(s), 1082 bytes, 3 retained code bodies.
- [Use canonical Coord3D storage in radar projection](radar-projection-coord3d-20261101-1634.md): 2 row(s), 596 bytes, 7 retained code bodies.
- [Use canonical Coord3D storage in view updates](view-updates-coord3d-20261101-1634.md): 1 row(s), 2618 bytes, 12 retained code bodies.

All non-debug object sections preserve bytes and external or resolved local
relocation positions in every source. Native layout, arithmetic and data remain
unchanged; compiler-local labels are compared by their defined section position.
For the radar cleanup, eh_state_pins.py --fix uniquely rebinds existing state 0
at 00C49C80 from $L539 to $L540. No address, extent or identity changes. The
native unwind map, a fresh EH-state check and the normal gate confirm it.
That tool-owned metadata update is the only functions.csv change in this batch.
The accept tool validates these actual removals but leaves historical queue keys
under its control; no historical queue entry was removed by hand.

The native linking-first picker was reviewed at census bb53b24f2b: the served
aiMoveToPosition wrong copy is already documented in prior blocked attempts.
Its AI shim remains at e8b16ffa12b7a109a8c17d3a70b6e9fe99466e53 (Oct24), and
the BFME2 donor remains 59e3f8f825b698775df9e1728265fe962a5d0c02 (fresh check
Nov1 13:06 UTC). The scoped review's synthetic lease was released; unchanged
trials/scans were not repeated, and that review is not a completed task.

The downloaded index is the Nov1 13:17 frozen census at bb53b24f2b. The fetch
completed; a subsequent relative-path display failed, so the downloaded index
was independently loaded and its metadata recorded without fetching it again.

Final bounded preview (a prediction against an index, not a new census):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicMaximumPathfindExtent.cpp: LINKS  LINKED 127 -> 127 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 127)
game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicGetLayerHeight.cpp: LINKS  LINKED 267 -> 267 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 267)
game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicGetExtent.cpp: LINKS  LINKED 171 -> 171 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 171)
game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapIsClearLineOfSight.cpp: LINKS  LINKED 1,080 -> 1,080 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 1,080)
game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarViewBoxRva006C0FA0.cpp: LINKS  LINKED 596 -> 596 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 596)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewUpdateBfme.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 2,616)
  unresolved  ?get@BfmeScriptEngineFreezeExtra@@QBEEXZ
  duplicate   ?isGamePaused@GameLogic@@QAE_NXZ
  comdat      ?isGamePaused@GameLogic@@QAE_NXZ  (retail: not retail's body)
link_check: 5 of 6 link cleanly; LINKED 2,241 -> 2,241 bytes (76.7s)
```

Complete current provider/consumer selection remains unproven where the
available index or receipts are incomplete. No complete-image link, gameplay,
RAM/leak/crash/FPS gain is claimed. No shared header, compiler option, native
address pin, alias, new identity or baseline was changed.

Controls: ignored build/six-each-half-resources-20261101-1634 and the matching
diagnostic package. Two independent repository processes use BUILD_POOL=7 each
(aggregate ceiling14 of28 logical CPUs); memory budget about48GiB of95.7GiB.
No local model was needed. Claims are released after ordinary publication.

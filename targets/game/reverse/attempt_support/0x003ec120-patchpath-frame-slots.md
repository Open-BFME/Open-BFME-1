# 0x003EC120 Pathfinder::patchPath (1553 B): frame-slot residue

Session a1/538, 2026-11-02. Bank: `targets/game/reverse/attempts/0x003ec120.cpp`
(re_log partial). Compiler: repo VC7.1, `/DNDEBUG /MD /EHsc`, STLport, declarations
copied from the matched sibling `game/GameEngine/Source/GameLogic/Pathfinder/PathfinderFindSafePathBfme.cpp`
(findSafePath, slot 4).

## Identity and boundary (BFME 1 evidence)

- The ledger row `?d_003ec141` (gen dump `d_003e5ca0.asm`, 1520 B) starts 0x21 bytes
  inside the body. The real entry is 0x003EC120 (EH prologue `mov eax,fs:[0]`), the body
  ends with `jmp` back into the shared epilogue at +0x60C and INT3 at +0x611: 1553 B.
  Earlier verdict on 0x003EC141 already recorded this (no-boundary).
- Pathfinder PathfindServicesInterface vtable 0x010EE5C8 slot 3 -> ILT 0x000374F2 -> 0x003EC120.
  Slot 4 is the matched findSafePath; ZH slot 3 is `patchPath(const Object*, const LocomotorSet&,
  Path*, Bool)`; `ret 0x10` = four stack args. Body is ZH `Pathfinder::patchPath`
  (AIPathfind.cpp) with BFME changes: no `allyFixedCount/enemyFixed` break, info gets
  `acceptableSurfaces = 3` and `ai ? ai->getIgnoredObstacleID() : 0`, no allocateInfo failure tests.
- Callee names (all ledger/pin backed): getRadiusAndCenter 0x3DEE30, vector clear 0x3D7C90,
  bfmeFillAL 0x403140, worldToCell 0x3D7EC0, Object::getLayer ILT 0x3A391, getCell 0x3D4E80,
  allocateCellInfos/acquire, startPathfind 0x3F6940, rva003D6400, bfmeStepE05B0 0x3E05B0
  (checkForMovement, TCheckMovementInfo* as ICoord2D*), getIgnoredObstacleID ILT 0x1A36B,
  adjustCoordToCell 0x3D6040, bfmeDetach 0x3F69E0 (inlined open-list pop = Gen_003D6490
  ::bfmeTakeFirstLive), ??0Path ILT 0x335B4 (new 0x24), prependNode inlined (PathNode ctor
  from PathNodeInsertion.cpp, ZH store order: m_isOptimized after the tail test),
  prependCells 0x3DD930, Path::optimize 0x401660, releaseInfo 0x3F6F10, cleanOpen 0x3D5FC0,
  putOnClosedList 0x3F6C30, checkChangeLayers 0x3DAE40, examineNeighboringCells 0x3E6EE0.

## State of the bank

1553 B = retail, shape 0.979, 669 non-reloc diffs. Every diff except ~10 instructions is a
stack offset: our frame is `sub esp,0x80`, retail `0x78`.

Code levers that got here (each measured):
- Coord3D with a member-wise `operator=` (as PathNodeInsertion.cpp): the two position copies
  CSE into one load triple like retail (POD block copy materialises `lea` + reloads). 0.878->0.913.
- `Coord3D x; x = *p;` (assignment, not copy-init) for currentPosition/startPos/goalPos.
- Reusing ONE Coord3D for startPos and goalPos and ONE for currentPosition and the loop's
  cellCenter, and one function-scope `ICoord2D cell` for both cell lookups, one cellCoord for
  the loop and the goal index: frame 0x8c -> 0x80, size 1599 -> 1551.
- `Bool overflow = worldToCell(...); if (overflow)` gives retail's `cmp al,bl`.

## The remaining 8 frame bytes

Retail slots (offset from frame base, EHRec at -12): tag byte temp of the inlined vector clear
-129, centerInCell -128, cellCoord -124 (also goal cell index and the while loop's matchNode
spill), cellCount -116, cell temp -112 (clip lookup temp, goalDeltaSqr, ground lookup temp and
candidateGoal), radius -104, isHuman -100 (also the new-Path temp), startCellNdx -96,
goalPos -88, currentPosition -76, info -64.

The bank has the upper part exactly (startCellNdx..info) but cell/cellCoord are function
scope, so the spills goalDeltaSqr/candidateGoal/matchNode cannot be packed into them (8 B).
Making the cell temps block-scoped (or inline-function locals) packs the spills exactly like
retail, but then one 8-byte temp (the ground lookup temp, or goalCellNdx without the info
ctor) always lands alone just below goalPos and startCellNdx sinks: frame 0x84/0x88.

VC7.1 /FAsc experiments (build-only harness, 60+ cases) in EH functions:
- Sibling block locals overlay; any `new T` with ctor (EH state) changes the rules.
- With EH, the last-declared address-taken block local before the EH loop does not overlay
  (it sits in the upper group); a later address-taken block local or an inlined temp after the
  EH loop restores the overlay in small cases, but NOT in this body (a diagnostic trailing
  local packed with cellCount and the ground temp stayed alone).
- Removing `info` (or its ctor) frees the ground temp but then goalCellNdx becomes the lone one.
- An inline helper creating the TCheckMovementInfo, a by-value cellCenter helper, out-of-class
  auto-inlined getClippedCell/getGroundCell (getGroundCell then stays out of line), info in a
  nested block, if/else around the goal section, goalDeltaSqr in its own block: no change.

Small structural residue besides the frame (10 instructions): the goalPos initial copy loads
y before storing x in retail, the in-loop goalPos copy is loads-then-stores in retail, and the
ground lookup's join (`xor eax,eax` + single store) differs.

Next step: find the source shape that keeps the cell temps block-scoped AND lets the ground
temp overlay the clip temp (8 B frame), then the copies. Scripts: build/a1_538/combo2.py,
build/a1_538/slots.sh, build/a1_538/ov/gen.py (not tracked).

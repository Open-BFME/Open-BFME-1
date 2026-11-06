# 0x003E6B80: why the ground-path builder keeps an address name (2026-11-06)

Body: the 623-byte Pathfinder method at retail 0x003E6B80 (ILT 0x00020DA1). Its
shape is Zero Hour's `Pathfinder::buildGroundPath` (prependCells,
optimizeGroundPath, corner smoothing through snapLine). It is now matched in
`game/GameEngine/Source/GameLogic/AI/PathfinderBuildGroundPath.cpp`.

## Name check against retail's incremental-link thunk table

`python3 tools/ilt_oracle.py check NAME 0x003E6B80` places the target at ILT slot
26092, whose bucket window is 16755-16765. Every Zero Hour-style decoration falls
outside it:

| decoration | verdict |
|---|---|
| `?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z` (protected, the bank's spelling) | CONTRADICTED, p_false 7.18e-04 |
| `?buildGroundPath@Pathfinder@@QAE...` (public) | CONTRADICTED |
| `?buildGroundPath@Pathfinder@@AAE...` (private) | CONTRADICTED |
| `int` instead of `bool` center, `long` diameter, reference or non-const coordinates, const cell | CONTRADICTED (18 variants) |

The contradiction is class-wide. snapLine (0x003E6AF0), worldToCell (0x003D7EC0),
isGroundPathPassable (0x003EAC00), lineClear (0x003EE970) and 117 Pathfinder
rows in `targets/game/reverse/ilt_contradicted_baseline.txt` are also outside
their windows. So BFME 1's decorated class or signature spelling is not Zero
Hour's, and no evidence yet says what it is. The ZH method name is not proven
for this address.

## Name used

`?rva003E6B80@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z` is the
existing symbols.csv pin at ILT 0x00020DA1. The matched findGroundPath caller
(0x003F2160 +0x7DC) calls that ILT with the Pathfinder receiver in ECX. It is
address-derived, so the ILT guard does not test it, and the ZH role stays in
comments. The receiver/ABI evidence is in
`targets/game/reverse/identity_evidence/0x003e6b80-retry-layout-and-abi.md`.

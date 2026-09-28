# 0x003EC8C0 Pathfinder::findSafePath: helper names

The removed bank `targets/game/reverse/attempts/0x003ec8c0.cpp` was the Zero Hour
findSafePath text. Its own banner says it was "not a production conversion". It
never compiled against the BFME callees, so its helper names were never checked
against retail. The landed body `game/GameEngine/Source/GameLogic/AI/PathfinderFindSafePathBfme.cpp`
is byte-exact over all 750 bytes and calls the BFME helpers by the address-derived
names already pinned for the matched checkPathCost at 0x003E11E0
(`PathfinderStepD4F90.cpp`). The retail call sites refute the bank's names:

| bank name | retail call site in 0x003EC8C0 | landed name |
| --- | --- | --- |
| `checkChangeLayers(cell)` | +0x264 calls ILT 0x0001264D -> 0x003DAE40 with two arguments (cell, obj); Zero Hour's checkChangeLayers takes one | `rva003DAE40` (existing pin) |
| `cleanOpenAndClosedLists()` | +0x2A9 and +0x2DD call ILT 0x00032B5F -> 0x003D5FC0, whose matched body is the cell-info pool reset | `rva003D5FC0` (existing pin) |
| `examineNeighboringCells(...)` | +0x286 calls ILT 0x000127A6 -> 0x003E6EE0, a gen-dump body with no matched source or proven name | `rva003E6EE0` (address-derived) |
| `m_openList` | no open-list pointer exists. Retail pushes through 0x003D6400 and pops through 0x003D6490, which are the 512-bucket array at this+0x34 with cursor this+0x834 | `rva003D6400` / `rva003D6490` (existing pins) |
| `m_zoneManager` | false pairing: the member the bank called on is this+0xC9C (0x00403140). The landed `m_bfme2470C` is a separate `vector<Coord3D>` at this+0x2470C that retail clears through the 0x003D7C90 `__copy` | `m_bfme2470C` (address token) |
| `putOnClosedList(list)` | +0x25B calls ILT 0x00005E48 -> 0x003F6C30 on the cell with &this+0x838 | `rva003F6C30` (existing pin) |
| `releaseInfo()` | +0x2D6 calls ILT 0x0004B3B7 -> 0x003F6F10 | `rva003F6F10` (existing pin) |

The Zero Hour names stay plausible semantic twins, but no matched caller, vtable
slot or literal proves them for these BFME bodies. So the landed source keeps the
address tokens the ledger already uses.

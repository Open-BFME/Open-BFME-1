# 0x003F6EA0 is PathfindCell::~PathfindCell, not MixFileCreator::FileInfoStruct

Retail body: RVA 0x003F6EA0, 17 bytes (`ret` at +0x10, int3 padding from
+0x11 up to `PathfindCell::reset` at 0x003F6EC0). It loads the first member,
tests it, and when non-null passes the pathfind cell-info free-list head
VA 0x012F1094 (`g_bfmePathfindFreeList` / `g_rva012F1094`) to the release
helper behind ILT 0x000203D8, the same call `PathfindCell::reset` makes.

## BFME 1 target evidence

- Matched `PathfindLayer::bfmeReset` (0x003FBE20, 135 B) frees
  `blockOfMapCells` with `delete[]`: it pushes ILT VA 0x00436AB1 (ILT
  0x00036AB1 jumps to 0x003F6EA0), the count at `[eax-4]` and element size
  0x10, then calls the eh vector destructor iterator `??_M@YGXPAXIHP6EX0@Z@Z`
  and `??_V@YAXPAX@Z`. The element destructor of a PathfindCell array is
  `PathfindCell::~PathfindCell`. `PathfindLayerAllocateCells.cpp` and
  `PathfinderNewMap.cpp` use the same ILT the same way.
- `dir32_addresses.csv` already records `??1PathfindCell@@QAE@XZ` at
  VA 0x00436AB1.
- `python3 tools/ilt_oracle.py check '??1PathfindCell@@QAE@XZ' 0x003F6EA0`:
  CONFIRMED (p_false 6.52e-04, exact). The same check on the old name
  `??1FileInfoStruct@MixFileCreator@@QAE@XZ`: CONTRADICTED (outside every
  window of the target's slots).
- The released pool is the PathfindCellInfo free list, not any MixFile
  structure; retail has no identical-COMDAT folding, so the body has one
  identity.

## The vector deleting destructor at 0x003D5710

The 84-byte body at 0x003D5710 (ILT 0x00045E49), previously claimed as
`??_EFileInfoStruct@MixFileCreator@@QAEPAXI@Z` in `mixfile.cpp`, pushes the
same destructor ILT VA 0x00436AB1 with stride 0x10 to the eh vector
destructor iterator and calls 0x003F6EA0 directly in its scalar branch.
`ilt_oracle.py check '??_EPathfindCell@@QAEPAXI@Z' 0x003D5710`: CONFIRMED
(p_false 1.57e-03, exact); the old name: CONTRADICTED. Zero Hour's
`MixFileCreator::FileInfoStruct` holds a `StringClass Filename` at +0x0C, so
its destructor would destroy +0x0C, not release the word at +0x00 into the
pathfind free list. The body is re-homed in
`game/GameEngine/Source/GameLogic/AI/PathfindCellVectorDtor.cpp` through a
`delete[]` emission anchor marked absent-from-retail.

## Donor and reference evidence (leads, not BFME 1 proof)

- Zero Hour `GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp`
  `PathfindCell::~PathfindCell` releases `m_info` when set.
- BFME 2 `f6d845ecd4` `reverse/functions.csv` corrected its own twin
  (`??1PathfindCell@@QAE@XZ`, 17 B, `Code/GameEngine/Source/GameLogic/Pathfinder/PathfindCellDtor.cpp`)
  from a WorldBuilder `PathfindCell::Info::Free` assertion, and its
  `??_EPathfindCell@@QAEPAXI@Z` through a `delete[]` anchor in
  `PathfindCellVectorDtor.cpp`. The anchor technique is carried from that
  donor; no donor header, layout or address was imported.

## Change

The body moves next to `PathfindCell::reset` in
`game/GameEngine/Source/GameLogic/AI/PathfindCell_reset.cpp`, reusing that
unit's verified release-helper call; the misnamed
`MixFileCreator_FileInfoStruct_dtor.cpp` (its only row) is retired.

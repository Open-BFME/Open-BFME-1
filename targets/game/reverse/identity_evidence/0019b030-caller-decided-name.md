# 0x0019B030: the matched caller decides the name

The 641-byte body at `0x0019B030` lands as `?rva0019B030@BfmeTableERJ@@QAEXXZ`
(`BfmeTableERJ::rva0019B030`). Banked attempts had called it
`Rva0019B030Owner::loadBuildLists`, a name no landed source or pin ever used.

- **The matched caller links to it by that exact name.**
  `GameLogic::init` (game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp,
  matched) declares `void BfmeTableERJ::rva0019B030(void); // 0x0019B030` and
  calls `g_bfmeTableERJ->rva0019B030()` at `+0x300` through ILT `0x00040381`.
  The existing `symbols.csv` pin `?rva0019B030@BfmeTableERJ@@QAEXXZ,0x0019B030`
  records that call. Retail was linked without identical-COMDAT folding, so
  the body has one identity. That identity has to be the name its matched
  caller resolves, not a second one.
- **Nothing proves `loadBuildLists`.** No caller, vtable slot or literal names
  the method. The literal `BuildLists` is the chunk label passed to the parser
  registration, not a method name. The strings `Bases\Camps\Camps.map` and
  `Bases\Others\Others.map` are file paths. `Rva0019B030Owner` was a scratch
  class invented for the stash.
- **What the evidence does show.** `g_bfmeTableERJ` is pinned at VA
  `0x012EF428`, which `dir32_addresses.csv` gives as `TheSidesList`, so the
  owner object is the SidesList singleton. The source comment records this.
  Renaming the caller's class to SidesList is a separate change to the matched
  GameLogicInit.cpp.

# Bank 0x0090EB00: `ChunkLoadClass -> Gen_00920a60` is not a rename

The banked Load_Texture reconstruction at 0x0090EB00 still takes
`ChunkLoadClass &cload`; the type now comes from the real WW3D header
`chunkio.h` instead of a bank-local copy of the class, so the local
`class ChunkLoadClass` declaration disappeared from the file.

`Gen_00920a60` is a new, unrelated TU-local view of the callee at 0x00920A60,
whose ledger row is `?m@Gen_00920a60@@QAEXH@Z` (game/gen_small/fun_005.cpp).
The shroud-filter object is modelled as deriving from it so the call binds to
that ledger name. No identity changed. The function keeps its pinned name
`Load_Texture` (symbols.csv pin at 0x0090EB00).

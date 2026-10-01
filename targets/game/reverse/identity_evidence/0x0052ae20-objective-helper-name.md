# Name for 0x0052AE20

The row for 0x0052AE20 in `functions.csv`, the function ledger, still uses `?d_0052ae20@@YAXXZ` and records Ghidra's generic `FUN_0092ae20`. The pin table in `symbols.csv` and the retail export list in `exports.csv` do not name this body `bfmeFindNthPred`. The matched callback at 0x0052AE80 registers for `Objective%dStatus` selectors and calls the helper through an `int __cdecl(int)` pointer. That callback proves the helper's ABI, but it does not give the helper a C++ name.

The old draft chose `bfmeFindNthPred` from the body's behavior. The helper returns the index of the nth eligible objective. That behavior does not prove EA used this C++ name. The replacement uses `Rva0052AE20` until a retail symbol, matched named caller, or other identity evidence names the helper.

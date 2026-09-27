# The caller identifies 0x003C2100 as a LivingWorldLogic callback

The `functions.csv` row for `j_00035ff3` targets VA `0x007C2100`. The row for the dump at RVA `0x003C2100` names the same body `FUN_007c2100`.

`LivingWorldLogicRva003C3850.cpp` declares `RecordAction` as a `LivingWorldLogic` method that accepts `LivingWorldRegion*`. The matched body at `0x003C3850` stores `j_00035ff3` in that callback and invokes it on `owner` with `value`.

The old bank called this callback `process` on `Rva003C2100Owner` and gave it `Rva003C2100Record*`. The matched caller contradicts those receiver and argument types. The caller does not establish a semantic method name, so the bank uses `Rva003C2100` with the proven owner and argument types.

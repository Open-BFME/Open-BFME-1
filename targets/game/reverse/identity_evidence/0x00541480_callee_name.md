# 0x00541480 bank: callee at 0x00637D10

The banked attempt for the 11.7 KB function at 0x00541480 called its callee at
0x00637D10 `getSlot`. The ledger has no identity for that address: it is the
generated ILT thunk `?j_00637d10@@YAXXZ` (target thunk_FUN_00a1e8b0) with a
`?b_00637d10` gen-thunk pin. `getSlot` was invented for the bank; the
gpt-6-astra gap seat renamed it to the address-derived `Rva00637D10`.
No established identity is lost.

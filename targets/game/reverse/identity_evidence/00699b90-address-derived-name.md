# Identity at RVA 0x00699B90

The prior bank called the body `bfmeRefreshAAK`. That name appears only in the bank and its attempt history. Before conversion, `functions.csv` used the address-only dump name, and `symbols.csv` listed only the generated thunk name `?b_00699b90@@YAXXZ` at this address. No semantic pin names a function at RVA `0x00699B90`.

The call index names `Rva006B47F0Owner::refresh006B47F0` and `Rva006B47F0Owner::refresh006B48B0` as the two callers. Neither names the callee. The body calls the independently matched `Rva00699180Owner::refreshPair` method while it loops over three `0x1C4` blocks. Those facts establish the body’s call contract and behavior, but they do not establish the `AAK` identity.

The replacement name `?Rva00699B90@@YAXXZ` keeps the retail address and avoids asserting an unsupported class or method name.

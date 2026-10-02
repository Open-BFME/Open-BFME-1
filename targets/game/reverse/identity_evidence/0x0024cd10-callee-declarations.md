# HordeTransportContain update callee declarations

The 120-byte caller at RVA 0x0024CD10 calls the ILT at 0x0000F510,
which jumps to 0x0024CAE0, and the ILT at 0x0003CBD7, which jumps to
0x0024C940. `tools/callees.py 0x0024CD10 120` confirms these routes.
Both calls pass the primary object pointer (`this - 0x10`).

The former TU used `HordeTransportContainBase::first` and `::second`.
Its own comment explicitly said neither callee had a known identity.
The class was a declaration-only call view; no body or base-class layout
established a separate type with that name.

The function ledger already owns these bodies as
`Rva0024CAE0Owner::maintainNestedRiders` (436 bytes) and
`Rva0024C940Owner::processNestedRiders` (322 bytes), respectively, in
`Rva0024CAE0MaintainNestedRiders.cpp` and
`Rva0024C940ProcessNestedRiders.cpp` under GameLogic/Object/Contain.
Both have nonvirtual void no-argument thiscall ABI. Use those existing
address-derived declarations rather than declare two unavailable members
of a speculative common base. This changes neither provider identity nor
ledger ownership, and does not infer a type from adjacent vtable entries.

The tail ILT 0x000133EF reaches the existing TransportContain update at
0x0022D660. Its ledger symbol has the virtual UpdateSleepTime return ABI;
explicit qualification retains the direct base call. The corrected caller
passes the exact 120-byte scoped build and link_check reports 3 unresolved
names before, zero blockers and 120 linked bytes after.

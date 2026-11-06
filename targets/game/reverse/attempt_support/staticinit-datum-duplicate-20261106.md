# StaticInitializers datum duplicate cannot be deleted in place (2026-11-06)

Link queue rank 45: `?TheBfmeObject_00C6FF10@@3VGen_00C6FF10Target@@A`
duplicates=1, wrong_selected. Two strong definers: the retail-proven 12 B
cell in BfmeObject00C6FF10Data.cpp (matched row) and a 1-byte
`Rva00C6B3D0Init` object in Rva00C6B390StaticInitializers.cpp:150 that wins
the link by order (22815 < 22945).

## Why deletion fails

Each `extern "C" { InitStruct __identifier("datum"); }` datum definition
emits a `$E` dynamic-initializer stub row (`?Rva00C6BxxxInit@@YAXXZ`, 14 in
this TU). Removing the 00C6FF10 datum lines removes its `$E` stub and
cascades: 10/15 rows fail (shifted callee thunks per stub, `_$E37` gone,
`??1Rva00C6B4E0Init` teardown call unresolvable). Pristine TU is 15/15, so
the layout is load-bearing. Reverted; nothing pushed.

## Options for the next agent (none quick)

- Re-home all affected `$E`/teardown rows against the new numbering
  (eh_state_pins --fix + add_match --replace-existing per row) in the same
  commit as the deletion. Heavy but mechanical.
- Grow the Rva00C6B3D0Init storage to the proven 12 B in place. Shifts every
  later `.data` object, cascading DIR32 bases. Worse.
- Reorder link inputs so Data.cpp wins. Explicitly forbidden for COMDAT
  selection; these are strong duplicates and row order is still load-bearing
  elsewhere. Do not.
- The Owner TU's tree view (12 B at 0x012F10DC) and the Data row agree with
  each other; only the link winner is wrong. Any fix must keep all 15 TU
  rows byte-identical AND resolve the duplicate, verified by the full link,
  not just the scoped gate (the scoped gate passed the broken intermediate
  state for other rows).

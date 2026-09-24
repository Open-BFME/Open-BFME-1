# The false Drawable route through 0x0001C8D2

## Confirmed retail evidence

The matched 15-byte row at `0x00527200` is compiled from the Zero Hour
`Drawable::clearModelConditionState` inline wrapper. Its retail bytes push the
incoming argument and `-1`, call ILT `0x0001C8D2`, and return. Those bytes and
the call relocation prove the forwarding *shape*, not the Drawable identity.
The five-byte ILT jumps to `0x00526660`. Its prior C++ source names a Drawable
method and jumps to a locally invented shim pinned to `0x00526660`; the pin
therefore cannot independently corroborate that name.

The `0x00526660` body saves its original `this` in ESI, then at offset `+0x7F`
passes the same receiver in ECX to ILT `0x0003AA67`. Retail decodes that ILT
to the separately matched `MpGameSetup::bfmeGetStartPositionInfo` at
`0x00525F80`. The body also uses `this+4`, `+8`, `+0xC`, the eight-slot arrays
at `+0x88`, `+0xA8`, and `+0xC8`, and the mode flag at `+0x124`. These match
the independently reconstructed multiplayer setup view in
`MpGameSetup.cpp`, not Drawable's witnessed layout. The exact dynamic owner
could still be a derived screen class, so the replacement should retain an
address token in its class and method names. Retail's `ret 8` starts at
`0x00526868` and ends at `0x0052686B`: the complete extent is 523 bytes,
while the Ghidra inventory and derived
`reloc_names.csv` entry report 518. No body at `0x00526660` is claimed as
matched by this correction.

The current relocation harvester sees the falsely named 15-byte wrapper as a
byte-true caller, follows its call through the ILT, and publishes a Drawable
candidate for `0x00526660` with `identity=real`. This is a provenance error
propagating from the two matched labels; hiding only the candidate would
leave both labels and the bad pin in place.

## Proposed correction and pre-implementation review gate

Replace the 5-byte claim with an address-derived
`Rva0001C8D2Thunk::forward(int,int)` thiscall thunk, and the 15-byte claim
with `Rva00527200Owner::rva00527200(int)`. Each name retains its own address
token, and the wrapper preserves the same receiver and argument stack across
the ILT. A scratch C++
translation unit probes at 5/5 and 15/15 bytes, each with one aligned
relocation and no non-relocation differences. The 5-byte matched row resolves
the wrapper's call without a second alias pin; pin only the opaque forwarding
shim directly to the observed body at `0x00526660`. Use two
`add_match.py --correct-identity` transactions with this evidence, remove the
old Drawable and shim pins, and regenerate the derived naming file.

This preserves the two verified byte ranges without claiming the 523-byte
body or asserting a semantic class name. A plain `?j_0001c8d2@@YAXXZ` thunk
would require a separately pinned typed method alias at the stub for the
15-byte thiscall wrapper. Pin consistency cannot validate a `route=` for that
alias without a same-name matched body at `0x00526660`, and omitting the route
would hide the fact that the name resolves through a stub. The typed but
address-derived five-byte claim avoids that conflict. Merely deleting the
derived queue row would leave the false matched claims; naming the replacement
`MpGameSetup` would assert more than the same-receiver call proves; deleting
the matched rows would discard valid C++ byte coverage. The expected benefit
is corrected identity provenance and removal of a misleading finish
candidate, not new game-code bytes or measured throughput.

Before implementation, independently challenge whether any other matched
caller uses the old Drawable pin, whether an address-derived thunk/wrapper
can pass strict relocation checks without a hidden fallback, and whether
removing the old pin breaks other scoped matches. Record the decision here
before editing the claims.

Pre-change focused test run: 119 passed, one unrelated failure in
`test_published_rows_are_unambiguous_anonymous_and_sized_by_the_inventory`
because the checked-in derived entry for `0x0014E2B0` says 571 bytes while the
Ghidra inventory says 574. This is a pre-existing derived-file freshness
failure, not evidence about this identity route; it must not be hidden by
weakening the assertion.

## Review decision

The independent review found the Drawable identity refuted, but returned
**revise** for the initial plain-`?j_` design: its typed alias pin could not
carry a valid `route=` without a same-name matched body at `0x00526660`.
The reviewed design above uses a matched address-derived thiscall thunk and
one direct opaque body pin, retaining strict relocation verification. The
independent reviewer further suggested putting the thunk's own RVA in its
name rather than the forwarded body's RVA; the revised scratch source still
probes 5/5 and 15/15 exactly modulo aligned relocations.
review also found that the old Drawable pin appears only in a cached
`Object.obj` among the available cached objects, and the sole cached matched
caller is the 15-byte wrapper. The object cache is incomplete, so a full
strict build after pin removal remains mandatory. If another matched caller
fails, repair its source and independent identity evidence or defer removal;
never restore the false semantic pin just to make the gate green. Proceed with
the revised transaction and tests; no production claim changed at this
checkpoint.

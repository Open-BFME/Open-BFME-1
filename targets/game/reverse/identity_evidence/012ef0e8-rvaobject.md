# Opaque object datum at VA 0x012EF0E8

The decorated identity `?RvaObject012EF0E8@@3UGen00026F35@@A` (C
`Gen00026F35 RvaObject012EF0E8`) owns storage at VA 0x012EF0E8 in retail
`.data`. Retail holds zeros there (loader semantics per
`reloc_ledger.Image.read`), and `Gen00026F35` is an empty struct
(`struct Gen00026F35 { void handle(); };`, no members, implicitly trivial
default constructor), so a plain definition emits zero-filled storage with no
dynamic initializer. The exact size is the struct's `sizeof` under the build
flags as proven by the data gate.

## Retail facts and contract

`RvaObject012EF0E8` is an opaque object cookie used only by address. Its sole
retail code references come from `Rva00C6FCC0Cleanup.cpp`:

- `void rva00C6FD10() { RvaObject012EF0E8.handle(); }` — calls the method on
  the object (the call itself is a code reference, unaffected by this row).

## Extent and all users

`sizeof(::RvaObject012EF0E8)` bytes at VA 0x012EF0E8 as proven by the data
gate. Sole consumer is `rva00C6FD10` in
`game/GameEngine/Source/Common/Rva00C6FCC0Cleanup.cpp` (kept as `extern`
there). Home is the data-only TU
`game/GameEngine/Source/Common/StaticInit/Rva012EF0E8Global.cpp`: the
consumer TU carries an unrelated pre-existing unowned reference
(?RvaObject012ED5E0 at 0x012ED5E0, no row, no exemption), so it cannot go
green in the same scoped build; that redness predates this row.
Sibling AsciiString `RvaObject*` datums in the consumer TU are separate,
harder rows (non-trivial constructors need init-function rows).

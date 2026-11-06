# Empty AsciiString at VA 0x012ED828

The decorated identity `?RvaObject012ED828@@3VAsciiString@@A` (C++
`AsciiString RvaObject012ED828`) owns 4 bytes at VA 0x012ED828 in retail
`.data`: one null narrow-buffer pointer (read via `reloc_ledger.Image.read`;
initial bytes `00 00 00 00`). Dynamic construction is separate from the
stored initial image: the AsciiString default constructor writes exactly
one zero word, as in the landed `theDrawString`/`theInputString` precedent.

- Defined in `game/GameEngine/Source/Common/StaticInit/TheDrawStringGlobal.cpp`
  alongside the other orphan AsciiString globals (`theDrawString`,
  `theInputString`); used only by address by the `rva00C6FCE0`-family
  startup callbacks in `Rva00C6FCC0Cleanup.cpp` (the
  `reinterpret_cast<Gen0000D828 *>(&RvaObject012ED828)->handle()` route to
  the AsciiString release path 0x000D828->0x0005EE90->0x00887940).
- The name is address-derived; no original EA identifier is established.
  The adjacent `RvaObject012ED82C` (VA 0x012ED82C) is a separate 4-byte
  datum recorded in its own row.

## Extent and all users

`sizeof` 4 bytes at VA 0x012ED828 as proven by the data gate. Sole DIR32
consumer is `rva00C6FCE0` in Rva00C6FCC0Cleanup.cpp (defined here, used
there; the reference resolves through this data row).

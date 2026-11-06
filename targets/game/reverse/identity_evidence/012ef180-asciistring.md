# Empty AsciiString at VA 0x012EF180

The decorated identity `?RvaObject012EF180@@3VAsciiString@@A` (C++
`AsciiString RvaObject012EF180`) owns 4 bytes at VA 0x012EF180 in retail
`.data`: one null narrow-buffer pointer (read via `reloc_ledger.Image.read`;
initial bytes `00 00 00 00`). Dynamic construction is separate from the
stored initial image: the AsciiString default constructor writes exactly
one zero word, as in the landed `theDrawString`/`theInputString` precedent.

- Defined in `game/GameEngine/Source/Common/StaticInit/TheDrawStringGlobal.cpp`
  alongside the other orphan AsciiString globals; used only by address by
  the `rva00C6FD20` startup callback in `Rva00C6FCC0Cleanup.cpp`.
- The name is address-derived; no original EA identifier is established.

## Extent and all users

`sizeof` 4 bytes at VA 0x012EF180 as proven by the data gate. Sole DIR32
consumer is `rva00C6FD20` in Rva00C6FCC0Cleanup.cpp (defined here, used
there; the reference resolves through this data row).

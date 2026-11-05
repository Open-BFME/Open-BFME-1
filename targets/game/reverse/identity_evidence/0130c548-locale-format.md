# Locale date-format static buffer at VA 0x0130C548

The decorated identity `_locale_format_0084ED20` (C `char
locale_format_0084ED20[]`) owns storage at VA 0x0130C548 in retail `.data`.
Retail holds zeros there (loader semantics per `reloc_ledger.Image.read`).
The TU declares it as an incomplete `char` array and both reads (by address)
and writes it at runtime:

- `out = locale_format_0084ED20; ... *out++ = ...; *out = 0; return
  locale_format_0084ED20;` — builds a date-format string into the static
  buffer on each call (up to the local 80-byte working area).

The load-time bytes are zero; runtime fills are not part of the byte gate.
The true static bound is unevidenced, so the definition claims the minimal
honest extent of one BSS byte. Neighboring zeros stay unclaimed.

## Extent and all users

`sizeof` 1 byte at VA 0x0130C548 as proven by the data gate. Sole consumer is
`Rva0084ED20Tail` in `game/stlport/LocaleCodePageQueries.c`, defined in place
there. Follows the sibling `locale_format_0084EF30` row at 0x0130C128.

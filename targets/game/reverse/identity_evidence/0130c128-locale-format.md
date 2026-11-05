# Locale time-format static buffer at VA 0x0130C128

The decorated identity `_locale_format_0084EF30` (C `char
locale_format_0084EF30[]`) owns storage at VA 0x0130C128 in retail `.data`.
Retail holds zeros there (loader semantics per `reloc_ledger.Image.read`).
The TU declares it as an incomplete `char` array and both reads (by address)
and writes it at runtime:

- `char *format = locale_format_0084EF30; strcpy(format, "%H");
  strcat(format, separator); ...` — builds a time-format string into the
  static buffer on each call.

The load-time bytes are zero; runtime fills are not part of the byte gate.
The true static bound is unevidenced (writes suggest a multi-byte buffer, but
no extent is proven), so the definition claims the minimal honest extent of
one BSS byte. Neighboring zeros stay unclaimed.

## Extent and all users

`sizeof` 1 byte at VA 0x0130C128 as proven by the data gate. Sole consumer is
`Rva0084EF30` in `game/stlport/LocaleCodePageQueries.c`, defined in place
there.

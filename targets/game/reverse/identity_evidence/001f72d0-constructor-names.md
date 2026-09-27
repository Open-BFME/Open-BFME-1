# ClearanceTesting constructor naming

The old 001F72D0 source is a naked body made only of `__asm _emit` byte directives. `_emit` is assembler syntax, not a class member, function identity, or descriptive source name. The native replacement introduces two float pairs, with offset-derived members `m_f210` and `m_f214`. There is no established semantic field name in the deleted body to preserve.

The name-regression token matcher pairs `_emit` with `m_f210` across this complete rewrite. This exact-content correction acknowledges that parser false positive; it does not permit any actual descriptive name to be removed. The replacement constructor byte-verifies 149 bytes at RVA 001F72D0. Its matched caller at 00117310 allocates 0x220 bytes; the member at +0x1A8 is the GeometryInfo constructed via ILT 37B6E to 00100580.

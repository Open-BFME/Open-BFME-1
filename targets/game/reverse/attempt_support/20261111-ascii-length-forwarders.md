# AsciiString length forwarding emission

BFME 1 base e3fda96dc8. Seven queue consumers use the canonical ascii_string.h, whose getLength wrapper returns StringBase<char>::getLength directly. Qualify that exact existing base operation at each call. All nine matched parent/EH rows pass the normal scoped gate with unchanged retail relocations. COFF inspection confirms the AsciiString wrapper symbol disappears from all seven objects; no new names, imports, layouts, pins or ledger changes.

Reviewed BFME 2 76f0baefa6f285d54bc1ca922397674312a5913f connection-auth-string-cleanup-20261028-codex.md and related getLength evidence. It confirms canonical-header helpers can add emitters, but supplies no replacement provider or target identity. This repair follows BFME 1's existing explicit forwarding implementation and verified callers. Census-only linking is diagnostic; current provider closure and linked gains remain unknown.

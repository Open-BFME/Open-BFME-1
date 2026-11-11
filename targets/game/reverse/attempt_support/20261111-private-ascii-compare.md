# Private AsciiString comparison emission

The queue compare family includes Glo012F1024Entry_select.cpp, whose private comparison is fully inlined. Imported forceinline on its existing declaration removes the competing comparator section without adding a reference or import. Normal build passes the complete parent and its retail relocations. The body, data layout, names and pins are unchanged.

BFME 2 reference 76f0baefa6f285d54bc1ca922397674312a5913f: reviewed connection-auth-string-cleanup-20261028-codex.md and kindof-emission-link-20261015/readme.md. The latter supplies the emission technique, not BFME 1 layout or identity. Existing BFME 1 compare-family attempts rule out broad canonical-header body changes: they break inline callers. This change is limited to the private fully inlined comparator. Other family consumers remain unresolved. No current linked-byte gain claimed.

# TerrainScorchFXNuggetFieldParse at VA 0x010F336C

The datum is a const FieldParse array with 3 entries, including one all-zero terminator, occupying 48 bytes in retail .rdata. The chosen spelling is `?TerrainScorchFXNuggetFieldParse@@3QBUFieldParse@@B`. Each nonterminal entry has a narrow NUL-terminated keyword pointer at +0, a four-argument cdecl INI parser pointer at +4, null userData at +8, and a byte offset at +12. The competing WideFieldParse class spelling describes a local layout proxy, rather than the type accepted by retail MultiIniFieldParse::add. The chosen DIR32 spelling already exists; it is retained beside the old row.

The matched nugget parse callback and the matched two-table builder both pass this exact address to retail MultiIniFieldParse::add at VA 0x00C50920, followed by FXNuggetFieldParse at VA 0x010F2480. The callback uses the resulting descriptor in INI::initFromINIMulti. There is no receiver for the datum. Its callback contract is (INI*, instance, field-storage, const userData), and offsets apply to the allocated nugget. These are descriptor reads, not writes to the table. The PE section is read-only.

The retail keyword in the FXList registration table and the existing matched callback identity establish the nugget role. Zero Hour FXList.cpp independently defines ViewShakeFXNugget, TerrainScorchFXNugget, and ParticleSystemFXNugget parsers using the same FieldParse element layout. BFME extends the base and table contents; the initializers below use retail offsets, not reference offsets.

No data row overlaps the extent and no other DIR32 address starts strictly inside it. The first all-zero 16-byte entry proves the descriptor terminator; bytes beyond that terminator are not claimed.

Raw evidence is in `build/rlink/identity-types-1791185133/retail-all.txt`, `tables-description.txt`, `tables.json`, `table-compile.txt`, `declaration-counts.csv`, and `land-tables.txt`. The registration keywords and their complete ILT routes are independently dumped in `final-probes.txt`. The `.bin` file named by this VA preserves retail bytes to the next named boundary. String initializer contents are compared independently before their compiler-generated literal spellings are added to DIR32. Every parser thunk is recorded as its five E9 bytes and final target. The table data gate checks every scalar byte and relocation.

| Keyword | Retail keyword VA | Parser VA | Final body VA | Offset |
|---|---|---|---|---|
| Type | 0x01080DDC | 0x0042B1D4 | 0x00827670 | 0xB4 |
| Radius | 0x0108EE10 | 0x00C52B20 | 0x00C52B20 | 0xB8 |

A different keyword, callback destination, field offset, nonzero userData or terminal entry would refute the initializer. A callback registered under another nugget keyword, or an appender that consumed a different element layout, would refute the identity. No function identity is corrected by this change.

The competing spellings below are counted from original explicit game-source declarations, including macro expansions. Included vendor declarations are separate; the enum classic-table spelling is proven by the vendor header and canonical wide-scan use regardless of its direct game-source count. Raw declaration lines and source paths are retained in `build/rlink/identity-types-1791185133/declaration-counts.txt`; the authoritative count rows are in `declaration-counts.csv`.

| Spelling | Original game CPP declarations (files) |
|---|---|
| `?TerrainScorchFXNuggetFieldParse@@3QBUFieldParse@@B` | 1 |
| `?WideTblA00427CB0@@3QBVWideFieldParse@@B` | 1 |

# Region sentinel at VA 0x012F7078 remains unresolved

Retail conclusively establishes one sixteen-byte region object in `.data`, with four float elements and sixteen zero initial bytes. It has no initial relocation. No other datum or distinct DIR32 name lies inside that sixteen-byte extent; the next named object begins at 0x012F708C. The raw extent, bytes and overlap check are in `build/rlink/identity-15/retail-probe.log`. The supplementary inventory checks all four element addresses and the data sections in `retail-extra-complete.log`.

The dynamic initializer is at RVA 0x00C6C350 (VA 0x0106C350). `region-initializer-corrected.log` shows ECX set to 0x012F7078 and two corner references supplied on the stack. The corner words are two copies of `0xFF7FFFFF` and two copies of `0x7F7FFFFF`, representing negative and positive maximum finite float. The five-byte E9 thunk at VA 0x004277EB contains `e9 70 42 5f 00` and ends at VA 0x00A1BA60. That body's raw instructions in `retail-extra-complete.log` copy four float words from the supplied corners to receiver offsets 0, 4, 8 and 12. The initializer also registers an exit helper with atexit. The earlier `region-initializer.log` is a deliberately retained wrong-RVA probe; it does not supply evidence for this object.

The `LivingWorldSound` constructor at RVA 0x0061BF00 copies all four words to its default zoom region. The sound parser at RVA 0x0061C410 passes this object's address to the region-equality operation. Its ILT at VA 0x00407C66 contains `e9 85 3e 61 00` and ends at VA 0x00A1BAF0; the raw body compares the four float elements. These accesses confirm the rectangle layout and the default sentinel role. The direct base and interior address inventories identify only the constructor, parser and dynamic initializer as direct users.

The competing spellings are `Rva012F7078Region` as `Region2D`, `TheInvalidRegion` as const `Region2DBase`, and `g_bfmeBoxYP` as `BfmeBoxYP`. Their explicit game declaration counts and lines are in `spelling-census.log`. The initializer's current source actually defines its old free name as a `Region2D`, so the listed `BfmeBoxYP` DIR32 type is stale. No Zero Hour `TheInvalidRegion` declaration, independent global pin or EA string identifies this BFME-only sentinel. The region's confirmed role does not establish that proposed global name or const qualification. A byte match of its users would not settle that spelling.

This address's sources and ledger rows are left unchanged. An independently named EA declaration, a debug or reference table naming this global, or an existing witnessed symbol establishing the exact global name and type would settle it. No compiler float constant is defined as a datum, no replacement address placeholder is introduced, and no guessed name is landed.

## Spelling census before the correction

Counts below come from the original source snapshots. Template-static counts include the shared game header and owning explicit instantiation, plus files with explicit extern-template declarations. Ordinary pointer counts require the decorated pointer type. For the STLport member, zero means no explicit game declaration; the vendor header and the three known retail numeric-output users are recorded in the raw census. Stale decorated types whose current source already differs are identified in the notes.

| VA | Existing decorated spelling | Game files | Notes |
|---|---|---:|---|
| 0x012F7078 | `?Rva012F7078Region@@3URegion2D@@A` | 1 |  |
| 0x012F7078 | `?TheInvalidRegion@@3URegion2DBase@@B` | 2 |  |
| 0x012F7078 | `?g_bfmeBoxYP@@3VBfmeBoxYP@@A` | 1 | Its sole source currently defines Region2D, while this stale DIR32 spelling says BfmeBoxYP. |

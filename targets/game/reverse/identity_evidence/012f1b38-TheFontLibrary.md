# TheFontLibrary datum at VA 0x012F1B38

Corrected ownership and declaration spelling: `?TheFontLibrary@@3PAVFontLibrary@@A` is one FontLibrary pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour GUI/GameFont.cpp:35 defines FontLibrary *TheFontLibrary = NULL. Retail font consumers load this word as their receiver for font lookup, default settings and substitution; the FontDefaultSettings parser and font creation consumers agree with the reference. GameClient construction stores the created font library in the slot and destruction resets it. The existing GameFont.cpp definition is the authoritative owner. FontLibraryBFMERetail is retained only as a local method ABI view reached by a cast, not as the type or identity of the global.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x002F3BD0, 0x0040C310, 0x0040CE30, 0x00418880, 0x0041FDF0, 0x0042F5A0, 0x00431380, 0x004349D0, 0x0043A8A0, 0x0043DF00, 0x0043E700, 0x00441D30, 0x004469F0, 0x0044AD40, 0x00471900, 0x00472000, 0x00477320, 0x004779C0, 0x0047A190, 0x00485B50, 0x0048C480, 0x00491A40, 0x00510DC0, 0x00588FA0, 0x00695B80, 0x006ED5B0, 0x006EE0C0, 0x006EE3F0, 0x006EE800, 0x006F0300, 0x006F2CC0, 0x006F5580, 0x006F5890, 0x006F5A90, 0x00787710. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f1b38-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/GUI/GameFont.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?Rva00510DC0FontLibraryGlobal@@3PAVFontLibraryBFMERetail@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?Rva012F1B38@@3PAXA`: 0 game source files with an explicit declaration of that name and type before correction.
- `?TheFontLibrary@@3PAUFontLibraryBFMERetail@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?TheFontLibrary@@3PAVFontLibrary@@A`: 21 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

An allocation, vtable or parser proving a different subsystem at this pointer would refute the identity.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f1b38-retail.log`, `012f1b38-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

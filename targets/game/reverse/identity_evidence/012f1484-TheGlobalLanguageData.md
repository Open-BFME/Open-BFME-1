# TheGlobalLanguageData datum at VA 0x012F1484

Corrected ownership and declaration spelling: `?TheGlobalLanguageData@@3PAVGlobalLanguage@@A` is one GlobalLanguage pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour definition is GlobalLanguage *TheGlobalLanguageData in GameClient/GlobalLanguage.cpp:63. Retail repeatedly loads the word as a receiver, including the font-size adjustment and language font descriptors. The retail engine contains the exact singleton string TheGlobalLanguageData. The override-aware accessors at RVA 0x0043FC50 and its siblings read language descriptors through this pointer; their different local pointee names do not denote independent globals.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x0006BD3C, 0x00079060, 0x000B33F0, 0x002F3BD0, 0x0040C310, 0x0040CE30, 0x00418880, 0x0041FDF0, 0x0042F5A0, 0x00438F70, 0x0043A8A0, 0x0043DF00, 0x0043E700, 0x0043FC50, 0x0043FD60, 0x0043FE70, 0x00440B40, 0x00441D30, 0x00442460, 0x004469F0, 0x0044AD40, 0x0047EDE0, 0x00480090, 0x0048C480, 0x00547730, 0x00572A60, 0x00583680, 0x005A6090, 0x00695B80, 0x006ED5B0, 0x006EE800, 0x006F0300, 0x006F2CC0, 0x006F5510, 0x006F5A90, 0x0078CE50. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f1484-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/GlobalLanguage.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?Rva012F1484@@3PAXA`: 1 game source files with an explicit declaration of that name and type before correction.
- `?TheGlobalLanguageData@@3PAVGlobalLanguage@@A`: 16 game source files with an explicit declaration of that name and type before correction.
- `?TheGlobalLanguageData@@3PAVGlobalLanguageData@@A`: 3 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWR@@3PAUBFMEGlobalLanguage@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWR@@3PAUBfmeGlobalWR@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWR@@3PAVBfmeGlobalWR@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWR@@3PAVGlobalLanguageAI@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWS@@3PAVBfmeGlobalWS@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWT@@3PAVBfmeGlobalWT@@A`: 0 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobalWU@@3PAVBfmeGlobalWU@@A`: 0 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

A receiver allocation or vtable proving a different subsystem, or an access requiring an object at the slot rather than the pointer held there, would refute the identity.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f1484-retail.log`, `012f1484-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

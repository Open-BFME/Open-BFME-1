# TheWaterTransparency datum at VA 0x012F18F0

Corrected ownership and declaration spelling: `?TheWaterTransparency@@3V?$OVERRIDE@VWaterTransparencySetting@@@@A` is one OVERRIDE<WaterTransparencySetting> object containing one pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour Water.cpp:38 defines OVERRIDE<WaterTransparencySetting> TheWaterTransparency = NULL; Water.h declares that exact type. Retail INI::parseWaterTransparencyDefinition at RVA 0x000C3A00 reads and writes the word, creates a WaterTransparencySetting on the first definition, and follows Overridable links at pointee +4 for override use. The independent water texture initializer at RVA 0x001901F0 reads the same word and walks the same chain. The reference OVERRIDE<T> stores only const T *m_overridable; no additional wrapper word is present. The new definition is placed in the existing INIWater.cpp, the main parser owner.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x000C3A00, 0x001901F0, 0x00190700, 0x0038F4B0, 0x006CFAE0, 0x007A5D10. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f18f0-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/Common/INI/INIWater.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?TheWaterTransparency@@3V?$OVERRIDE@VWaterTransparencySetting@@@@A`: 2 game source files with an explicit declaration of that name and type before correction.
- `?g_bfmeGlobal012F18F0@@3PAVBfmeGlobal012F18F0@@A`: 1 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

An access to a second wrapper word, or a parser table or constructor proving a different pointee, would refute this correction.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f18f0-retail.log`, `012f18f0-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

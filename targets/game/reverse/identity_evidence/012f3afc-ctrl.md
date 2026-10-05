# ctrl datum at VA 0x012F3AFC

Corrected ownership and declaration spelling: `?ctrl@@3VUnicodeString@@A` is one UnicodeString object holding one wide buffer pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour KeyboardOptionsMenu.cpp:113 defines UnicodeString ctrl. The retail keyboard initializer fetches KEYBOARD:Ctrl+ into this object. The key handlers use it as the Control modifier label, and their string operations access a 16-bit character buffer. Its cleanup at RVA 0x00C70140 loads this address into ECX and jumps through ILT RVA 0x0003B304 to the UnicodeString release route. The existing definition in KeyboardOptionsMenu.cpp owns the datum.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x004C9490, 0x004C9820, 0x004C9C60, 0x004CA140, 0x004CAA90, 0x00C6BA90, 0x00C70140. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f3afc-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/KeyboardOptionsMenu.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?TheBfmeObject_00C70140@@3VGen_00C70140Target@@A`: 1 game source files with an explicit declaration of that name and type before correction.
- `?ctrl@@3VUnicodeString@@A`: 3 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

A different localization key assigned to this object or narrow-character operations on its buffer would refute the identity.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f3afc-retail.log`, `012f3afc-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

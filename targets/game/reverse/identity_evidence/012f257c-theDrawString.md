# theDrawString datum at VA 0x012F257C

Corrected ownership and declaration spelling: `?theDrawString@@3VAsciiString@@A` is one AsciiString object holding one narrow buffer pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour GameWindowManagerScript.cpp:123 defines theDrawString and parseDrawCallback assigns the parsed callback token before name-to-key lookup. Retail parseDrawCallback at RVA 0x00485930 performs that operation at this address. Retail window creation copies the same narrow string into the draw callback descriptor, and parseWindow releases it through StringBase<char>::releaseBuffer at RVA 0x00887940. The native initializer at RVA 0x00C6B960 calls ILT RVA 0x00017BD9, which jumps to RVA 0x00062030; that constructor writes exactly one zero word. Its cleanup goes through 0x0000D828 -> 0x0005EE90 -> 0x00887940. The existing native definition in Common/StaticInit/TheDrawStringGlobal.cpp is kept; three separate static parser copies become declarations of that one definition.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x00485930, 0x00486A60, 0x004874A0, 0x00487F80, 0x00C6B960, 0x00C700E0. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f257c-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/Common/StaticInit/TheDrawStringGlobal.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?TheBfmeObject_00C700E0@@3VGen_00C700E0Target@@A`: 1 game source files with an explicit declaration of that name and type before correction.
- `?theDrawString@@3VAsciiString@@A`: 5 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

A wide-character operation on this buffer, an initializer storing a second word, or a parser receiver at a different address would refute the correction.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f257c-retail.log`, `012f257c-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

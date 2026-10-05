# TheSupplyAndTechImageLocations datum at VA 0x012F15B0

Corrected ownership and declaration spelling: `?TheSupplyAndTechImageLocations@@3VTechAndSupplyImages@@A` is one TechAndSupplyImages object containing two list<ICoord2D> objects. The datum is 8 bytes in retail `.data`; its initial bytes are `00 00 00 00 00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour SkirmishGameOptionsMenu.cpp defines TechAndSupplyImages TheSupplyAndTechImageLocations at line 599, with tech and supply position lists. Retail positionAdditionalImages at RVA 0x00452AD0 clears and fills both lists; MapSelectorTooltip at RVA 0x004F1760 iterates the supply list and the Cash and TOOLTIP:SupplyDock branch. The retail constructor at RVA 0x00452150 constructs one list at receiver +0 and another at +4. Each stored element is an ICoord2D pair of 32-bit coordinates, accessed at node +8 and +12. The existing definition in SkirmishGameOptionsMenu.cpp uses the native BFME allocator and proves sizeof(object)=8.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x00452AD0, 0x004F1760, 0x00C6B7D0, 0x00C70030. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f15b0-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 8-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?TheBfmeObject_00C70030@@3VGen_00C70030Target@@A`: 1 game source files with an explicit declaration of that name and type before correction.
- `?TheSupplyAndTechImageLocations@@3VTechAndSupplyImages@@A`: 3 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

A third member, a list receiver offset other than 0 and 4, or element accesses inconsistent with two 32-bit coordinates would refute the chosen layout.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f15b0-retail.log`, `012f15b0-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

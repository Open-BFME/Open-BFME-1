# ControlBar-m_containData datum at VA 0x012F3448

Corrected ownership and declaration spelling: `?m_containData@ControlBar@@1PAUContainEntry@1@A` is 20 ControlBar::ContainEntry records, each {GameWindow *control; ObjectID objectID;}. The datum is 160 bytes in retail `.data`; its initial bytes are `00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour ControlBar.h:932-939 declares protected nested struct ContainEntry and protected static m_containData. The reference ControlBarCommand.cpp defines the array. Retail resetContainData at RVA 0x004A3B00 advances the entries by 8 bytes and bounds the loop at 20 entries. The population callbacks at RVA 0x004A3C70 and 0x004AEC90 store the GameWindow pointer at entry +0 and the object ID at +4. findContainedObject at RVA 0x004AED60 compares 20 control pointers and looks up the corresponding ID. BFME has 20 records, rather than the reference build's 18. Both local class declarations are retyped to the proven nested protected type, and the existing definition remains in ControlBarContextUI.cpp. The new DIR32 spelling encodes both protected access and the nested element type.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x004A3B00, 0x004A3C70, 0x004AEC90, 0x004AED60. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f3448-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 160-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarContextUI.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?m_containData@ControlBar@@1PAUContainEntry@@A`: 2 game source files with an explicit declaration of that name and type before correction.
- `?m_containData@ControlBar@@2PAUContainEntry@@A`: 0 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

A loop extending beyond entry 19, a record stride other than 8, or a different meaning for either record word would refute the extent or element contract.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f3448-retail.log`, `012f3448-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

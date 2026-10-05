# Rva00EF3884BriefingList datum at VA 0x012F3884

Corrected ownership and declaration spelling: `?Rva00EF3884BriefingList@@3V?$list@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@A` is one STLport list<UnicodeString> object holding one sentinel pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour Diplomacy.cpp:161-166 defines the briefing list and returns its address from GetBriefingTextList. BFME changes the element type from AsciiString to UnicodeString: retail RVA 0x004C4630, the independently matched Unicode briefing updater, inserts and compares wide strings. The list accessor at RVA 0x004C3340 returns exactly this address. Retail initializer RVA 0x00C6BA40 calls ILT 0x00008DCD, which jumps to the list constructor at 0x004C4500. That body writes one receiver word and allocates a 12-byte sentinel node. List nodes have next and previous pointers at +0/+4 and one 4-byte UnicodeString object at +8. Cleanup follows 0x000398FB -> 0x0009F770 and frees 12-byte nodes after releasing the wide string elements. The compiler proves sizeof(list)=4. The element count is dynamic. The existing role-describing address-qualified spelling is retained and its native definition is placed beside the main Unicode updater.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x004C3340, 0x004C3DE0, 0x004C4630, 0x00C6BA40, 0x00C70120. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f3884-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/GUI/GUICallbacks/UpdateDiplomacyBriefingUnicodeText.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?Rva00EF3884BriefingList@@3V?$list@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@A`: 2 game source files with an explicit declaration of that name and type before correction.
- `?TheBfmeObject_00C70120@@3VGen_00C70120Target@@A`: 1 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

Narrow-character string handling in the inserted elements, another persistent receiver word, or a node payload other than a single UnicodeString would refute the chosen element type or extent.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f3884-retail.log`, `012f3884-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

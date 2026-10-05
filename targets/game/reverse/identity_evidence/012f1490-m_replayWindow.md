# m_replayWindow datum at VA 0x012F1490

Corrected ownership and declaration spelling: `?m_replayWindow@@3PAVGameWindow@@A` is one GameWindow pointer. The datum is 4 bytes in retail `.data`; its initial bytes are `00 00 00 00`. It has no initial non-null pointer and no data relocation. The PE base relocation directory is empty. Dynamic construction is separate from the stored initial image.

The Zero Hour definition is GameWindow *m_replayWindow in GameClient/InGameUI.cpp:108. Retail RVA 0x0043E3E0 obtains the window from the script creation slot and stores EAX into this word. The script literal is ReplayControl.wnd. Retail show, hide and toggle bodies load this word into ECX and call GameWindow::winHide through ILT RVA 0x00027F2A, which jumps to RVA 0x00478390. The InGameUI constructor clears the same word.

The receiver contract is the object or pointer described above. Calls and stores witnessed in the raw retail disassembly use that contract; this correction changes declarations, not the instructions or function identities. Every directly witnessed retail user in the scoped scan is listed by RVA: 0x0043A7F0, 0x0043A820, 0x0043A840, 0x0043E3E0, 0x00440B40, 0x0044B800. The complete bodies and their memory accesses are in `build/rlink/identity15-1791196707/012f1490-exact-users.log`; the original address probe records each followed five-byte E9 chain.

`known-extents.log` checks the entire 4-byte interval against `data_rows.csv` and every DIR32 address. There is no other data row or interior DIR32 name in the interval. The native compiler sizeof probe and `add_data_match.py` verify the declared extent and initial bytes. The definition is owned by `game/GameEngine/Source/GameClient/InGameUI.cpp`. Existing DIR32 spellings are retained; a new spelling is appended only when the chosen spelling is absent. No symbol pin is removed or rewritten.

## Competing declarations

- `?g_bfmeReplayControlAR@@3PAXA`: 1 game source files with an explicit declaration of that name and type before correction.
- `?m_replayWindow@@3PAVGameWindow@@A`: 2 game source files with an explicit declaration of that name and type before correction.

The declaration inventory, including paths and source lines, is in `build/rlink/identity15-1791196707/declaration-inventory.json`. Header-inherited declarations are not included in these explicit source counts. Counts do not establish identity.

## Refutation

A different script associated with this store, or a route from the show/hide calls to a receiver other than GameWindow, would refute the identity.

## Raw evidence

Retail probes: `build/rlink/identity15-1791196707/012f1490-retail.log`, `012f1490-exact-users.log`, `known-extents.log`, `layout-disassembly.log` and `retail-strings.log`. Reference search: `reference-uses.log`. Data and source gate receipts are recorded in `build/worker-final.md`.

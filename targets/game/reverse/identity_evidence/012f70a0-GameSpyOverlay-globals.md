# GameSpyOverlay globals at VA 0x012F70A0 through 0x012F70B3

Retail proves `okFunc` at VA 0x012F70A8, `cancelFunc` at VA 0x012F70AC and `reOpenPlayerInfoFlag` at VA 0x012F70B0. VA 0x012F70A4 is a message-box activity byte whose EA spelling remains unproven. Its corrected source name is `g_Va012F70A4`. It performs the lifetime-tracking role of Zero Hour's `messageBoxWindow`, but it is not a window pointer. The four overlay globals have one external definition in `game/GameEngine/Source/GameNetwork/GameSpyOverlay.cpp`; the split dialog translation unit and the existing callback, cleanup and setter bodies declare those definitions externally.

## Retail range and initial state

The baseline image has SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`, image base 0x00400000 and an empty PE base-relocation directory. All addresses below belong to the zero-filled virtual tail of `.data`. The initial bytes are established by the PE section mapping through `reloc_ledger.Image.read`, rather than by bytes stored in the executable file. `build/rlink/retail-probe-full.log` records the image hash, section boundaries, initial bytes, every absolute-address occurrence, containing function rows and full retail disassemblies.

| Start VA | Proven accessed size | Initial bytes | Identity and reference correspondence |
|---|---:|---|---|
| 0x012F70A0 | 4 | 00 00 00 00 | `TheDownloadManager`, an adjacent global outside GameSpyOverlay. The existing DIR32 spelling and matched DownloadMenu allocation, destruction and receiver accesses identify it. The reference defines it in `GameNetwork/DownloadManager.cpp:34`. It is unchanged. |
| 0x012F70A4 | 1 | 00 | `g_Va012F70A4`, mutable message-box activity state. It corresponds in role to `messageBoxWindow` at reference GameSpyOverlay.cpp:47, whose pointer type and exact spelling cannot be assigned to BFME's byte. |
| 0x012F70A5 | 3 | 00 00 00 | Unidentified intervening bytes. No direct absolute address occurrence targets them. No datum is asserted. |
| 0x012F70A8 | 4 | 00 00 00 00 | `okFunc`, matching reference GameSpyOverlay.cpp:48. |
| 0x012F70AC | 4 | 00 00 00 00 | `cancelFunc`, matching reference GameSpyOverlay.cpp:49. |
| 0x012F70B0 | 1 | 00 | `reOpenPlayerInfoFlag`, matching reference GameSpyOverlay.cpp:50 and its setter/checker at lines 321 through 331. |
| 0x012F70B1 | 3 | 00 00 00 | Unidentified intervening bytes before the separately recorded `overlayLayouts` at VA 0x012F70B4. No datum is asserted. |

The existing DIR32 names have no starts inside any of the four new datum ranges. Initially no data row overlaps the investigated range. These facts are recorded by the complete range-filtered ledger output in `retail-probe-full.log`. `add-dir32.log` checks each final interval against all DIR32 names and data rows again. Each final interval contains only its own data row. Mutable stores and indirect calls establish that these are program state and callback pointers, rather than compiler constants.

## Competing spellings and declarations

`build/rlink/audit-final.log` derives the following counts from game declarations before and after the correction. `declarations-before.log` and `declarations-after-raw.log` retain the raw searches. Counts refer to declaring source files, not uses, parameter names or comments. A higher declaration count does not outweigh the proven reference correspondence. The COFF audit additionally verifies one external definition for each of the four new spellings and undefined external references in the other affected objects.

| VA | Spelling | Declaring game files before | Declaring game files after |
|---|---|---:|---:|
| 0x012F70A0 | TheDownloadManager | 1 | 1 |
| 0x012F70A4 | g_rva006279F0CallbackActive | 2 | 0 |
| 0x012F70A4 | g_rva00627A50Flag | 1 | 0 |
| 0x012F70A4 | Rva00627A20Enabled, symbols.csv spelling | 0 | 0 |
| 0x012F70A4 | g_Va012F70A4 | 0 | 5 |
| 0x012F70A8 | g_rva006279F0Callback | 1 | 0 |
| 0x012F70A8 | g_rva00627A50A | 1 | 0 |
| 0x012F70A8 | okFunc | 2 | 4 |
| 0x012F70AC | g_rva00627A20Callback | 1 | 0 |
| 0x012F70AC | g_rva00627A50B | 1 | 0 |
| 0x012F70AC | Rva00627A20Callback, symbols.csv spelling | 0 | 0 |
| 0x012F70AC | cancelFunc | 2 | 4 |
| 0x012F70B0 | g_Va012F70B0 | 1 | 0 |

The old `reOpenPlayerInfoFlag` name had three declaring files: two private bool definitions in the overlay TUs and the unrelated external unsigned-char declaration in CancelPatchCheckCallback_BFME.cpp. The private main-TU symbol reached both VA 0x012F70A4 and VA 0x012F70B0; the split-TU symbol reached only VA 0x012F70A4. After correction, the name still has three declaring files: its sole external bool definition in GameSpyOverlay.cpp, its external bool declaration in SmallLeafBodies.cpp and the unchanged unrelated unsigned-char declaration. Only the first two share the new `?reOpenPlayerInfoFlag@@3_NC` COFF spelling at VA 0x012F70B0. Existing old spellings remain in the address ledgers as required, although the affected source declarations have been removed.

## Readers, writers and callback contracts

The retail scan finds 49 little-endian absolute-address occurrences in the entire image for every possible target address in the questioned interval. All are in `.text`, and disassembly accounts for all of them as memory operands in the eleven function extents below. This is a census of direct absolute references, not a claim about arbitrary computed pointers. Operand sites, instruction offsets and widths are recorded individually in `retail-probe-full.log` and indexed in `access-index.log`.

`retail-probe-asserted.log` repeats the scan and asserts that every occurrence belongs to a decoded absolute memory operand and that every observed width agrees with the proposed scalar or pointer size. `download-coff-final.log` records the adjacent TheDownloadManager DIR32 operands from its three readers/writers after compiling their unchanged sources; `build-download-evidence.log` passes all 28 rows in those two sources. The main overlay globals' authored DIR32 operands are in `routes-coff-after.log`.

| Global | Retail body RVA | Reads | Writes |
|---|---|---:|---:|
| TheDownloadManager | 0x004C74B0, DownloadMenuInit | 1 | 2 |
| TheDownloadManager | 0x004C76F0, DownloadMenuShutdown | 1 | 1 |
| TheDownloadManager | 0x0062F7F0, StartDownloadingPatches | 3 | 0 |
| g_Va012F70A4 | 0x006279F0, existing opaque OK callback body | 0 | 1 |
| g_Va012F70A4 | 0x00627A20, existing opaque Cancel callback body | 0 | 1 |
| g_Va012F70A4 | 0x00627A50, existing opaque cleanup body | 1 | 1 |
| g_Va012F70A4 | 0x00627C80, GSMessageBoxOk | 1 | 2 |
| g_Va012F70A4 | 0x00627D80, GSMessageBoxOkCancel | 1 | 2 |
| g_Va012F70A4 | 0x00627E90, GSMessageBoxYesNo | 1 | 2 |
| okFunc | 0x006279F0 | 1 | 1 |
| okFunc | 0x00627A50 | 1 | 1 |
| okFunc | 0x00627C80 | 1 | 2 |
| okFunc | 0x00627D80 | 1 | 2 |
| okFunc | 0x00627E90 | 1 | 2 |
| cancelFunc | 0x00627A20 | 1 | 1 |
| cancelFunc | 0x00627A50 | 1 | 1 |
| cancelFunc | 0x00627C80 | 1 | 1 |
| cancelFunc | 0x00627D80 | 1 | 2 |
| cancelFunc | 0x00627E90 | 1 | 2 |
| reOpenPlayerInfoFlag | 0x00627C40, existing opaque setter | 0 | 1 |
| reOpenPlayerInfoFlag | 0x00628270, CheckReOpenPlayerInfo | 1 | 1 |

The message-box wrappers are free cdecl functions, with two four-byte UnicodeString value arguments followed by one or two pointers to zero-argument cdecl callbacks. They have no receiver. Retail `GSMessageBoxOk` stores its third argument into VA 0x012F70A8. The two-button wrappers store their third argument there and their fourth argument into VA 0x012F70AC. They pass body VA 0x00A279F0 as the OK/Yes callback and body VA 0x00A27A20 as the Cancel/No callback to the existing independently pinned `MessageBoxOk`, `MessageBoxOkCancel` and `MessageBoxYesNo` implementations. Each callback body loads its respective four-byte global, clears the one-byte activity state, invokes the nonnull function pointer with no arguments and clears that pointer. This independently reproduces the reference's `okFunc` and `cancelFunc` access patterns at lines 55 through 78 and 109 through 137. The old split TU mislabeled its callback arguments and used its `_okFunc` name at VA 0x012F70AC and `_cancelFunc` at VA 0x012F70A8 in its final stores. The correction gives every reference to each external pointer one consistent address.

The activity byte is tested before cleanup, cleared after cleanup, set to one after creating a dialog and cleared by either callback. The cleanup body at RVA 0x00627A50 performs the same lifetime test before clearing both callback pointers. This establishes its correspondence in role to Zero Hour's window-tracking variable, while the exclusively one-byte accesses and zero/one writes refute the pointer type. No existing pin or reference declaration establishes BFME's exact name, so an address-derived name is retained.

The reference's other file-scope arrays are outside the questioned interval. The retail overlay-open body indexes `gsOverlays` at VA 0x012B92A4 and `overlayLayouts` at VA 0x012F70B4. Their declarations appear at reference GameSpyOverlay.cpp:160 and :173, and the indexed retail accesses appear in the full overlay-open disassembly in the COFF route logs. They remain unchanged.

The setter at RVA 0x00627C40 writes one to VA 0x012F70B0. `CheckReOpenPlayerInfo` at RVA 0x00628270 tests that byte, pushes overlay enum value zero, calls the proven overlay-open route and clears the byte. Zero Hour declares `GSOVERLAY_PLAYERINFO` as the first enum entry in `GameSpyOverlay.h:49`. Its setter/checker performs exactly these operations. The source retains the existing volatile qualifier to preserve its access shape. Zero Hour's `Bool` is `bool` in `Libraries/Include/Lib/BaseType.h:132`, so the new external COFF spelling is `?reOpenPlayerInfoFlag@@3_NC`. The unrelated existing `?reOpenPlayerInfoFlag@@3EC` spelling at VA 0x012F7178 is an unsigned-char declaration from a different TU. That pin and every MainMenuUtils source remain unchanged for the other seat.

## ILT routes and repository relocations

`build/rlink/routes-coff-before.log` records the original private COFF operands, including the one `_reOpenPlayerInfoFlag` symbol reaching both VA 0x012F70A4 and VA 0x012F70B0, and the split TU's crossed final callback stores. `routes-coff-after.log` records all affected functions' DIR32 symbols, storage classes, offsets, retail targets and object addends after correction, including the three callback/cleanup bodies and the reopen setter. The external callback globals and flags have one consistent retail target each.

Every used ILT jump is read as five bytes and followed until the final body. The raw routes are in both COFF route logs: VA 0x0044A340 (`e9 eb c3 47 00`) reaches MessageBoxOk at VA 0x008C6730; VA 0x004159FB (`e9 80 0e 4b 00`) reaches MessageBoxOkCancel at VA 0x008C6880; VA 0x0043DF69 (`e9 32 86 48 00`) reaches MessageBoxYesNo at VA 0x008C65A0; VA 0x0042BA21 (`e9 7a c5 5f 00`) reaches GameSpyOpenOverlay at VA 0x00A27FA0. Existing pin rows are in `callee-pins.log`, and the supplied reference declarations are in `reference-declarations.log` and `zh-overlay.log`.

VA 0x00442A50 (`e9 3b 2a 48 00`) reaches the nine-byte wrapper at VA 0x008C5490. Its complete retail body pushes a null argument and calls VA 0x00449AD0 (`e9 6b 8c 4d 00`), which reaches the existing ReleaseWindowLayout pin's body at VA 0x00922740. The wrapper takes no receiver or arguments from the activity-byte callers. Its instruction bytes and both jumps are in the COFF route logs. It does not read a window pointer from VA 0x012F70A4.

## Correction scope and refutation

Only variable declarations, definitions, uses, types and the split function's parameter labels are corrected. Existing function ledger names and extents remain unchanged, so no function identity is retired and no `add_match.py --correct-identity` operation is needed. The three callback/cleanup sources and the existing reopen setter now reference the shared definitions. Their explanatory callback comments no longer describe download completion. No shared header, generated source, GameSpy MainMenuUtils source or VA 0x012F7178 datum is changed. Existing DIR32 spellings and symbols.csv pins are retained; four new DIR32 spellings and four byte-gated data rows are additive.

The exact EA name at VA 0x012F70A4 and the identity of the two intervening three-byte ranges remain unresolved. An independent BFME symbol record or EA declaration for that exact byte would settle the spelling. A validated reference using a four-byte window pointer at that address would refute the one-byte conclusion. A dialog's third callback argument reaching VA 0x012F70AC instead of VA 0x012F70A8, a callback slot receiving the opposite body, or a different final target for a recorded ILT jump would refute the callback names. A proven player-information reopen path using a different byte would refute the reopen correspondence. An additional direct absolute reference outside the eleven recorded extents would refute the access census. Any changed verified instruction or failed scoped gate would reject the candidate.

The final build, CSV, pin-consistency, declared-function, data verification and before/after LINKED receipts and all changed paths are listed in the local `build/worker-final.md`. The census preview has pre-existing linking blockers and is not a whole-program link.

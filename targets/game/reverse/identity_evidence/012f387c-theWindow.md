# theWindow at VA 0x012F387C

## Unresolved correction after a byte-gate refusal

The retail datum role and extent below are established, but this correction was refused by the source byte gate. Changing its main-writer declaration from static storage to an external definition changed instruction scheduling in the existing matched body. Raw failure: `build/rlink/pointer-globals-20261005/group3-build-02.log`. All source changes and the new data row for this address were restored. This datum remains unchanged and unlinked. A declaration-only spelling or storage contract that preserves the original instruction sequence would settle the implementation blocker; rewriting the body is outside this run.

The datum is a zero-initialized four-byte GameWindow pointer in `.data`, with the bytes read over the entire extent in `012f387c-extent-probe.log`. It occupies 4 bytes. Every initial pointer value is null; there is no initialized-pointer relocation to follow. No other data row overlaps the verified extent and no DIR32 name starts strictly inside it. The canonical decorated spelling already exists in `dir32_addresses.csv`, so it is retained beside the competing rows without inserting a duplicate. The rejected candidate definition was sized and data-byte-verified by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Diplomacy.cpp`.

## Retail facts and reference

ShowDiplomacy at VA 008C3DE0 creates the layout using the EA string Diplomacy.wnd at 010FDE8C. It loads the returned WindowLayout first-window member at offset 8 and stores that GameWindow pointer at 008C3EA3. ResetDiplomacy at 008C3350 clears it at 008C339C. UpdateDiplomacyBriefingText and grabWindowPointers use it as the parent GameWindow for Diplomacy.wnd child lookup. These uses match the Zero Hour file-scope theWindow variable. The unrelated same-named local variable in ControlBarPopupDescription is not renamed. Diplomacy.cpp owned the candidate external definition, which was restored; grabWindowPointers retains its original declaration.

Reference: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Diplomacy.cpp:95`.

## Receiver and argument contract

The slot holds the first GameWindow of the Diplomacy layout. Readers pass its value as the parent argument for child-window lookup. The witnessed layout field is at offset 8; it is not an inline window or string buffer. The refused external definition is restored, so the existing receiver and argument contract is unchanged.

## Competing spellings

These are original explicit declaration counts from `strict-original-declarations.log`, including multiline static definitions. Same-spelled local variables in other menus are counted but do not identify this retail address. The canonical type is chosen from retail and reference evidence.

| Decorated spelling | Initial game-file declaration count |
|---|---:|
| `?g_bfmeGlobLF@@3PAVBfmeGlobLF@@A` | 2 |
| `?theWindow@@3PAVGameWindow@@A` | 3 |

## Refutation and raw evidence

A store of a nonwindow pointer, a different WindowLayout first-window offset, a reader requiring another layout, an interior datum boundary or changed verified instructions would refute the candidate correction.

Raw logs are under `build/rlink/pointer-globals-20261005/`: `012f387c-retail-xrefs.log`, `012f387c-writer-context.log`, `012f387c-extent-probe.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `zh-global-declarations.log`, `window-array-boundaries.log`, `008cbbb0-full-disassembly.log` and the gate logs named in `check-receipts.jsonl` and `build/worker-final.md`.

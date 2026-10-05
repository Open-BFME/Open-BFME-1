# parent at VA 0x012F415C

## Unresolved correction after a byte-gate refusal

The retail datum role and extent below are established, but this correction was refused by the source byte gate. Changing its main-writer declaration from static storage to an external definition changed instruction scheduling in the existing matched body. Raw failure: `build/rlink/pointer-globals-20261005/group3-build-06.log`. All source changes and the new data row for this address were restored. This datum remains unchanged and unlinked. A declaration-only spelling or storage contract that preserves the original instruction sequence would settle the implementation blocker; rewriting the body is outside this run.

The datum is a zero-initialized four-byte GameWindow pointer in `.data`, with the bytes read over the entire extent in `012f415c-extent-probe.log`. It occupies 4 bytes. Every initial pointer value is null; there is no initialized-pointer relocation to follow. No other data row overlaps the verified extent and no DIR32 name starts strictly inside it. The canonical decorated spelling already exists in `dir32_addresses.csv`, so it is retained beside the competing rows without inserting a duplicate. The rejected candidate definition was sized and data-byte-verified by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenInit.cpp`.

## Retail facts and reference

ScoreScreenInit at VA 008E8DC0 resolves the named parent ID through TheWindowManager vtable slot 0xDC and stores the returned GameWindow at 008E9085. Its subsequent child lookups load this slot as their parent. The reference names the key ScoreScreen.wnd:ParentScoreScreen and defines a GameWindow *parent. populatePlayerInfo reads the same address as the lookup parent for player labels. This is the ScoreScreen parent variable, not another menu file's local parent. ScoreScreenInit.cpp owns the main writer; its candidate external definition was restored; ScoreScreen.cpp and populatePlayerInfo use it.

Reference: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen.cpp:124`.

## Receiver and argument contract

The slot holds the ScoreScreen parent GameWindow returned by GameWindowManager. Consumers pass it as the parent argument when resolving player labels. The refused external definition is restored, so the existing receiver and argument contract is unchanged.

## Competing spellings

These are original explicit declaration counts from `strict-original-declarations.log`, including multiline static definitions. Same-spelled local variables in other menus are counted but do not identify this retail address. The canonical type is chosen from retail and reference evidence.

| Decorated spelling | Initial game-file declaration count |
|---|---:|
| `?Rva012F415C@@3PAVGameWindow@@A` | 1 |
| `?parent@@3PAVGameWindow@@A` | 45 |

## Refutation and raw evidence

A store of a nonwindow pointer, a child lookup using another parent slot, an interior datum boundary or changed verified instructions would refute the candidate correction.

Raw logs are under `build/rlink/pointer-globals-20261005/`: `012f415c-retail-xrefs.log`, `012f415c-writer-context.log`, `012f415c-extent-probe.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `zh-global-declarations.log`, `window-array-boundaries.log`, `008cbbb0-full-disassembly.log` and the gate logs named in `check-receipts.jsonl` and `build/worker-final.md`.

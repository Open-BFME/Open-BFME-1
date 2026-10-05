# TheSelectionTranslator at VA 0x012F4CA0

## Result and retail extent

The datum is a zero-initialized four-byte SelectionTranslator pointer in `.data`, with the bytes read over the entire extent in `012f4ca0-extent-probe.log`. It occupies 4 bytes. Every initial pointer value is null; there is no initialized-pointer relocation to follow. No other data row overlaps the verified extent and no DIR32 name starts strictly inside it. The canonical decorated spelling already exists in `dir32_addresses.csv`, so it is retained beside the competing rows without inserting a duplicate. The definition is byte-verified and sized by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/MessageStream/SelectionXlat.cpp`.

## Retail facts and reference

The constructor at VA 009B7D70 stores this at 009B7E1C. InGameUI::setInputEnabled reads the slot at 0083B37E and calls ILT 004306DE (E9 DD6C5800), final target 009B73C0, to clear drag selection. GameWinBlockInput at 00878F60 loads this singleton and calls ILT 0042F3A1 (E9 2A805800), ending at 009B73D0, with a false left-button state, then the same drag-selection reset. Zero Hour SelectionTranslator constructor publishes the singleton; the reference input-blocking callback uses these same operations.

Reference: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/SelectionXlat.cpp:261`.

## Receiver and argument contract

The slot supplies the SelectionTranslator ECX thiscall receiver. GameWinBlockInput passes a false left-button state and invokes drag-selection reset through the verified ILT routes. The BfmeSelectionTranslator partial method view is retained through an explicit cast at its existing use. No wrapper, inheritance or linker alias is introduced.

## Competing spellings

These are original explicit declaration counts from `strict-original-declarations.log`, including multiline static definitions. Same-spelled local variables in other menus are counted but do not identify this retail address. The canonical type is chosen from retail and reference evidence.

| Decorated spelling | Initial game-file declaration count |
|---|---:|
| `?TheSelectionTranslator@@3PAVBfmeSelectionTranslator@@A` | 1 |
| `?TheSelectionTranslator@@3PAVSelectionTranslator@@A` | 1 |

## Refutation and raw evidence

A constructor publishing another singleton address, an ILT route ending at a different body, another receiver contract or changed verified instructions would refute this correction.

Raw logs are under `build/rlink/pointer-globals-20261005/`: `012f4ca0-retail-xrefs.log`, `012f4ca0-writer-context.log`, `012f4ca0-extent-probe.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `zh-global-declarations.log`, `window-array-boundaries.log`, `008cbbb0-full-disassembly.log` and the gate logs named in `check-receipts.jsonl` and `build/worker-final.md`.

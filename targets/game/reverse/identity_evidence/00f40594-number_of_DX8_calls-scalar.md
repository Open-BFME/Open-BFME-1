# number_of_DX8_calls at VA 0x01340594

The datum is `?number_of_DX8_calls@@3IA`, a 4-byte `unsigned int` in retail `.data`, initialized to zero (`00 00 00 00`). The existing definition in `game/Libraries/Source/WWVegas/WW3D2/dxwrapper.cpp:201` owns it. This correction adds its data row and respells twelve source files without changing function bodies. `BfmeConv816.cpp` retains `g_bfmeCountELH`, whose existing DIR32 alias remains valid, because its unrelated `BfmeThingELAb::bfmeGoELAb` definition is already unmatched. No pin or DIR32 alias is removed.

## Retail facts and identity

The reference definition is `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp:181`. The header declares `extern unsigned number_of_DX8_calls` at line 119 and increments it after DX8 interface calls in the macros at lines 132 through 139. The reference resets and snapshots it in the statistics routines at lines 1623, 1646 and 1660. The BFME spelling already has a `symbols.csv` pin and a DIR32 row at this VA. Raw reference and owner queries are in `build/rlink/t32-counter-redo-20261005/reference-counter.log` and `owner-definition.log`.

Retail `DX8Wrapper::Begin_Statistics` at RVA 0x00902380 clears this dword. `DX8Wrapper::End_Statistics` at RVA 0x009023C0 reads it and copies it to the separate previous-frame counter. Device and shader bodies increment this same dword after interface calls. Render-state and texture-stage counters occupy separate addresses, including VA 0x01340564 and VA 0x01340568, so `ScreenTotalChanges` does not describe this datum. Re-decoded retail instructions and boundary labels from the first run are in `build/rlink/t32-counter-redo-20261005/retail-counter-before.log`. That probe reports missing Ghidra boundary rows explicitly and does not assert complete coverage. Matched-row boundary evidence, full statistics bodies, and each five-byte E9 in the ILT chains to matched counter users are recorded independently in `build/rlink/t32-counter-redo-20261005/matched-counter-routes.log`.

Before addition, no data row overlaps `[0x01340594, 0x01340598)` and no DIR32 name lies strictly inside it. The initial value, neighboring bytes, existing pins, and interval queries are measured in `build/rlink/t32-counter-redo-20261005/retail-counter-before.log`. The sanctioned data addition verifies the existing definition against retail, including its scalar size.

## Receiver and argument contract

This is a global scalar with no receiver or arguments. The reference type is unsigned 32-bit. The retail accesses operate on a dword, and increments preserve modulo-32-bit behavior. Files formerly declaring signed placeholder counters now declare `extern unsigned int number_of_DX8_calls`; each changed source must retain every verified function byte under its scoped gate.

## Competing spellings

These counts identify game source files that directly declare or define the identifier before the correction. The header is counted as a file, not expanded into every translation unit that includes it. Raw file inventories and individual declaration lines are in `build/rlink/t32-counter-redo-20261005/spelling-inventory-before.log` and `declaration-counts-before.log`. The broader identifier-use inventory in `retail-counter-before.log` also includes files that use the header declaration. The canonical name is selected from the reference and retail behavior, independently of the counts.

| DIR32 spelling | Game files directly declaring or defining it |
|---|---:|
| `?D3DCallCount@DX8Wrapper@@0IA` | 0 |
| `?Rva01340594DX8Calls@@3IA` | 5 |
| `?ScreenNumberOfCalls@@3IA` | 0 |
| `?ScreenTotalChanges@@3IA` | 0 |
| `?g_00716500_count@@3HA` | 1 |
| `?g_0071be90_count@@3HA` | 1 |
| `?g_bfme936Count@@3HA` | 2 |
| `?g_bfmeA1057@@3HA` | 1 |
| `?g_bfmeB1104@@3HA` | 0 |
| `?g_bfmeCountELH@@3HA` | 1 |
| `?g_bfmeCountTDB@@3HA` | 1 |
| `?g_bfmeD3DCallCount@@3IA` | 1 |
| `?g_bfmeHits1054@@3HA` | 0 |
| `?number_of_DX8_calls@@3IA` | 31 |

## Refutation

A different reference declaration, incompatible retail access width or role, a datum or DIR32 target inside the claimed extent, an ILT route terminating at a different body, or any changed verified function byte would refute the correction. The declaration exception is confined to the untouched `BfmeConv816.cpp`; all changed sources must pass `find_declared_unmatched.py --fail`. Raw gates and per-file LINKED measurements are recorded in `build/worker-final.md`.

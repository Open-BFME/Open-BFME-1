# comboBoxPlayer at VA 0x012F3C24

## Result and retail extent

The datum is a zero-initialized 32-byte array of eight GameWindow pointers in `.data`, with the bytes read over the entire extent in `012f3c24-extent-probe.log`. It occupies 32 bytes. Every initial pointer value is null; there is no initialized-pointer relocation to follow. No other data row overlaps the verified extent and no DIR32 name starts strictly inside it. The canonical decorated spelling already exists in `dir32_addresses.csv`, so it is retained beside the competing rows without inserting a duplicate. The definition is byte-verified and sized by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp`.

## Retail facts and reference

LanGameOptions initialization at VA 008CBBB0 constructs the EA string LanGameOptionsMenu.wnd:ComboBoxPlayer%d at 010FF2D0 and stores the GameWindow lookup result with mov [esi*4+012F3C24],eax at 008CC00A. The loop ends with cmp esi,8 at 008CC407 and jl 008CBFA0 at 008CC40A. This proves eight four-byte entries. Tooltip and start handlers index the same array. VA 008CAFBA passes the address of this table, not the contents of a pointer variable, to the LAN slot-list helper. The next table begins at 012F3C44, exactly 32 bytes later. Zero Hour defines the same eight-slot GameWindow pointer array. The sole external definition remains in LanGameOptionsMenu.cpp; the inline-assembly call site now declares and spells that array instead of a char array.

Reference: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp:135`.

## Receiver and argument contract

The name denotes inline storage for eight GameWindow pointers. Passing comboBoxPlayer supplies the table address, while indexing supplies one GameWindow pointer. The LAN helper receives the same table address and arguments after respelling its declaration and assembly operand. No wrapper, inheritance or linker alias is introduced.

## Competing spellings

These are original explicit declaration counts from `strict-original-declarations.log`, including multiline static definitions. Same-spelled local variables in other menus are counted but do not identify this retail address. The canonical type is chosen from retail and reference evidence.

| Decorated spelling | Initial game-file declaration count |
|---|---:|
| `?comboBoxPlayer@@3PAPAVGameWindow@@A` | 5 |
| `?g_rva004CAF70_a@@3PADA` | 1 |

## Refutation and raw evidence

An initialization loop reaching a ninth element, a pointer-variable load instead of the witnessed table address, an interior datum boundary or changed verified instructions would refute this correction.

Raw logs are under `build/rlink/pointer-globals-20261005/`: `012f3c24-retail-xrefs.log`, `012f3c24-writer-context.log`, `012f3c24-extent-probe.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `zh-global-declarations.log`, `window-array-boundaries.log`, `008cbbb0-full-disassembly.log` and the gate logs named in `check-receipts.jsonl` and `build/worker-final.md`.

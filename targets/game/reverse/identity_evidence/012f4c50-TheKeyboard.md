# TheKeyboard at VA 0x012F4C50

## Result and retail extent

This datum is one zero-initialized four-byte `Keyboard *TheKeyboard` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/Input/Keyboard.cpp`.

## Retail facts and reference

GameClient initialization at VA 0082F5A0 calls its keyboard factory through vtable offset 0xA0, stores the object at 0082F68A, and names it with TheKeyboard at 010F3790. The destructor clears it at 008315FC. Keyboard shift queries and the HotKeyTranslator printable-key receiver use this slot. The existing isShift@Keyboard call pin, the reference Keyboard singleton and the EA string prove the pointee identity; MovieOpen keyboard and modifier views read this object.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Input/Keyboard.cpp:40`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x0045CC20`, `0x0046B910`, `0x007A40A0`, `0x007BBE50`, `0x007C3850`, `0x0080E990`, `0x0080F780`, `0x0082F5A0`, `0x00831380`, `0x008329D0`, `0x008A747F`, `0x008B2F30`, `0x008B4010`, `0x008B4FF0`, `0x008B5E40`, `0x008B8940`, `0x008BBFC0`, `0x008BCFD0`, `0x00969420`, `0x009694E0`, `0x009A4C60`, `0x009B18C0`, `0x009B3F50`, `0x009B5590`, `0x009B8520`, `0x00A09710`, `0x00AF0300`, `0x00AF2CC0`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?KeyboardGlobal0040F780@@3PAUKeyboard0040F780@@A` | 2 |
| `?TheBfmeKeyboardModifiers@@3PAVBfmeKeyboardModifiers@@A` | 0 |
| `?TheKeyboard@@3PAVKeyboard@@A` | 9 |
| `?rva004BBFC0_keyboard@@3PAURva004BBFC0Keyboard@@A` | 1 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f4c50-retail-xrefs.log`, `012f4c50-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.

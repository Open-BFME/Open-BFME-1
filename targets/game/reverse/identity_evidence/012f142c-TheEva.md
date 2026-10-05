# TheEva at VA 0x012F142C

## Result and retail extent

This datum is one zero-initialized four-byte `Eva *TheEva` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/Eva.cpp`.

## Retail facts and reference

GameEngine initialization at VA 00479060 passes slot address 012F142C at 004794E4 to ILT 0042580B (E9 80D90400), ending at 00473190. The immediately preceding string at 010765A0 is TheEva. Player::setRankLevel, SpecialAbilityUpdate and VictoryConditions use this slot to enqueue Eva messages; their call at ILT 0042B5F3 (E9 A87D3F00) ends at 008233A0. The existing typed pin setShouldPlay@Eva describes its message and optional Coord3D argument. These are the reference Eva announcement-manager operations.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Eva.cpp:569`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x00479060`, `0x004D7E30`, `0x005CEFC0`, `0x0063F670`, `0x006408E0`, `0x0069E330`, `0x006A9420`, `0x006A9850`, `0x006F05D0`, `0x0075F920`, `0x0076F4D0`, `0x00770730`, `0x00797540`, `0x008182A0`, `0x00819F00`, `0x0081EBD0`, `0x00822BD0`, `0x00825B80`, `0x00825C90`, `0x00826C60`, `0x00828880`, `0x00832010`, `0x008329D0`, `0x008A6E20`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheBfmeGlobal_012f142c@@3PAVBfmeGlobal_012f142c@@A` | 2 |
| `?TheEva@@3PAVEva@@A` | 11 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f142c-retail-xrefs.log`, `012f142c-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.

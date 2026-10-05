# TheIMEManager at VA 0x012F3344

## Unresolved correction after a declaration-gate refusal

The IMEManagerInterface singleton identity below is established, and its candidate data and function-byte gates passed. The required declared-unmatched gate rejects OnlineLoginConstructor.cpp because its existing BfmeAptWindowContext constructor has no ledger claim or unmatched annotation. The same rejection occurs on the original file, as measured in `build/rlink/pointer-globals-20261005/ime-original-declared-unmatched.log`. This is an existing unproven helper definition, not a spelling or filesystem issue. All IME-only source changes and its new data row were restored; this address remains unchanged. Independently proving and correctly recording that helper, or removing its unneeded definition with byte verification, would settle the source-gate blocker. No other address correction was discarded.

This datum is one zero-initialized four-byte `IMEManagerInterface *TheIMEManager` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. The restored candidate definition was backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GameClient.cpp`.

## Retail facts and reference

GameClient initialization stores the return of ILT 00437A33 (E9 48594500), final target 0088D380, at VA 0082FCB2. The naming path at 0082FCC7 uses TheIMEManager at 010F3710. IMEManager::init, GameWindow destruction, text-entry handling and shell hiding all read the slot to operate on IME state. The reference singleton type is IMEManagerInterface, with concrete IMEManager implementations behind it. Since the reference-owned IMEManager.cpp is absent in game, the definition belongs in GameClient.cpp, whose init creates this singleton. Concrete deletion and method views remain explicit casts.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/IMEManager.cpp:325`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x0045CC20`, `0x0082F5A0`, `0x00831380`, `0x00879CD0`, `0x0088D9C0`, `0x008BE340`, `0x008BEBD0`, `0x008CA140`, `0x00915DD0`, `0x0094CB60`, `0x009538A0`, `0x0097F0B0`, `0x0097F2E0`, `0x0097F470`, `0x0097F4E0`, `0x0097F5B0`, `0x0097F8E0`, `0x0097FCB0`, `0x00B986C0`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Glo012F3344@@3PAVGlo012F3344Type@@A` | 3 |
| `?Glo012F3344@@3PAVRva0057F0B0ShellGlobal@@A` | 1 |
| `?TheBfmeImeManager@@3PAVBfmeImeManager@@A` | 4 |
| `?TheIMEManager@@3PAVIMEManager@@A` | 3 |
| `?TheIMEManager@@3PAVIMEManagerInterface@@A` | 2 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f3344-retail-xrefs.log`, `012f3344-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.

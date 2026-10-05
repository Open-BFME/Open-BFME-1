# TheBannerUI at VA 0x012F4B70

## Result and retail extent

This datum is one zero-initialized four-byte `BannerUI *TheBannerUI` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/InGameUICreateReplayControlThunk.cpp`.

## Retail facts and reference

InGameUI::createReplayControl at VA 00840B40 allocates 0x44 bytes, invokes ILT 00434CF7 (E9 A4FC5400), ending at 009849A0, and stores the returned object at 00840F49. InGameUI destructor clears it at 0084AEED. BannerUI parsing and ArmySummaryHelpText consume the same pointer, and the class vtable is independently pinned from SubsystemInterface slots and adjacent BannerUI strings. BannerUI::init uses the EA asset BannerUI.apt, and its destructor uses BannerUI/~Location%d/Banner paths. The constructor at VA 009849A0 passes the EA string TheBannerUI at 0110B8F8 at instruction 00984A14 to the subsystem naming path, independently confirming the existing singleton spelling. The sole definition is in the main-writer source InGameUICreateReplayControlThunk.cpp.

The Zero Hour reference has no BannerUI counterpart. The BFME EA strings, constructor, vtable and consumers cited above establish its identity.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical. The BannerUI definition is added alongside the writer without changing or renaming its existing naked function; no naked or emit line is added.

## Readers and writers

Decoded retail bodies referencing this address: `0x006ED8C0`, `0x00840B40`, `0x008410C0`, `0x0084AE70`, `0x0084B3F0`, `0x0089A540`, `0x0089A8F0`, `0x008C0C80`, `0x008C0E10`, `0x0090D3B0`, `0x0090D3D0`, `0x00981E30`, `0x00982A10`, `0x00982C70`, `0x00984550`, `0x00984D20`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheBannerUI@@3PAVBannerUI@@A` | 8 |
| `?TheBfmeGlobal_012f4b70@@3PAVBfmeGlobal_012f4b70@@A` | 1 |
| `?g_Glo00EF4B70@@3PAVGen005847F0@@A` | 0 |
| `?g_bfmeObjDXI@@3PAVBfmeGlobDXI@@A` | 1 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f4b70-retail-xrefs.log`, `012f4b70-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `009849a0-full-disassembly.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.

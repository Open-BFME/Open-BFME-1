# TheMappedImageCollection at VA 0x012F6924

## Result and retail extent

This datum is one zero-initialized four-byte `ImageCollection *TheMappedImageCollection` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/System/Image.cpp`.

## Retail facts and reference

GameClient initialization at VA 0082F5A0 allocates 0x14 bytes, invokes ILT 0042E433 (E9 A84C5A00), final target 009D30E0, stores the object at 0082F702, and calls ILT 004071F8 (E9 A3B15C00), ending at 009D23A0, with an image-load argument 0x200. The destructor clears the pointer at 008315E6. Portrait and mapped-image lookup callers use its name-indexed image collection. The Zero Hour declaration and definition name this pointee ImageCollection; MappedImageCollection is a competing local view, not a separately allocated singleton. The constructor ledger uses object-symbol=??0ImageCollection@@QAE@XZ at this exact body, though its LocomotorStore identity claim is outside this datum-only correction.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/System/Image.cpp:137`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x004BAAA0`, `0x004C2480`, `0x004E0B40`, `0x004E0B60`, `0x004E0B80`, `0x004E0BA0`, `0x004F9CF0`, `0x004FA610`, `0x0050AE70`, `0x0050AEF0`, `0x0053EE70`, `0x0053EEC0`, `0x00543730`, `0x00543890`, `0x005448F0`, `0x006A1A80`, `0x00815D50`, `0x0082EE70`, `0x0082F5A0`, `0x00831380`, `0x008516E0`, `0x00851A57`, `0x00855F60`, `0x00856A90`, `0x0086C790`, `0x0086F490`, `0x0086F910`, `0x00871900`, `0x0087A0A0`, `0x00885EE0`, `0x008916D0`, `0x00891A40`, `0x008920E0`, `0x00892400`, `0x00893120`, `0x0089C3F0`, `0x008A0F70`, `0x008A2CB0`, `0x008C8B40`, `0x008D9DF0`, `0x008DA760`, `0x008E8050`, `0x008E8320`, `0x008F1760`, `0x008F2C00`, `0x008F9CE0`, `0x008F9E60`, `0x009091F0`, `0x0091C2D0`, `0x00920E70`, `0x00921390`, `0x009284F0`, `0x0092A2E0`, `0x00930550`, `0x009406E0`, `0x00958BE0`, `0x00959400`, `0x0095D150`, `0x0097F980`, `0x00992570`, `0x00992640`, `0x00992A90`, `0x00996D40`, `0x0099B070`, `0x009BB150`, `0x009CB720`, `0x00A193E0`, `0x00A19420`, `0x00A2D810`, `0x00A2DB90`, `0x00A8EBF0`, `0x00AC3500`, `0x00B00950`, `0x00B8D810`, `0x00B95140`, `0x00B9A980`, `0x00B9AEC0`, `0x00B9B7D0`, `0x00B9BCA0`, `0x00B9C7E0`, `0x00B9D9F0`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheMappedImageCollection@@3PAVImageCollection@@A` | 53 |
| `?TheMappedImageCollection@@3PAVMappedImageCollection@@A` | 2 |
| `?TheMappedImageCollection@@3PAVMappedImageCollectionPortraitShim@@A` | 0 |
| `?TheOpen2Images143730@@3PAVOpen2Images143730@@A` | 0 |
| `?g_bfmeM1024@@3PAVBfmeM1024@@A` | 1 |
| `?g_bfmeRegistryBF@@3PAVBfmeRegistryBF@@A` | 0 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f6924-retail-xrefs.log`, `012f6924-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.

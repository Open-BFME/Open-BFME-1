# TheMouse at VA 0x012F4C5C

## Result and retail extent

This datum is one zero-initialized four-byte `Mouse *TheMouse` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/Input/Mouse.cpp`.

## Retail facts and reference

GameClient initialization at VA 0082F5A0 calls its mouse factory through vtable offset 0xA4, stores the result at 0082FBB3, invokes the mouse init and reset vtable slots 0x24 and 0x28, and names it with TheMouse at 010F3744. The destructor clears it at 008314EC. Mouse capture, cursor and movie consumers match the Mouse interface in the reference. W3D draw and local state views refer to the same Mouse object.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Input/Mouse.cpp:57`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x0046B910`, `0x006EF010`, `0x006EF090`, `0x00748430`, `0x00783490`, `0x007839E0`, `0x00786910`, `0x0078D100`, `0x00794260`, `0x00796B00`, `0x00797540`, `0x007BE1F0`, `0x007C8B90`, `0x0080DC10`, `0x0080DC30`, `0x0080F780`, `0x0082F5A0`, `0x00831380`, `0x008329D0`, `0x0083AA10`, `0x0083AAF0`, `0x0083ACE0`, `0x0083ADE0`, `0x0083AF60`, `0x0083CCB0`, `0x00842DE0`, `0x008445C0`, `0x00845080`, `0x0084A2E0`, `0x0084AE70`, `0x00867460`, `0x0086E850`, `0x0086ECC0`, `0x0087E630`, `0x0088E480`, `0x008914C0`, `0x008BFFE0`, `0x008CB220`, `0x008CBAF0`, `0x008CE850`, `0x008D9100`, `0x008F1430`, `0x008F14F0`, `0x008F1760`, `0x008F2410`, `0x008FA800`, `0x0090FF30`, `0x00914A40`, `0x00918150`, `0x0091D300`, `0x0091E700`, `0x0091EFE0`, `0x0091F3A0`, `0x00924730`, `0x0092B2A0`, `0x009307B0`, `0x009369A0`, `0x0093A280`, `0x0093AF50`, `0x00946E00`, `0x00954510`, `0x009639B0`, `0x00965170`, `0x009651F0`, `0x00966B10`, `0x00969720`, `0x009699B0`, `0x00973000`, `0x00974500`, `0x0097A200`, `0x00985D60`, `0x00999490`, `0x009A4570`, `0x009A4690`, `0x009A5FA0`, `0x009A63D0`, `0x009A6790`, `0x009A67E0`, `0x009ADE90`, `0x009AFFB0`, `0x009B1C70`, `0x009B4260`, `0x009B4380`, `0x009B51D0`, `0x009B52B0`, `0x009B5590`, `0x009B6BA0`, `0x009B8520`, `0x00A09360`, `0x00A09940`, `0x00A0D3E0`, `0x00A0D410`, `0x00A0D510`, `0x00A0EE80`, `0x00A0FFC0`, `0x00A12070`, `0x00A12160`, `0x00A13D60`, `0x00A140C0`, `0x00A15B10`, `0x00A174D0`, `0x00A2CFF0`, `0x00AEB500`, `0x00AF0300`, `0x00AFC3F0`, `0x00AFEA60`, `0x00B00300`, `0x00B3D4C0`, `0x00B43CE0`, `0x00B43F80`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Mouse0040F780@@3PAVMouse@@A` | 2 |
| `?TheMouse@@3PAUMouseState@@A` | 0 |
| `?TheMouse@@3PAURva005A63D0Mouse@@A` | 0 |
| `?TheMouse@@3PAVBfmeZ1100@@A` | 0 |
| `?TheMouse@@3PAVGen_005A4470@@A` | 0 |
| `?TheMouse@@3PAVMouse@@A` | 60 |
| `?g_bfmeObjDYF@@3PAVBfmeGlobDYF@@A` | 0 |
| `?g_bfmeStateDS@@3PAVBfmeStateDS@@A` | 0 |
| `?g_bfmeZ1083@@3PAVBfmeZ1083@@A` | 0 |
| `?g_bfmeZ1095@@3PAVBfmeZ1095@@A` | 1 |
| `?g_bfmeZ1100@@3PAVBfmeZ1100@@A` | 1 |
| `?g_mgr12F4C5C@@3PAVBfmeMgr4C5@@A` | 0 |
| `?g_w3dMouseDrawTarget@@3PAVW3DMouseDrawInterface@@A` | 0 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f4c5c-retail-xrefs.log`, `012f4c5c-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.

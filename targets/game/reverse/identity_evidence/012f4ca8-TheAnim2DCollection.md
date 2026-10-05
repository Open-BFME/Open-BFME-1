# TheAnim2DCollection at VA 0x012F4CA8

## Result and retail extent

This datum is one zero-initialized four-byte `Anim2DCollection *TheAnim2DCollection` in retail `.data`. The PE section's virtual-only tail supplies the zero bytes; the stored value is null and therefore has no initialized-pointer relocation to follow. The four-byte loads and stores prove the pointer width. The baseline has no base-relocation directory. No data row overlaps this word, and no DIR32 name starts inside its four-byte extent. The canonical decorated spelling already exists in `dir32_addresses.csv`; the competing rows are retained as evidence, and every game declaration of their globals now uses the canonical spelling.

## Retail facts and reference

Retail VA 0082F728 calls ILT 00448DE7 (E9 84155700), whose final target is 009BA370. The returned object is stored at 0082F731. VA 0082F744 passes the EA string TheAnim2DCollection at 010F3778 to the subsystem naming path. INI::parseAnim2DTemplate at 004BAB30 and Drawable::setEmoticon at 008149E0 load this singleton and call ILT 0040C0EA (E9 41F25A00), ending at 009BB330, the template lookup body. The writer, template lookup and per-frame update role agree with Zero Hour.

Zero Hour defines `Anim2DCollection *TheAnim2DCollection = NULL` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/System/Anim2D.cpp:48`. Its typed singleton and the witnessed retail calls identify one object, rather than several overlapping globals. The definition remains in that reference-owned source file and gains a byte-verified data row. Existing partial pointee views remain local and are reached by casts at their uses; no inheritance, forwarding function or linker alias is added.

## Receiver and argument contract

The global holds an object address, never an inline object or pointer table. Retail loads the word into ECX before thiscall members, or loads the vptr through the pointee for virtual dispatch. Calls retain their original arguments and final ILT routes. Canonicalizing the data relocation changes no function signature or verified instruction. The source gate verifies every existing row in each changed file.

## Competing spellings

Counts are game files with matching explicit declarations or definitions before the correction, from the strict original-declaration inventory; they do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Rva012f4ca8@@3PAVAnim2DCollection@@A` | 2 |
| `?TheAnim2DCollection@@3PAVAnim2DCollection@@A` | 13 |

## Refutation and raw evidence

A retail store of a different object, a pointer width other than four bytes, a relocation or datum boundary inside this word, an ILT route ending at a different body, or a byte change in any existing matched row would refute this correction.

Raw logs: `build/rlink/pointer-globals-20261005/012f4ca8-retail-xrefs.log`, `0082f5a0-full-disassembly.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `evidence-pins.log`, `zh-global-declarations.log`, and `zh-global-uses.log`. Probe instructions include exact bytes and each five-byte E9 jump in every shown route. Gate logs and timestamps are listed in `build/worker-final.md` and the raw `check-receipts.jsonl`.

# 0x009B3F40 SIMD quantization retry

## Result and remaining blockers

This is a partial at revision e5a61d2af33a9b0a241f4d02edd914804daee825. The preserved Rva009B3F40Vp6Reconstruct body compiles to 555 bytes against the 555-byte retail extent and differs in 26 bytes after data references resolve. The first difference is +0x22. The old bank compiled to 555 bytes with 493 differences. The scoped gate fails byte equality, while its string, constant and DIR32 checks pass. Nothing is landed.

The remaining codegen blocker is the bank-address and multiplier prelude, DC register allocation and first scalar source load. Caller validation of the native return type and original formal argument count remains an ABI blocker: no raw direct branch or stored VA pointer to the target was found. The inherited VP6 label is retained because the bank naming policy requires it; vendor ownership and the original native function name are not independently established. The body uses an address-derived identity and retains one SIMD assembly island. A pure intrinsics trial produced a different prologue and loop and does not establish that all C++ intrinsic forms are impossible.

## New hypothesis and refutation

The landed Rva009A6780BuildQuantizers declaration and its complete decoded writes support typed word vectors at context+0x08 and context+0x18 and dword table banks separated by 0x100. The new hypothesis was that a C++ prelude and scalar tail, surrounding only the actual SIMD kernel, would let MSVC delay ESI/EDI saves and eliminate the old full-assembly prologue failure. It would be refuted if that construction retained the old early saves or did not improve its measured comparison. The experiment improved the comparison. Moving the zero-run initialization after pointer and multiplier definitions recovered the retail frame slots and scalar increment shape.

## Complete boundary and ABI review

The preceding landed initializer at RVA 0x009B3EC0 ends with RET at 0x009B3F3C, followed by three INT3 bytes. The target begins at 0x009B3F40 and has one common return at 0x009B416A, followed by five INT3 bytes before the next prologue at 0x009B4170. All target branches remain within this extent and land on decoded instructions. The SIMD loop advances by 16 bytes to 0x80. The scalar loop is unrolled by three and advances its table-byte cursor by 12 to 0x100. There are no direct, indirect or virtual calls, tail jumps, exception states or cleanup helpers in the target.

Let entry ESP be S. PUSH EBX followed by MOV EBX,ESP sets EBX=S-4. Consequently [EBX+8], [EBX+0x0C], [EBX+0x10] and byte [EBX+0x14] are entry slots S+4, S+8, S+12 and S+16. The body accesses a context pointer, source pointer, destination pointer and the low selector byte in that order. Entry ECX and EDX are overwritten before use, excluding an observed register receiver or register argument. RET performs no argument cleanup. Source samples are sign-extended 16-bit values; output stores are 16-bit. Source and destination use MOVDQA, establishing their required alignment. There is no hidden return-storage pointer access. EAX holds the completed loop cursor on exit, so the physical return register does not establish a native void return; the saved void cdecl signature remains an emission view rather than caller-certified ABI.

## Independent layout evidence

Both requested neighbouring initializer sources were inspected. They write context+0x13C and context+0x140 and supply no target prologue or quantizer declaration. The complete retail bodies at 0x009A6780 (table builder) and 0x009A6BA0 (scalar quantizer) were decoded instead. The builder writes both dword banks at +0x190/+0x290, +0x390/+0x490, +0x590/+0x690 and +0x790/+0x890. Its word stores initialize every lane at +0x08 through +0x16, +0x18 through +0x26 and +0x28 through +0x36. The scalar quantizer independently reads selector table VA 0x01142608 and shifts its bank byte by eight. This supplies field-width and stride evidence beyond the donor name. The builder has four __ftol2 calls; the complete 117-byte helper was decoded and checked separately. It consumes ST(0), produces EDX:EAX and reaches one shared LEAVE/RET path. The builder stores EAX as each dword reciprocal.

The target reads the first two unshifted vectors, computes packed absolute magnitudes with XOR/SUB, adds word offsets, uses unsigned high-word multiplication, restores signs and clears the destination. Its DC path reads +0x190, +0x390 and +0x590 after the selected bank displacement. Its AC path reads the complete 16-bit temporary, the signed source word, a dword run penalty at +0x790 and a dword threshold at +0x590. These accesses support the banked byte view and existing Rva009A6780State vector declaration; no STL type is involved. The scalar donor uses a different scan table, so its table name was not substituted for the target table at VA 0x012D8258.

## Measurements and rejected shapes

Every source and unedited probe output is preserved under build/009b3f40-retry/. Counts below come from those raw probe outputs; relocation masking is diagnostic until checked by the scoped gate. The intrinsics shortfall is additional missing output, not a better bank.

| Trial | Compiled bytes | Differing comparison bytes | First offset |
|---|---:|---:|---|
| 00-original.cpp | 555 | 493 | +0x1c |
| 01-intrinsics.cpp | 484 | 448 | +0x0 |
| 02-simd-island.cpp | unavailable | unavailable | compile failure |
| 03-simd-island.cpp | 567 | 294 | +0x22 |
| 04-value-width.cpp | 564 | 268 | +0x22 |
| 05-width-only.cpp | 564 | 269 | +0x22 |
| 06-sum-only.cpp | 567 | 294 | +0x22 |
| 07-store-only.cpp | 567 | 295 | +0x22 |
| 08-typed.cpp | 564 | 268 | +0x22 |
| 09-threshold-lifetime.cpp | 564 | 268 | +0x22 |
| 10-run-late.cpp | 555 | 26 | +0x22 |
| 11-index-first.cpp | 555 | 26 | +0x22 |
| 12-native-table-index.cpp | 596 | 490 | +0x28 |
| 13-byte-bank.cpp | 555 | 26 | +0x22 |
| 14-integer-bank.cpp | 555 | 26 | +0x22 |
| 15-pointer-first.cpp | 555 | 211 | +0x22 |
| best.cpp | 555 | 26 | +0x22 |

Widening the temporary to the full zero-extended integer value follows the actual MOVZX instructions and improved the scalar tests. Reversing threshold addends alone produced unchanged output. Moving the run reset before the destination store improved ordering but did not fix the increments. Splitting the threshold expression alone also produced unchanged output. Initializing run after the table pointers recovered exact scalar instruction lengths. A native two-dimensional bank index added an extra live index and worsened size. Byte-bank and integer-bank views retained the same good comparison. Loading the two vector pointers before the multiplier worsened the comparison. No prior /Oy variant was repeated. The family generator supplied only the already tested store reversal; shape_search correctly refused the existing SIMD island because it accepts pure C++ only.

Resolved difference offsets: 0x22, 0x28, 0x2b, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x37, 0x3a, 0x3e, 0x45, 0x48, 0xad, 0xb1, 0xc0, 0xc6, 0xc9, 0xcc, 0xd0, 0x128, 0x12d.

## Reproduction and reopening

The preferred bank is targets/game/reverse/attempts/0x009b3f40.cpp. Probe its actual symbol ?Rva009B3F40Vp6Reconstruct@@YAXPAXPAF1E@Z at RVA 0x009B3F40 with --size 555. build/009b3f40-retry/resolved_comparison.json retains the actual resolved comparison and relocation records. build/009b3f40-retry/10-scoped-gate.txt retains the raw scoped gate failure. build/009b3f40-retry/retail_decode.txt contains the target, builder and scalar donor; ftol2-decode.txt and their checked-callee logs cover the evidence helpers. references.txt records the empty raw reference screening result, which does not prove that dynamically computed indirect callers cannot exist.

Reopen with evidence that changes the native bank or multiplier lifetime, a demonstrated compiler structure for the remaining prelude, or a decoded actual caller that establishes the native return and argument contract. Ordinary declaration reordering or equivalent pointer arithmetic without changed evidence does not justify repeating this run. No functions.csv row, symbols.csv pin, shared header or tooling file was changed.

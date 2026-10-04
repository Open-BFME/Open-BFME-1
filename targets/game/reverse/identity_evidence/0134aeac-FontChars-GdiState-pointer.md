# FontChars GDI state pointer at VA 0x0134AEAC

VA 0x0134AEAC (RVA 0x00F4AEAC) holds one loader-zero, four-byte pointer to the shared, reference-counted GDI state used by BFME font code. Define it under the existing DIR32 spelling `?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A`. Retail establishes the pointer's runtime contract, but does not establish its original C++ name or distinguish an external global from a file-scope static or static data member. No real-name substitution is justified.

## Retail facts

The hash-bound game baseline is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`. The pointer is in the virtual-only tail of the writable `.data` section, outside its raw file extent. Its four initial bytes are loader zeros, rather than four bytes copied from the file. It has no base relocation or export of its own and is not a compiler constant.

The constructor at RVA 0x00940610 reads the pointer at VA 0x00D40715. On zero, it allocates 0x14 bytes, passes that allocation in ECX to the state constructor at VA 0x00D3C340, and stores EAX into the pointer at VA 0x00D4073C. It then increments the state's dword at offset zero. The state constructor initializes dwords at offsets 0, 4, 8, 12 and 16. Its imported GDI calls create a memory DC at offset 16 and a DIB bitmap at offset 8, with bitmap bits at offset 12 and the previous bitmap at offset 4.

The destructor at RVA 0x00940010 reads the pointer at VA 0x00D400A7 and VA 0x00D400AE, decrements the state's reference count, and tests for zero. On the last reference, it restores the old bitmap, deletes the bitmap and DC, frees the state allocation and stores zero at VA 0x00D400FA. These are the only two absolute pointer-write instructions found by the full-section scan. The other references load the pointer and use the shared DC or DIB bits.

## Retail readers and writers

Addresses in the instruction columns are VAs. Body addresses are RVAs. Anonymous ledger names are retained as anonymous identities.

| Body RVA | Existing identity | Pointer-read instructions | Pointer-write instructions |
|---|---|---|---|
| 0x0093C4A0 | `Rva0093C4A0Target::Check` | 0x00D3C4B3, 0x00D3C4D0 | None |
| 0x0093C570 | `FontCharsClass::Create_GDI_Font` | 0x00D3C688, 0x00D3C6AA | None |
| 0x0093F440 | `?d_0093f440@@YAXXZ` | 0x00D3F469, 0x00D3F493, 0x00D3F55E, 0x00D3F6D3, 0x00D3F7D4 | None |
| 0x00940010 | `FontCharsClass::~FontCharsClass` | 0x00D400A7, 0x00D400AE | 0x00D400FA (zero) |
| 0x00940610 | `FontCharsClass::FontCharsClass` | 0x00D40715 | 0x00D4073C (new state) |
| 0x00940D40 | `?d_00940d40@@YAXXZ` | 0x00D40DB5, 0x00D40DF7, 0x00D40E50, 0x00D40FF1, 0x00D410F4 | None |
| 0x009412F0 | `?d_009412f0@@YAXXZ` | 0x00D4131B, 0x00D41339 | None |

The scan found 21 encodings of the pointer VA in all raw PE sections. All are instruction operands in `.text`, comprising 19 reads and two writes. Function ownership was checked against the narrowly filtered function ledger and Ghidra boundary ledger, and the operands were decoded from those boundaries. The initial ILT is present, but neither its entries nor any five-byte E9 in `.text` jumps to these seven bodies. The observed E8 callers therefore call these bodies directly. For example, VA 0x00D40773 calls the destructor, and VA 0x00D3C888 and VA 0x00D3C89E call the glyph check. The complete E8 candidate list and the E9 search are in the raw probe logs.

## Receiver and argument contract

The datum itself is one pointer and has no receiver or arguments. The font constructor and destructor receive a `FontCharsClass` instance in ECX and use absolute accesses to the shared pointer. The glyph check receives its font object in ECX, reads its font handle at offset 0x48, and takes three stack arguments: UTF-16 input, WORD glyph output and signed character count. It reads the shared state's DC at offset 0x10. The matched wrapper at RVA 0x0093C870 supplies these arguments and calls the glyph check twice with different font receivers. The glyph-check TU's five-dword layout places its DC at the same offset as the constructor and destructor's class. Changing its struct spelling to the existing class spelling changes the external COFF reference, without changing that layout or any instructions.

## Names, range ownership and reference comparison

Before the change, two game files declare `?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A`: `FontCharsClassConstructorBFME.cpp` and `FontCharsClassDestructorBFME.cpp`. One game file, `Rva0093C4A0.cpp`, instead declares `?g_fontCharsGdiState0134AEAC@@3PAUFontCharsGDIState@@A`. The latter spelling has no current DIR32 entry. The retail operands in all three bodies use exactly the same VA. The canonical spelling has independent existing ledger support, so declaration counts do not choose the identity. The correction defines the canonical spelling in the constructor TU and aligns the glyph-check declaration with it.

The pre-change range check found no `data_rows.csv` interval overlapping `[0x0134AEAC, 0x0134AEB0)` and no other DIR32 name starting inside that range. The only DIR32 entry at its start is the canonical spelling. The nearby pin check found no competing `symbols.csv` spelling at either the VA or RVA interpretation. No existing pin is changed or deleted.

Both Zero Hour `Generals` and `GeneralsMD` references declare `OldGDIFont`, `OldGDIBitmap`, `GDIBitmap`, `GDIFont`, `GDIBitmapBits` and `MemDC` as non-static instance members in `render2dsentence.h`, and initialize them in the instance constructor in `render2dsentence.cpp`. Neither has BFME's shared 20-byte GDI state class or a named shared pointer. BFME's layout therefore does not support adopting one of those member names for this datum.

## Refutation and raw evidence

A nonzero initial value in the hash-bound image, an overlapping datum or DIR32 name, a pointer write inconsistent with the constructor/last-release lifetime, a different shared-state DC offset, or a proven original static-member/global symbol would refute the corresponding conclusion. A changed instruction or failed data-byte verification would reject this implementation. A surviving unrecorded COFF reference would refute completion of the spelling repair.

Raw outputs are retained under `build/rlink/fontchars-0134aeac-1791146676/`: `retail-pointer-probe.log`, `retail-pointer-routes.log`, `retail-lifetime-and-names.log`, `caller-and-reference-contracts.log`, `font-sources.log`, `discovery.log` and `link-before.log`. Gate outputs and after-link measurements are listed in `build/worker-final.md`.

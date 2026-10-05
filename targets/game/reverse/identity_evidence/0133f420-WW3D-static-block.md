# WW3D static storage at VA 0x0133F420 through 0x0133F433

The canonical private spellings are applied to the supported game users. The nine existing definitions in ww3d.cpp remain the sole owners; no duplicate datum is introduced.

Nine members have conclusive identities. Their existing definitions in `game/Libraries/Source/WWVegas/WW3D2/ww3d.cpp` are the owners. The bytes at VA 0x0133F42C and VA 0x0133F42F remain unresolved. No function identity, function extent, shared header, or executable instruction is changed.

## Storage and canonical names

The baseline image has twenty zero bytes at this range in the virtual-only tail of `.data`. These are loader-zero writable storage, not compiler constants. The section's file-backed end precedes the range. The extent probe finds no data-row overlap and no differently addressed DIR32 name inside any proposed member's extent. The same-address competing spellings are recorded in `build/rlink/spellings-before.log`, with the number and paths of game files declaring each spelling.

| VA | Type and size | Initial value | Identity and canonical COFF spelling |
| --- | --- | --- | --- |
| 0x0133F420 | unsigned int, 4 bytes | 0 | `WW3D::SyncTime`, `?SyncTime@WW3D@@0IA` |
| 0x0133F424 | unsigned int, 4 bytes | 0 | `WW3D::PreviousSyncTime`, `?PreviousSyncTime@WW3D@@0IA` |
| 0x0133F428 | bool, 1 byte | false | `WW3D::IsInitted`, `?IsInitted@WW3D@@0_NA` |
| 0x0133F429 | bool, 1 byte | false | `WW3D::IsRendering`, `?IsRendering@WW3D@@0_NA` |
| 0x0133F42A | bool, 1 byte | false | `WW3D::IsCapturing`, `?IsCapturing@WW3D@@0_NA` |
| 0x0133F42B | bool, 1 byte | false | `WW3D::IsScreenUVBiased`, `?IsScreenUVBiased@WW3D@@0_NA` |
| 0x0133F42C | byte flag, 1 byte; original C++ type unproved | 0 | Highlight-rendering flag; original member name and class ownership unresolved |
| 0x0133F42D | bool, 1 byte | false | `WW3D::AreStaticSortListsEnabled`, `?AreStaticSortListsEnabled@WW3D@@0_NA` |
| 0x0133F42E | bool, 1 byte | false | `WW3D::MungeSortOnLoad`, `?MungeSortOnLoad@WW3D@@0_NA` |
| 0x0133F42F | byte flag, 1 byte; original C++ type unproved | 0 | Runtime rendering flag; original member name and class ownership unresolved |
| 0x0133F430 | FrameGrabClass pointer, 4 bytes | null | `WW3D::Movie`, `?Movie@WW3D@@0PAVFrameGrabClass@@A` |

All nine proved members are private below `private:` at line 314 in the game's `ww3d.h`. The Zero Hour header places the same members below `private:` at line 310. The native public getters and setters access private storage; they do not make the storage public. Therefore `@@0` is the correct access mangling. The `@@2` declarations in local ABI views are incompatible with the defining header. The actual native field behind `Is_Munge_Sort_On_Load_Enabled()` is `MungeSortOnLoad`, not `IsMungeSortOnLoadEnabled`.

## Retail behavior and receiver/argument contracts

RVA 0x008FD310 reads the dword at 0x0133F420, stores that old value at 0x0133F424, and stores its first unsigned stack argument at 0x0133F420. RVA 0x007239A0 returns the first dword minus the second. This is the reference's `Sync(unsigned int)` and `Get_Frame_Time()` contract. There is no receiver. The existing `SyncTime` pin also names 0x0133F420. Animation and texture-mapper bodies independently read the first word as the synchronized time. Raw bodies are in `build/rlink/body-008fd310.log` and `build/rlink/body-007239a0.log`.

RVA 0x008FD640 calls DX8 initialization, allocates a 0x324-byte default static-sort-list object, stores its pointer at 0x0133F444 and 0x0133F448, and sets 0x0133F428 only for non-lite startup. RVA 0x008FD6E0 clears the same flag after teardown. Begin/render/end bodies use it as their initialization guard. The sort-list pointers are outside this question's range. These facts distinguish initialization state from movie capture and distinguish the sort-list object from the pointer at 0x0133F430. Raw bodies are in `build/rlink/body-008fd640.log` and `build/rlink/body-008fd6e0.log`.

RVA 0x008FE280 reads 0x0133F429 to guard an already active render, then sets it before rendering. RVA 0x008FD880 clears it after flushing. Those read/write roles agree with native `IsRendering`; they are independent of declaration order. Raw bodies are in `build/rlink/body-008fe280.log` and `build/rlink/body-008fd880.log`.

RVA 0x008FD370 tests 0x0133F42A, clears it, invokes the scalar deleting destructor through the object pointer at 0x0133F430, and clears that pointer. RVA 0x008FD400 returns whether the pointer is non-null. RVA 0x008FDFD0 reads it for frame capture. The capture-start body at RVA 0x008FDE90 sets the flag and publishes the newly constructed grabber pointer. These are the reference's `IsCapturing` and `Movie`, not a second default static-sort-list pointer. The storage is static and has no receiver; capture operations use the pointed-to FrameGrabClass object as their receiver. Raw bodies are in `build/rlink/body-008fd370.log`, `build/rlink/body-008fd400.log`, `build/rlink/body-008fdfd0.log`, and `build/rlink/body-008fde90.log`.

RVA 0x006ED5B0 sets 0x0133F42B on display initialization, in the same reference operation that enables screen UV bias. RVA 0x00933A50 reads it before adding the half-pixel bias to the coordinate offset. RVA 0x006E7030 stores its first stack byte there, and RVA 0x0078AE10 reads it. The reference getter/setter contract is `bool Is_Screen_UV_Biased()` and `void Set_Screen_UV_Bias(bool)`. Raw bodies are in `build/rlink/body-006ed5b0.log`, `build/rlink/body-00933a50.log`, `build/rlink/body-006e7030.log`, and `build/rlink/body-0078ae10.log`.

RVA 0x008FD4E0 saves 0x0133F42D, clears it while rendering the current static-sort lists, and restores it. The scene/object renderers perform the same save/clear/restore operation. Display initialization sets this byte. Line and particle renderers read it to select static-sort handling. These agree with the native `AreStaticSortListsEnabled` getter/setter contract. The byte getter at RVA 0x006F9FF0 and setter at RVA 0x006E7050 touch that same address. Raw bodies are in `build/rlink/body-008fd4e0.log`, `build/rlink/body-008fe3c0.log`, `build/rlink/body-008fe730.log`, `build/rlink/body-006f9ff0.log`, and `build/rlink/body-006e7050.log`.

RVA 0x0096E750 tests the mesh SORT flag and zero sort level, then reads 0x0133F42E before tail-jumping to compute static sort levels. RVA 0x0094E060 reads the same byte before recomputing sort levels when the material selection changes. This matches Zero Hour `meshmdlio.cpp` and `meshmdl.cpp` calls to `Is_Munge_Sort_On_Load_Enabled()`, whose native header body reads private `MungeSortOnLoad`. RVA 0x0094DE20 is another six-byte read of the same byte followed by RET and INT3 padding. The direct reference scan found no absolute write to this byte; it does not exclude an indirect write. Raw bodies are in `build/rlink/body-0096e750.log`, `build/rlink/body-0094e060.log`, and `build/rlink/extra-retail-complete.log`.

The native header and definitions, including source line numbers, are recorded in `build/rlink/canonical-declarations.log`. The complete direct reference scan is `build/rlink/retail-references.log` with machine-readable records in `build/rlink/references.json`; each owned body has a raw `body-<rva>.log`. The extent checks and three additional instruction sites are in `build/rlink/extra-retail-complete.log`. This is a single static scan of the reference executable (n=1), not a runtime test. Ledger names in the census are labels; the instruction behavior and the native accessor bodies establish the corrections.

Five-byte E9 routes relevant to the byte accessors and frame-time getter are recorded with their original bytes and final body bytes in `build/rlink/thunks-callers.log`. Each recorded route terminates at the referenced body, whose first instruction is not another E9. No route is inferred from a stale symbolic label. The corrected data references themselves are direct absolute operands and do not rely on a thunk name.

## Ownership, limitations, and observations that would refute the correction

The existing ww3d.cpp object defines each of the nine canonical symbols once in uninitialized writable `.bss` storage. Their initial bytes agree with retail's loader-zero bytes, as recorded in `build/rlink/static-storage-verified.log`. No duplicate definitions are added. `tools/add_data_match.py` was attempted for all nine private symbols and refused to size each because the symbol cannot be named from its TU. The raw outputs are `build/rlink/add-data-<Member>.log`. The brief explicitly permits the existing private-static definition precedent when the tool cannot size it, so no data_rows.csv row is fabricated and no access is widened to satisfy the tool.

Two canonical spellings absent from DIR32 are added beside the existing spellings: private `IsRendering` and private `MungeSortOnLoad`. Their corresponding canonical pins are added, while every old pin remains unchanged. Local ABI views now declare the proved statics with private access. Native public inline getters/setters are used by external callers where they preserve the bytes. The wrongly typed shutdown movie pointer is retyped to FrameGrabClass and uses its virtual destructor. No ledger function name is changed, so `add_match.py --correct-identity` is not invoked and there is no function name regression.

The unsigned-byte setters in SmallLeafBodies.cpp retain their free data spelling. A scratch probe of the native bool setter with the existing unsigned-byte argument emits an additional TEST/SETNE normalization and grows from ten to fifteen bytes (`build/rlink/setter-probe.log`). Changing those function argument contracts would be a separate sanctioned identity correction. RendererInitialize00782ED0.cpp retains its two address-derived timing declarations because it independently reads private PreviousSyncTime; the native public API does not expose that word alone. Replacing that read with a computed expression would change the access contract. The unused `g_bfmeSeedBX` declaration in Bfme5TinySeven.cpp remains untouched; its former body already uses the native getter in Rva0095C7F0Initialize.cpp.

VA 0x0133F42C is set around highlighted-object rendering, cleared by the highlight filter, and read by DX8Wrapper drawing. This proves a highlight-related flag, but neither Zero Hour's header nor an existing pin supplies its original WW3D member name. VA 0x0133F42F is written by lighting-chunk parsing from a value compared with 1.0, temporarily disabled/restored by the separate rendering path at RVA 0x0078AC20, and read while choosing rendering state in RVA 0x00911020. Zero Hour `OverbrightModifyOnLoad` is used by mesh loading, whereas the BFME post-process body has no equivalent read of this byte. Adjacency alone cannot prove that spelling. Both bytes and their game sources remain unchanged. Raw counterevidence is in `build/rlink/meaning-check.log` and the corresponding retail body logs.

A different absolute operand in any cited accessor, a capture pointer that receives a static-sort-list object rather than the FrameGrabClass allocation, a native header declaring any proved member public, or any changed verified instruction would refute the correction. A surviving BFME declaration or an independently proved named caller/getter/setter accessing 0x0133F42C or 0x0133F42F would settle their outstanding original names and class ownership. A proved bool parameter contract plus a byte-preserving sanctioned function correction would settle the raw-byte setter limitation.

Source gates, CSV and pin checks, declaration checks, staged name and conversion gates, changed paths, measured LINKED bytes, and clock receipts are recorded in `build/worker-final.md`. Raw rerun logs are under `build/rlink/recheck-1791153676/`.

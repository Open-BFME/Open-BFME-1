# collate<char>::do_transform at RVA 0x00844400

The 87-byte body ends in `ret 0x0c` at RVA 0x00844454, followed by INT3
padding at 0x00844457. Ghidra independently creates the same 87-byte extent.

Retail vtable VA 0x0112EAD4 contains the deleting destructor at 0x00C32660,
compare at 0x00C442E0, this transform at 0x00C44400, and hash at 0x00C441C0.
Its preceding locator pointer is VA 0x011DE028. That locator's type descriptor
is VA 0x012C7818, whose name at +8 is `.?AV?$collate@D@_STL@@`.
The exact library's `inputs/vendor/stlport/stl/_collate.h` declares compare,
transform and hash in that order. The compare/hash neighbors have existing
native identities. `inputs/vendor/stlport/PROVENANCE.md` identifies this as
the STLport 4.5.3 dependency of the Zero Hour reference tree. Thus the full
method identity follows RTTI, slot order and the native library interface,
not the byte match or the previous bank's comment.

The bank reproduces 87 bytes except the empty iterator tag's stack home:
retail uses the hidden result-pointer slot at `[esp+0x18]`, while the bank
uses `[esp+0x20]`. Native `<locale>` declarations and the actual
`basic_string<char>::_M_range_initialize<const char*>` body, marked noinline,
restore all parent bytes. The helper is the vendor `_string.h` forward-range
implementation: measure distance, allocate count+1, uninitialized-copy the
range, and append the null terminator. It independently matches all 97 bytes
at RVA 0x002D8760 with resolved relocations. The already-existing const-char
helper pin at ILT RVA 0x0002A531 reaches that body and passes pin_consistency.
No duplicate helper ledger claim is added.

The parent unwind chain is handler RVA 0x00C55AE8 -> FuncInfo 0x00E44CC4 ->
state 0 (predecessor -1) cleanup 0x00C55AE0. The cleanup loads the saved result
receiver from `[ebp+4]` and jumps through ILT RVA 0x00016DE7 to 0x000A41C0.
That 39-byte body deallocates the range at receiver+0/+8 with the native
128-byte node-allocation threshold. This is the partially constructed string
base lifetime, not an invented guard or dummy destructor.

The final TU defines that destructor with the native `_M_deallocate_block()`
body and noinline. It independently passes strict comparison for all 39 bytes
at 0x000A41C0, with no unresolved relocations. Both helper checks use
`build.compile_function` and the ordinary string/constant/DIR32 verifiers
against the final production object; neither requires another ledger claim
or a new pin. The parent passes `./build.sh` in its final source form.

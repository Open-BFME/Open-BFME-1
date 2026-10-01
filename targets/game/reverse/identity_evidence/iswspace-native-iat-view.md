# Replace zero-data iswspace shadow with the native imported IAT cell

The matched identities and extents stay unchanged: the file-static helper at
RVA008872B0 is 46 bytes, ending with RET at008872DD; StringBase<unsigned short>
trim at00888ED0 is147 bytes, ending with RET at00888F62. This repair adds no
matched bytes and makes no fresh whole-image closure claim.

## Physical ABI and native owner

The shipped retail PE import directory identifies VA01359438 as
MSVCR71.dll!iswspace. Both bodies read that cell: helper DIR32 operand+13 and
trim DIR32 operand+79. The native VS2003 wctype.h declaration is
`_CRTIMP int __cdecl iswspace(wint_t)`, with wint_t defined as unsigned short.
Retail zero-extends the 16-bit input, passes it in a four-byte stack slot and
adds4 to ESP after the call. The return value is tested as int.

Old SkipWhitespaceW.c defined an uninitialized global function pointer named
iswspace, emitting the COMMON symbol `_iswspace`. Including this C body in the
trim TU duplicated that zero-data provider. Pinning `_iswspace` to the retail
IAT disguised the wrong definition in byte matching.

The repair instead declares only an external pointer view of the native import
cell. C identifier `_imp__iswspace` emits the canonical COFF symbol
`__imp__iswspace`; this is the symbol defined by the real CRT import-library
short record, not a new alias. No allocation, definition, initialization or pin
is supplied by these source files. The object symbol tables now contain only an
undefined external `__imp__iswspace` (section0, value0) and no `_iswspace` data
symbol. MSVCR71's real import record supplies the cell.

The loop retains the observed private EAX-incoming and EAX-returning helper ABI.
A direct native dllimport spelling after suppressing wctype's inline wrapper
hoists the IAT in the trim loop and emits156 bytes rather than147. The external
canonical cell view retains the repeated external-cell reads of retail without
asm, volatile additions, invented data or a resolver exception.

## Native StringBase adoption and real callees

StringBaseWideTrim.cpp includes the existing native
Libraries/Source/WWVegas/WWLib/string_base.h. Its old local StringBase class and
Header redeclarations are removed. Public trim's mangled name stays unchanged.
The native template supplies the single header pointer, ref count, ushort length
and capacity and two-byte element storage. Its own private data remain accessed
from the real member definition.

Retail trim's four direct call operands independently target the existing
matched bodies, with the same native header signatures:

- 00888EE1 calls008872B0, file-static `_skipWhitespace`, private EAX convention.
- 00888F13 calls00888260, wide ensureUniqueBufferOfSize; six stack arguments,
RET18h at008882E3 and008883EE; pointer receiver remains ECX.
- 00888F1C calls008881D0, wide releaseBuffer; RET at00888255, no stack args.
- 00888F56 calls00888840, wide removeLastChar; RET at00888921/0088892C, no stack args.

Fresh scoped gates verify both changed bodies2/2 and these three unchanged
StringBase callees3/3. Existing `_skipWhitespace` and wide releaseBuffer pins
are consistent; ensureUniqueBufferOfSize and removeLastChar resolve through
existing matched rows and require no added pins.

## Actual strict native positive and old zero-data negative

In isolated checkout origin/master f958ce4598, import_binding.py check passes
both actual source files, with no rewrite steps or import stubs. Actual linked
MAP and PE inspection proves each FF15 operand reads PE IAT10002000, whose
DLL/name entry is msvcr71.dll!iswspace. Both complete linked bodies match their
retail bytes outside relocation operands. Trim's helper call selects the real
included private helper at10001000. The helper needs no unrelated link-only
stubs; trim labels its three other functions as link-only stubs.

The old source negative also links successfully, making exit status alone
insufficient proof. Its PE has **zero imports**. The same call operand instead
reads a four-byte uninitialized `.data` cell at10002000; the mapped contents
are00000000. Thus the old route calls NULL rather than CRT iswspace. This
independently reproduces the earlier selected-map audit failure.

Receipts and reproduction scripts are in the isolated checkout's
build/iswspace_native/{check.py,receipt.json,actual_source_receipt.json}, with
the positive/negative DLLs and maps under links/. Official tool receipts are
build/import_binding/{SkipWhitespaceW,StringBaseWideTrim}/receipt.json.

## Retired witness

Repository-wide declaration search finds no remaining raw `_iswspace` data
view. Other authored iswspace declarations use native dllimport prototypes and
emit canonical `__imp__iswspace`. Only obsolete `_iswspace,01359438` is removed
from dir32_addresses.csv; canonical `__imp__iswspace,01359438` is retained.
No symbols.csv pin, function row, shared header, tool or guard is changed.

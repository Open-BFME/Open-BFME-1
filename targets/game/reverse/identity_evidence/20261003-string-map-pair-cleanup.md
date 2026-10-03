# String-map temporary and pair destructor

Retail BFME1 1.03 unpacked baseline; addresses below are RVAs. Raw PE bytes
were cross-checked with Ghidra memory. Ghidra also creates the complete
175-byte parent at 009D8580 and recovers its conditional key/value temporary.

The existing native parent in `Rva009D8580StringMapOperator.cpp` instantiates
STLport's `hash_map<basic_string<char>, int>::operator[]`. Its same-object
caller at 009D86E0 and insert callee at 009D8350 previously established the
key/value types. The actual upstream implementation at
`inputs/vendor/stlport/stl/_hash_map.h:184` constructs `_value_type(key, int())`
in its missing-key branch. `_value_type` is `pair<const basic_string<char>, int>`.

The retail prologue pushes C61079 at 009D8582. Handler C61079 selects FuncInfo
E507C8, map E507C0, state 0 -> -1, action C61060. This action tests mask 1 in
EBP-20 and destroys the temporary at EBP-1C through 009D7D80. Its complete
25-byte extent includes RET C61078; the handler starts immediately after it.
The unchanged native parent emits this action as $L11099, with the canonical
pair destructor as its only relocation. Identity comes from the parent's
actual temporary lifetime and types, not from neighboring code or byte equality.

009D7D80 is 39 bytes. It reads the string storage pointer at offset 0 and
storage-end pointer at offset 8, skips null storage, uses operator delete at
00881EB0 above 128 bytes, and otherwise calls the canonical STLport node
deallocator at 0082E5F0. RETs occur at 009D7D9B and 009D7DA6; INT3 padding begins
at 009D7DA7. The native pair destructor already emitted by the parent is the
provider; no custom allocator implementation or fake lifetime wrapper is needed.

Replace the `gen-tgrid` vector-clear placeholder at 009D7D80 with this canonical
native pair destructor, then claim the native action at C61060. No generated
source, shared header, or symbol pin is edited. Other legacy callers' type
views are not promoted as identity evidence by this change.

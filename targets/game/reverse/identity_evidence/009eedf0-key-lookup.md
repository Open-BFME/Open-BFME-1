# AssetRegistry address-derived lookup, RVA 0x009EEDF0

The matched Rva009EC0D0AssetRegistryName caller loads g_theAssetRegistry
and calls this existing pinned method with an unsigned key; it forwards the
returned const char pointer. This establishes the receiver and ABI, not an
original semantic method name. Retain Rva009EEDF0Lookup.

Native 197-byte extent ends RET4 at 0x009EEEB2, followed by padding.
Ghidra created/decompiled the same extent; retail bytes independently decoded
with pefile/capstone show EnterCriticalSection on this+0x2C, hash bucket vector
at +0x48/+0x4C and STLport node {next,key,value}. The map starts at +0x44,
consistent with separately matched AssetRegistry Find_Asset and
Render_Obj_Exists_Impl. Canonical Windows CRITICAL_SECTION is 24 bytes.
The value object uses virtual slot 0 with no arguments beyond ECX and returns
the name pointer; no semantic class or slot name is inferred.

The native miss literal at VA 0x011454A4 is <unknown> including its NUL.
STLport hash_map::find preserves the two native miss exits (empty bucket and
exhausted chain); a hand-rolled collapsed loop loses that compiler structure.
The single unwind state is guarded by a one-word critical-section pointer;
handler RVA 0x00C61A08 / FuncInfo 0x00E51250 cleanup 0x00C61A00 LEAs the
scope then jumps to lock release 0x009ECAC0. Normal exits LeaveCriticalSection.
The source guard uses an opaque address-derived local type; it does not
re-identify the separately recorded lock constructor or release body.

Probe with canonical Windows types: 197 bytes exact modulo 12 relocations.
Production acceptance requires the strict scoped build, including imports,
string literal and EH metadata; probe masking alone is not the verdict.

Strict add_match scoped build passed 1/1: two literals and all four DIR32
references verified; no added symbol pins or baseline edits.

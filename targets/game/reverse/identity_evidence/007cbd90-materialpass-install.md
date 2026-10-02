# RVA 0x007CBD90: derived MaterialPassClass::Install_Materials slot

The retail constructor RVA 0x007CBB30 calls native MaterialPassClass's
constructor 0x009333A0 at VA 0x00BCBB33, then installs primary table
**0x01128880** at VA **0x00BCBB4B**. Its synthetic `Bfme5MaterialPass`
label is not evidence of the original subclass spelling. The derived fields
are +0x38/+0x3C constructor arguments and zeroed +0x40/+0x44.

Table slot **2**, pointer VA **0x01128888**, contains the unique ILT
**0x00447348** -> body **0x007CBD90**. Ghidra's pointer search agrees
with a complete-image retail PE search. The native base constructor installs
table **0x0113C884** at VA **0x00D333DD**. Its same slot, VA 0x0113C88C,
contains direct body VA **0x00D33590**, the independently matched
`MaterialPassClass::Install_Materials() const`. Both tables have the same
RefCountClass::Delete_This first slot and deleting-destructor second slot;
their fourth slot is the corresponding cleanup/no-op. Thus the target is an
Install_Materials override, while its subclass remains unknown. The canonical
matpass.h declaration corroborates the const, zero-argument interface.

The target lazily loads `shaders\\unlitnormalextrusion.vso`, whose bytes at
VA **0x01128894** were independently read in Ghidra and retail. It configures
D3D state, transforms and shader constants, consistent with that interface.
Neither the shader filename nor synthetic constructor label supplies a native
subclass identity. No direct caller reaches the body or its ILT.

The 1181-byte boundary ends in plain RET at +0x49C and INT3 at +0x49D.
There is a 0x124-byte local frame, SEH, StringClass temporaries, imported
matrix operations and a helper with inferred ABI. The clean reconstruction now uses the address-derived subclass identity
`Rva007CBB30` and the proven Install_Materials override role, preserving the
unresolved native subclass spelling. The canonical source gate verifies all
46 matched bodies, 13 literals, 34 floats and 832 DIR32 references. Three
separate data rows verify the four-byte shader storage, four-byte once guard
and sixteen-byte canonical Vector4; declared extents and zero-filled initial
image values are compiler/retail-verified. The initialized-data checker has no
function-row anchor for this data-only TU and returns UNVERIFIED; the
repository-prescribed zero-filled data-row gate verifies these BSS objects.


## Native reconstruction evidence

The source retains the unproven subclass spelling as `Rva007CBB30`, using the
constructor address. It derives from canonical `MaterialPassClass`; the native
base extent is 0x38 bytes, independently checked against the constructor and
compiled header. The derived fields occupy +0x38/+0x3C/+0x40/+0x44. Native
+0x3C is copied as a float to the shader constant vector.

The call at target +0xCF passes the original receiver in ECX to ILT 0x00046457,
which reaches 0x007CBB70. That helper has no stack arguments, modifies +0x40 and
+0x44, reads +0x38, and returns its four-byte value in EAX. The address-derived
callee declaration asserts only that ABI, not a semantic method name. Its
270-byte code extent ends in RET at +0x10D. The separate 16-byte switch table
begins at +0x110 (RVA 0x007CBC80) and remains unclaimed data.

The rendering body tests bit 1 of the four-byte guard at VA 0x013071A4, sets it
before constructing a four-byte ShaderClass with bits 0x105833 at VA 0x013071A0,
and then uses the live object. Source preserves that delayed lifetime with
placement construction in aligned four-byte character storage, without a heap
allocation or startup constructor. Canonical Vector4 storage at VA 0x0130718C
is sixteen zero-filled bytes; native updates its first float and submits all
four floats to shader constant register 8. These three data objects occupy
loader-zero virtual .data; raw file-offset reads beyond SizeOfRawData are not
evidence. The data TU emits no CRT initializer section or initializer symbol.

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
matrix operations and a helper with inferred ABI. A large reconstruction is
outside this small-body pass. This commit records the proven override role
and retains the unresolved owner/conversion work; it changes no source or pin.

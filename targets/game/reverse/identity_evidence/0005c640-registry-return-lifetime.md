# Registry return lifetime at RVA 0005C640

Matched 009EBCE0 returns the address-qualified native type
Rva009EBCE0AssetReference. Its prologue pushes handler C61832, which loads
FuncInfo E5106C. State0 -> -1 selects C61800. This 25-byte action guards
bit1 at EBP-10, loads the hidden result pointer at EBP+4, then jumps through
ILT27C41 to 0005C640. RET C61818 proves the action extent. Both compiler
predecessor states agree, and exact corresponding label $L342 calls the
native Rva009EBCE0AssetReference destructor.

The raw 12-byte destructor loads the data pointer, null-guards it, and
jumps to the already pinned counted release at 009EB7A0. RET5C64B then
INT3 prove the full extent. The existing native destructor in unchanged
RegistryPrototypeLookup.cpp implements that exact operation and relocation.

This replaces the unrelated NetCommandRef provider at the existing opaque
row. The destructor identity retains the native owner's address; it does
not assert an original semantic class name. The particular retail copy is
proved by the matched parent return lifetime, not generic byte equality.
No pin or second identity is added, and these already matched12B add no
coverage. The separate native AssetReference view used by 009EBEC0 also
calls this address through its state0 action C61899, but unifying the two
return-type views is a separate coordinated repair.

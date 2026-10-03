# RVA 00A6C48B: distinct native CTransform leaf

Retail bytes are `B8 01 40 00 80 C3`, ending at RET 00A6C490.
The following independent function starts at 00A6C491 with the deleting
wrapper's flag test. Ghidra read_memory at VA00E6C48B agrees with the unpacked
baseline; table VA011518A0 slot1 and VA011518A8 slot1 both contain VA00E6C48B.
There is one body, inherited by two tables, not two identity claims.

The original Summer2003 d3dx9.lib member obj\i386\cprogram.obj supplies:

- `??_7CTransform@D3DXShader@@6B@`: exactly two relocations, deleting destructor
  at +0 and `?Apply@CTransform@D3DXShader@@UAEJXZ` at +4.
- `??_7CTReorderInstructions@D3DXShader@@6B@`: deleting destructor at +0,
  the same base method at +4, and its int-argument Apply overload at +8.
- The CTransform constructor's 18 bytes match retail 00A6C472, with its
  original table relocation at +8 bound to VA011518A0. Its seven-byte
  destructor matches 00A6C484 and stores that same table. The derived
  constructor at 00A6C4AE stores VA011518A8.
- The original Apply symbol contains exactly the six retail bytes, no
  relocations; its mangling establishes long __thiscall with no arguments.

These complete table relations establish the owner independently of an old
masked constructor claim naming CAllocateHierarchyWrapper at 00A6C472.
That legacy claim must not be used as owner evidence and is left for its own
identity/provider repair. This recovery conservatively retains the address
in its method name. No new pin, shared declaration, or semantic rename is used.

Fresh fetched master history and ledger checks found no existing 00A6C48B row.
`callees.py 0x00A6C48B 6` reports zero direct call targets.

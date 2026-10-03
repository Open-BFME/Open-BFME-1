# Native return lifetime at 00971CC0

The existing matched factory 00971E90 returns the address-qualified native
handle Gen00971E40. Its prologue pushes handler C5F2D1, which loads FuncInfo
E4E6E0. State 0 -> -1 selects C5F2B0: bit1 at EBP-10 guards destruction of
the hidden result at EBP+4, with a direct tail jump to 00971CC0. Both native
predecessor states agree; corresponding compiler label $L341 names
`??1Gen00971E40@@QAE@XZ` after supplying its visible C++ definition.

The full 12 bytes at 00971CC0 dereference this, test the pointer, and jump
to the already typed release body 009EB7A0. RET at 00971CCB is followed by
INT3. The source definition matches these bytes with the real release
relocation. Ghidra independently creates a 12-byte body.

This replaces the old unrelated NetCommandRef byte provider. The constructor
address remains in the native type name; no original semantic owner name is
claimed. The matched returned-object lifetime, rather than byte equality
with another destructor, proves this copy's binding. The ledger retains
one identity at 00971CC0. These 12 bytes were already matched and add no
coverage; they are a dependency repair for the 25-byte action.

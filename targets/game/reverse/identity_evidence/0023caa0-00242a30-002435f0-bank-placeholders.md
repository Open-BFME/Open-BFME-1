# Contain banks 0x0023CAA0 / 0x00242A30 / 0x002435F0: placeholder renames

name_regression reports five descriptive-to-placeholder renames in these
banked attempts. None of the old names is an identity:

- `0x0023caa0.cpp`, `Object -> Rva00238740Lookup`: nothing was renamed. The
  old bank declared its own TU-local `class Object` with pinned stubs. The new
  bank includes the real `object.h` and still uses `Object` throughout
  (`checkMember(Object *candidate)`). `Rva00238740Lookup` is the class of the
  matched ledger row `?find@Rva00238740Lookup@@...` at 0x00238740, the lookup
  that the body calls.
- `0x00242a30.cpp`, `m_bfmeHead -> m_pad0c`, `m_bfmeGap2 -> m_pad134`,
  `m_bfmeGap3 -> m_pad1dc`: these are unnamed padding spans in both versions.
  "Head" and "Gap" named no field. The new names give the offset each span
  starts at, which is the repo's layout-padding convention.
- `0x002435f0.cpp`, `fillFormationPosition -> rva002350c0`: the old bank
  declared `Coord3D *fillFormationPosition(Coord3D *, Int)` and aliased it to
  the ILT thunk `?j_00019736@@YAXXZ`, whose target is FUN_006350c0, i.e. RVA
  0x002350C0. That body is already a matched ledger row,
  `?rva002350c0@Rva00233F30@@QAE?AUBfmeRva44E60Record@@H@Z`: it returns a
  16-byte `BfmeRva44E60Record` by value, whose sole-caller evidence is in
  `identity_evidence/00232470.md`. `fillFormationPosition` does not occur in
  `inputs/reference`, `functions.csv` or `symbols.csv`, so it was a guess. The
  bank now calls the callee by its ledger name.

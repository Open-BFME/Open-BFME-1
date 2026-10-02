# GameWindow border setter link repair

The existing matched border setters have proven extents at RVA 0x00479040
(37 bytes), 0x004790E0 (40 bytes), and 0x00479190 (40 bytes). Their retail
stores use GameWindow offsets +0x50, +0xBC, and +0x128. The GameWindow.cpp
Zero Hour implementations use different offsets and are marked present-unmatched;
none has a ledger row. Remove those three definitions, retaining the verified
GameWindowBorderColorSetters.cpp implementations.

The untouched base-Generals reference GameWindow.cpp also emits wrong copies
of these setters. Its only matched ledger row is the implicit
WinInstanceData::operator= at RVA 0x00478780, size 999. Retain the exact header
instantiation in WinInstanceDataAssignment.cpp using the same compilation flags
and an internal pointer-to-member emission anchor. No wrapper implementation,
new identity, pin, header edit, or reference-tree edit is involved. The ledger
row stays in its original position and keeps its name, RVA, and extent.

## Verification

- Scoped builds pass all 55 GameWindow.cpp rows, the assignment row, and all
  three border setters.
- Baseline link_check.py on GameWindowBorderColorSetters.cpp reports three
  duplicate definitions and three wrong selected definitions: zero linked bytes.
- Census provenance: 2026-10-01 13:05, commit 5d21e9aecc, local accepted_gp index.
- Current-provider preview uses a private in-memory index copy. After asserting
  zero current ledger rows refer to the retired reference source, replace its
  object name at encounter slot 12053 with the isolated assignment object.
  This preserves the moved row's source encounter order. Refresh GameWindow.cpp,
  GameWindowBorderColorSetters.cpp, and WinInstanceDataAssignment.cpp together
  through link_check.refresh, then run check_object/report on each.
- Border setters: six blockers to zero; linked bytes 0 to 117. The wider
  GameWindow TU and isolated assignment still have unrelated existing blockers;
  no linked-byte gain is claimed for them. The canonical census is unchanged.

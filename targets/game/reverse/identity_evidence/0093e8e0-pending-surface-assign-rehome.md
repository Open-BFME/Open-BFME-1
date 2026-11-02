# 0x0093E8E0: address-derived re-home of a duplicate-named assignment body

- Row before: `?dup_0093e8e0@@YAXXZ`, gen-alias with
  `object-symbol=??4PendingSurfaceStruct@Render2DSentenceClass@@QAEAAU01@ABU01@@Z`,
  source `game/Libraries/Source/WWVegas/WW3D2/PendingSurfaceStructAssignmentBFME.cpp`.
- The same mangled name is the matched 47-byte row at 0x0036DAF0
  (`PendingSurfaceStructAssignThunk.cpp`). Retail was linked without identical
  COMDAT folding, so the two bodies (47 and 71 bytes, different code) cannot share
  one identity; both TUs emitting the symbol is link queue #476 (duplicates).
- BFME 1 evidence for 0x0093E8E0: no REL32 call or jmp in retail .text reaches it
  (scan 2026-11-02), so no caller names it. The body is the ZH
  PendingSurfaceStruct::operator= shape over the BFME renderer vector (structural
  inference only; donor/ZH name is a lead, not proof).
- Decision: keep the bytes, give the body the honest address-derived name
  `??4Rva0093E8E0PendingSurface@@QAEAAU0@ABU0@@Z`; the matched 0x0036DAF0 row keeps
  the ZH name.

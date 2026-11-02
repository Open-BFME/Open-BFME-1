# 0x00465AB0: address-derived re-home of a second newLocomotor-shaped body

- Row before: `dup_465ab0` with
  `object-symbol=?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z`,
  source `game/GameEngine/Source/GameLogic/Object/LocomotorStore_newLocomotor_dup.cpp`.
- The same mangled name is the matched 98-byte row at 0x001B6920
  (`LocomotorStore_newLocomotor.cpp`). Retail was linked without identical-COMDAT
  folding, so the 95-byte body at 0x00465AB0 is a different function; both TUs
  defining the symbol is link queue #300 (duplicates).
- BFME 1 evidence: no REL32 call or jmp in retail .text reaches 0x00465AB0 or its
  ILT 0x00018F52 (scan 2026-11-02). The body is the ZH newLocomotor shape (one
  `new Locomotor(tmpl)`, 0x2C bytes) — a structural lead, not an identity.
- Decision: keep the bytes under `?newLocomotor@Rva00465AB0LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z`.

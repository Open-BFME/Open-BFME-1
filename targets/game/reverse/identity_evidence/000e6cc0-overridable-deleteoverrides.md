# 0x000E6CC0 Overridable::deleteOverrides (39 B)

Replaces the invented row `?bfmeRelease@BfmeRefAB@@QAEPAV1@XZ`.

BFME 1 target evidence:
- ILT 0x00032D1C (`jmp 0x000E6CC0`) is already pinned as
  `?deleteOverrides@Overridable@@QAEPAV1@XZ` (LocomotorStore::reset 0x001B7160
  calls it); `tools/ilt_oracle.py` CONFIRMS that name at 0x000E6CC0 (exact
  window, p_false 2.6e-4) and CONTRADICTS `?bfmeRelease@BfmeRefAB@@QAEPAV1@XZ`.
- Body: if byte +0x08 is set, call vtable slot 0 with 1 (deleting dtor) and
  return 0; else if +0x04 is non-null, recurse through the same ILT and store
  the result at +0x04; return this. This is Zero Hour's
  `Overridable::deleteOverrides()` (GeneralsMD Common/Overridable.h:
  m_nextOverride at +4, m_isOverride at +8 after the vptr).

Structural inference: field names follow Zero Hour; offsets are measured.
Link queue #86 (census bb53b24f2b) listed ScienceStoreReset.cpp and
ThingFactory_reset.cpp as losers because the ledger had no row under this name.
